#ifndef BIT_LIBRARY_BATTERY_H
#define BIT_LIBRARY_BATTERY_H

#include <hal/gpio_types.h>
#include <atomic>
#include "Util/Threaded.h"
#include "Periph/ADC.h"
#include "Util/Hysteresis.h"
#include "Periph/Timer.h"
#include <mutex>
#include <esp_efuse.h>

class Battery : private Threaded {
public:
	Battery();
	~Battery() override;
	void begin();

	enum Level { Critical = 0, VeryLow, Low, Mid, Full, COUNT };

	void setSleep(bool sleep);

	uint8_t getPerc() const;
	Level getLevel() const;

	struct Event {
		enum {
			LevelChange
		} action;
		union {
			Level level;
		};
	};

	static int16_t getVoltOffset();
	static uint16_t mapRawReading(uint16_t reading);

	bool isShutdown() const;

private:
	static constexpr uint32_t ShortMeasureIntverval = 100;
	static constexpr uint32_t LongMeasureIntverval = 6000;

	ADC adc;

	Hysteresis hysteresis;

	std::mutex mut;

	bool sleep = false;

	std::atomic_bool abortFlag = false;

	SemaphoreHandle_t sem;
	Timer timer;
	static void isr(void* arg);
	void loop() override;

	void sample(bool fresh = false);
	void startTimer();

	bool shutdown = false;

	static constexpr esp_efuse_desc_t adc1_low = { EFUSE_BLK3, 96, 7 };
	static constexpr const esp_efuse_desc_t* efuse_adc1_low[] = { &adc1_low, nullptr };
	static constexpr esp_efuse_desc_t adc1_high = { EFUSE_BLK3, 103, 9 };
	static constexpr const esp_efuse_desc_t* efuse_adc1_high[] = { &adc1_high, nullptr };

};

#endif //BIT_LIBRARY_BATTERY_H
