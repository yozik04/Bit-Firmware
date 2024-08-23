#include "FSLVGL.h"
#include "FS/SPIFFS.h"
#include "Util/stdafx.h"
#include "Settings/Settings.h"
#include "Util/Services.h"
#include "Filepaths.hpp"
#include <cstdio>
#include <dirent.h>
#include <esp_spiffs.h>
#include <string>
#include <unordered_map>

std::initializer_list<std::string> ThemedCache = {
		"/bg.bin",
		"/header.bin",
		"/barShort.bin",
		"/barLong.bin",
		"/barMid.bin",
		"/header.bin",
		"/paused.bin",
		"/settings.bin",
		"/popup.bin",
		"/battery/bg.bin",
		"/battery/1.bin",
		"/battery/2.bin",
		"/battery/3.bin",
		"/battery/4.bin",
		"/battery/5.bin",
		"/battery/6.bin"
};

std::initializer_list<std::string> GeneralCache = {
		"/Profile/bg.bin",
		"/Profile/lock.bin",
		"/Profile/barOutline.bin",
		"/Profile/arrowDown.bin",
		"/Profile/arrowUp.bin",
		"/Profile/arrowLeft.bin",
		"/Profile/arrowRight.bin",
		"/Profile/ach-border.bin",
		"/Profile/ach-placeholder.bin",
		"/Profile/theme-01-icon.bin",
		"/Profile/theme-02-icon.bin",
		"/Profile/theme-03-icon.bin",
		"/Profile/theme-04-icon.bin",
		"/Profile/theme-outline.bin"
};

std::initializer_list<std::string> Archives = {
		"/Achi",
		"/AchiBW",
		"/Menu",
		"/MenuBW"
};

const char* TAG = "FSLVGL";

bool FSLVGL::themeChanged = false;

FSLVGL::FSLVGL(char letter, Allocator* alloc) : alloc(alloc), archive(Archives){
	lv_fs_drv_init(&drv);

	drv.letter = letter;
	drv.ready_cb = [](struct _lv_fs_drv_t*){ return true; }; // Is the drive ready to use?
	drv.open_cb = [](struct _lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode){ return ((FSLVGL*) drv->user_data)->lvOpen(path, mode);  };
	drv.close_cb = [](struct _lv_fs_drv_t* drv, void* file){ return ((FSLVGL*) drv->user_data)->lvClose(file);  };
	drv.read_cb = [](struct _lv_fs_drv_t* drv, void* file, void* buf, uint32_t btr, uint32_t* br){ return ((FSLVGL*) drv->user_data)->lvRead(file, buf, btr, br); };
	drv.write_cb = [](struct _lv_fs_drv_t* drv, void* file, const void* buf, uint32_t btw, uint32_t* bw){ return ((FSLVGL*) drv->user_data)->lvWrite(file, buf, btw, bw); };
	drv.seek_cb = [](struct _lv_fs_drv_t* drv, void* file, uint32_t pos, lv_fs_whence_t whence){ return ((FSLVGL*) drv->user_data)->lvSeek(file, pos, whence); };
	drv.tell_cb = [](struct _lv_fs_drv_t* drv, void* file, uint32_t* pos){ return ((FSLVGL*) drv->user_data)->lvTell(file, pos); };

	drv.dir_open_cb = [](struct _lv_fs_drv_t* drv, const char* path){ return ((FSLVGL*) drv->user_data)->lvDirOpen(path); };
	drv.dir_read_cb = [](struct _lv_fs_drv_t* drv, void* dir, char* fn){ return ((FSLVGL*) drv->user_data)->lvDirRead(dir, fn); };
	drv.dir_close_cb = [](struct _lv_fs_drv_t* drv, void* dir){ return ((FSLVGL*) drv->user_data)->lvDirClose(dir); };

	drv.user_data = this;

	lv_fs_drv_register(&drv);
}

FSLVGL::~FSLVGL(){
	esp_vfs_spiffs_unregister("storage");
}

void FSLVGL::themeChange(){
	themeChanged = true;
}

