#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
/*
 Pisca um LED conectado no pino GPIO_18 do Kit ESP32.
*/
void blink_task(void *pvParameter)
{
    // gpio_pad_select_gpio(GPIO_NUM_18); 
    gpio_set_direction(GPIO_NUM_18,GPIO_MODE_OUTPUT);
    printf("Blinking LED on GPIO 18\n");
    int cnt=0;
    while(1) {
		gpio_set_level(GPIO_NUM_18,cnt%2); // cnt % 2 (ou seja, se cnt for par, retorna 0, caso contrário, retorna 1)
        cnt++;
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
 
void app_main()
{	
    xTaskCreate(blink_task,"blink_task",1024,NULL,1,NULL);
    printf("blink task  started\n");
} 