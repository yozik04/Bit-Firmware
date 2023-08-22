#include "Battery.h"
#include "../Pins.hpp"
#include "Util/Events.h"
#include <soc/efuse_reg.h>
#include <Util/stdafx.h>
#include <cmath>
#include <driver/gpio.h>

//voltage divider means that for 4.6V on battery there is ( 4.6V * 2 / 3 ) = 3.067V voltage on pin, mapped so that 4095 equals 3.1V:
//expected ADC value is 3.067V / 3.1V * 4095 = 4051, taken a conservative estimate to 4050
#define MAX_READ 4050 // 4.5V
#define MIN_READ 3170 // 3.6V

Battery::Battery() : SleepyThreaded(MeasureIntverval, "Battery", 3 * 1024, 5), adc((gpio_num_t) PIN_BATT, 0.05, MIN_READ, MAX_READ, getVoltOffset()),
					 hysteresis({ 0, 4, 15, 30, 70, 100 }, 3){

	sample(true); // this will initiate shutdown if battery is critical
}

void Battery::begin(){
	start();
}

uint16_t Battery::mapRawReading(uint16_t reading){
	return std::round(map((double) reading, MIN_READ, MAX_READ, 3600, 4500));
}

int16_t Battery::getVoltOffset(){
	uint32_t upper = 0, lower = 0;
	esp_efuse_read_field_blob((const esp_efuse_desc_t**) efuse_adc1_low, &lower, 7);
	esp_efuse_read_field_blob((const esp_efuse_desc_t**) efuse_adc1_high, &upper, 9);
	return (upper << 7) | lower;
}

void Battery::sample(bool fresh){
	if(shutdown) return;

	auto oldLevel = getLevel();

	if(fresh){
		adc.resetEma();
		hysteresis.reset(adc.getVal());
	}else{
		auto val = adc.sample();
		hysteresis.update(val);
	}

	if(oldLevel != getLevel() || fresh){
		Events::post(Facility::Battery, Battery::Event{ .action = Event::LevelChange, .level = getLevel() });
	}

	if(getLevel() == Critical){
		stop(0);
		shutdown = true;
		off();
		return;
	}
}

void Battery::off(){
	// TODO: show low battery notification, then shut off
	extern void shutdown();
	shutdown();
}

void Battery::sleepyLoop(){
	if(shutdown) return;
	sample();
}

uint8_t Battery::getPerc() const{
	return adc.getVal();
}

Battery::Level Battery::getLevel() const{
	return (Level) hysteresis.get();
}

bool Battery::isShutdown() const{
	return shutdown;
}
