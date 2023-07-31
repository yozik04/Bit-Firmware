#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void init(){
	printf("hello world\n");
}

extern "C" void app_main(void){
	init();

	vTaskDelete(nullptr);
}
