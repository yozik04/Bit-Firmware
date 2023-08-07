#include "StaticRC.h"
#include <utility>
#include <esp_log.h>
#include "Color.h"

StaticRC::StaticRC(File file, PixelDim dim) : file(std::move(file)), dim(dim){}

void StaticRC::push(Sprite& parent, PixelDim pos, float rot) const{
	if(!file){
		ESP_LOGE("Render", "StaticRC: Pushing closed file");
		return;
	}

	if(rot == 0){
		Display::drawFile(parent, file, pos.x, pos.y, dim.x, dim.y);
	}else{
		Sprite rotated = Sprite(parent);
		rotated.createSprite(dim.x, dim.y);
		rotated.clear(TFT_TRANSPARENT);
		Display::drawFile(rotated, file, 0, 0, dim.x, dim.y);
		rotated.pushRotateZoomWithAA(pos.x + dim.x / 2, pos.y + dim.y / 2, rot, 1, 1, TFT_TRANSPARENT);
	}
}

void StaticRC::setFile(File file){
	StaticRC::file = file;
}

void StaticRC::setFile(File file, PixelDim dim){
	StaticRC::file = file;
	StaticRC::dim = dim;
}
