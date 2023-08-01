#include "ADC.h"
#include <esp_log.h>
#include <algorithm>

static const char* TAG = "ADC";

ADC::ADC(gpio_num_t pin, float ema_a, int min, int max, int readingOffset) : pin(pin), ema_a(ema_a), min(min), max(max), offset(readingOffset){
	if(pin != GPIO_NUM_10){
		ESP_LOGE(TAG, "Only GPIO 10 is supported for ADC");
		valid = false;
		return;
	}

	adc_oneshot_unit_init_cfg_t init_config1 = {
			.unit_id = ADC_UNIT_1,
			.ulp_mode = ADC_ULP_MODE_DISABLE,
	};
	adc_oneshot_new_unit(&init_config1, &adc1_handle);

	adc_oneshot_chan_cfg_t config = {
			.atten = ADC_ATTEN_DB_11,
			.bitwidth = ADC_BITWIDTH_12,
	};

	ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_CHANNEL_9, &config));

	sample();
}

ADC::~ADC(){
	adc_oneshot_del_unit(adc1_handle);
}

void ADC::setEmaA(float emaA){
	ema_a = emaA;
}

void ADC::resetEma(){
	val = -1;
	sample();
}

float ADC::sample(){
	if(!valid){
		return 0;
	}

	float reading = 0;
	if(pin == GPIO_NUM_10){
		int raw = 0;
		adc_oneshot_read(adc1_handle, ADC_CHANNEL_9, &raw);
		reading = raw;
	}

	if(val == -1 || ema_a == 1){
		val = reading;
	}else{
		val = val * (1.0f - ema_a) + ema_a * reading;
	}

	return getVal();
}

float ADC::getVal() const{
	if(!valid){
		return 0;
	}

	if(max == 0 && min == 0){
		return val + offset;
	}

	float min = this->min;
	float max = this->max;
	bool inverted = min > max;
	if(inverted){
		std::swap(min, max);
	}

	float val = std::clamp(this->val + offset, min, max);
	val = (val - min) / (max - min);
	val = std::clamp(val * 100.0f, 0.0f, 100.0f);

	if(inverted){
		val = 100.0f - val;
	}

	return val;
}

