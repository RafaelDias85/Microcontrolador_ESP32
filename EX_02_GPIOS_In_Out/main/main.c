#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/*
    -----------------------------------------------
    GPIO_MODE_OUTPUT       //Sa√≠da
    GPIO_MODE_INPUT        //Entrada
    GPIO_MODE_INPUT_OUTPUT //Dreno Aberto
    -----------------------------------------------
    GPIO_PULLUP_ONLY,               // Pad pull up
    GPIO_PULLDOWN_ONLY,             // Pad pull down
    GPIO_PULLUP_PULLDOWN,           // Pad pull up + pull down
    GPIO_FLOATING,                  // Pad floating
*/

/*Configurando os Pinos*/
#define LED GPIO_NUM_25
#define BUTTON GPIO_NUM_12

void Task_LED(void *pvParameter);

void app_main()
{
    xTaskCreate(Task_LED, "blink_task", 1024, NULL, 5, NULL);
    printf("Task_LED Iniciada com sucesso.\n");
}

void Task_LED(void *pvParameter)
{
    int cnt = 0;

    /* Configura a GPIO 25 como sai≠da */
    // gpio_pad_select_gpio( LED );
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);

    /* Configura a GPIO 17 como entrada */
    // gpio_pad_select_gpio( BUTTON );
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON, GPIO_PULLUP_ONLY);

    printf("Pisca LED com GPIO 25\n");

    while (1)
    {

        if (gpio_get_level(BUTTON) == 0)
        {
            gpio_set_level(LED, cnt % 2);
            cnt++;
        }

        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}