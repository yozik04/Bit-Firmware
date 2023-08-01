#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <nvs_flash.h>
#include "Settings/Settings.h"
#include "Util/Services.h"
#include "Periph/PWM.h"
#include "Pins.hpp"
#include "Services/BacklightBrightness.h"
#include "Services/ChirpSystem.h"
#include "Periph/I2C.h"
#include "Devices/Display.h"
#include "Devices/Input.h"
#include "Devices/Battery.h"
#include "Util/Notes.h"
#include "Util/Events.h"

BacklightBrightness* bl;

void init(){
	auto ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	auto settings = new Settings();
	Services.set(Service::Settings, settings);

	auto blPwm = new PWM(PIN_BL, LEDC_CHANNEL_1, true);
	blPwm->detach();
	bl = new BacklightBrightness(blPwm);
	Services.set(Service::Backlight, bl);

	auto buzzPwm = new PWM(PIN_BUZZ, LEDC_CHANNEL_0);
	auto audio = new ChirpSystem(*buzzPwm);
	Services.set(Service::Audio, audio);

	auto i2c = new I2C(I2C_NUM_0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);

	auto disp = new Display();
	auto input = new Input(true);
	Services.set(Service::Input, input);

	if(settings->get().sound){
		audio->play({
							Chirp{ .startFreq = NOTE_E4, .endFreq = NOTE_GS4, .duration = 100 },
							Chirp{ .startFreq = 0, .endFreq = 0, .duration = 200 },
							Chirp{ .startFreq = NOTE_GS4, .endFreq = NOTE_B4, .duration = 100 },
							Chirp{ .startFreq = 0, .endFreq = 0, .duration = 200 },
							Chirp{ .startFreq = NOTE_B4, .endFreq = NOTE_E5, .duration = 100 }
					});
	}

	printf("fade in\n");
	bl->fadeIn();
	printf("fade out\n");
	bl->fadeOut();
	printf("fade in\n");
	bl->fadeIn();


	auto& display = disp->getLGFX();
	int colors[] = { TFT_RED, TFT_GREEN, TFT_BLUE };
	for(auto& c : colors){
		display.clear(c);
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}

	display.clear(TFT_BLACK);
	display.setTextColor(TFT_GOLD);
	display.setCursor(50, 103);

	EventQueue queue(10);
	Events::listen(Facility::Input, &queue);

	while(1){
		Event item{};
		if(queue.get(item, portMAX_DELAY)){
			if(item.facility == Facility::Input){
				auto* data = (Input::Data*) item.data;
				if(data->action == Input::Data::Press){
					display.clear();
					display.setCursor(50, 103);
					display.print(Input::PinLabels.at(data->btn));
				}else if(data->action == Input::Data::Release){
					display.clear();
				}
			}
			free(item.data);
		}
	}
}

extern "C" void app_main(void){
	init();

	vTaskDelete(nullptr);
}
