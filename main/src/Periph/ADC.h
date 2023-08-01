#ifndef BIT_FIRMWARE_ADC_H
#define BIT_FIRMWARE_ADC_H

#include <hal/gpio_types.h>
#include <esp_adc/adc_oneshot.h>

class ADC {
public:
	// Specifying min and max maps value to [-100, +100]
	ADC(gpio_num_t pin, float ema_a = 1, int min = 0, int max = 0, int readingOffset = 0);
	virtual ~ADC();
	// Take a sample and get current value
	float sample();

	// Get current value without sampling
	float getVal() const;

	void resetEma();
	void setEmaA(float emaA);

private:
	bool valid = true;

	const gpio_num_t pin;
	float ema_a;
	const float min, max;
	const float offset;

	float val = -1;

	adc_oneshot_unit_handle_t adc1_handle;
};


#endif //BIT_FIRMWARE_ADC_H