void FSLVGL::loadCache(){
	if(cacheLoaded && themeChanged){
		unloadCache();
		themeChanged = false;
	}

	if(cacheLoaded) return;
	cacheLoaded = true;

	cache.setPaths(getCacheFiles());

	cache.load(alloc);
	archive.load(alloc);

	printf("Cache loaded. Alloc remaining: %zu B\n", alloc->freeSize());
	heapRep();
}

void FSLVGL::unloadCache(){
	if(!cacheLoaded) return;
	cacheLoaded = false;

	cache.unload();
	archive.unload();

	if(alloc){
		alloc->reset();
	}
}

std::vector<std::string> FSLVGL::getCacheFiles() const{
	auto settings = (Settings*) Services.get(Service::Settings);

	const auto theme = settings ? settings->get().theme : Theme::Theme1;

	std::vector<std::string> paths;
	paths.reserve(ThemedCache.size() + GeneralCache.size());

	static constexpr const char* ThemePaths[] = { "/Theme1", "/Theme2", "/Theme3", "/Theme4" };

	for(const auto& file : ThemedCache){
		paths.emplace_back(std::string(ThemePaths[(int) theme]) + file);
		printf("%s\n", paths.back().c_str());
	}

	for(const auto& file : GeneralCache){
		paths.emplace_back(file);
	}

	return paths;
}

void* FSLVGL::lvOpen(const char* path, lv_fs_mode_t mode){
	File file;

	static const auto mkPtr = [](File& file){
		file.seek(0);
		File* filePtr = new File();
		*filePtr = std::move(file);
		return filePtr;
	};

	file = archive.open(path);
	if(file) return mkPtr(file);

	file = cache.open(path);
	if(file) return mkPtr(file);

	static const std::unordered_map<lv_fs_mode_t, const char*> Map = {
			{ LV_FS_MODE_WR, "w" },
			{ LV_FS_MODE_RD, "r" }
	};

	file = SPIFFS::open(path, Map.at(mode));
	if(file) return mkPtr(file);

	return nullptr;
}

lv_fs_res_t FSLVGL::lvClose(void* file){
	File* filePtr = (File*) file;
	delete filePtr;
	return 0;
}

lv_fs_res_t FSLVGL::lvRead(void* fp, void* buf, uint32_t btr, uint32_t* br){
	File* file = getFile(fp);
	if(!*file) return LV_FS_RES_NOT_EX;

	*br = file->read((uint8_t*) buf, btr);

	return 0;
}

lv_fs_res_t FSLVGL::lvWrite(void* fp, const void* buf, uint32_t btw, uint32_t* bw){
	File* file = getFile(fp);
	if(!*file) return LV_FS_RES_NOT_EX;

	*bw = file->write((const uint8_t*) buf, btw);

	return 0;
}

lv_fs_res_t FSLVGL::lvSeek(void* fp, uint32_t pos, lv_fs_whence_t whence){
	File* file = getFile(fp);
	if(!*file) return LV_FS_RES_NOT_EX;

	static const std::unordered_map<lv_fs_whence_t, SeekMode> Map = {
			{ LV_FS_SEEK_SET, SeekMode::SeekSet },
			{ LV_FS_SEEK_CUR, SeekMode::SeekCur },
			{ LV_FS_SEEK_END, SeekMode::SeekEnd }
	};
	if(!Map.contains(whence)) return LV_FS_RES_INV_PARAM;

	const auto success = file->seek(pos, Map.at(whence));
	if(!success) return LV_FS_RES_INV_PARAM;

	return 0;
}

lv_fs_res_t FSLVGL::lvTell(void* fp, uint32_t* pos){
	File* file = getFile(fp);
	if(!*file) return LV_FS_RES_NOT_EX;

	printf("pos\n");

	*pos = file->position();
	return 0;
}

void* FSLVGL::lvDirOpen(const char* path){
	std::string p = Root + std::string(path);
	DIR* dir = opendir(p.c_str());
	return dir;
}

lv_fs_res_t FSLVGL::lvDirRead(void* dir, char* fn){
	auto entry = readdir((DIR*) dir);
	if(!entry) return LV_FS_RES_NOT_EX;
	strncpy(fn, entry->d_name, 256);
	return 0;
}

lv_fs_res_t FSLVGL::lvDirClose(void* dir){
	closedir((DIR*) dir);
	return 0;
}
