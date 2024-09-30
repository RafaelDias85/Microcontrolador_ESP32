#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_1 GPIO_NUM_2
#define LED_2 GPIO_NUM_25
#define GPIO_OUTPUT_PIN_SEL ((1ULL << LED_1) | (1ULL << LED_2))

#define BUTTON_1 GPIO_NUM_12
#define BUTTON_2 GPIO_NUM_14
#define GPIO_INPUT_PIN_SEL ((1ULL << BUTTON_1) | (1ULL << BUTTON_2))

#define ESP_INTR_FLAG_DEFAULT 0

volatile int cnt = 0;

void Task_LED(void *pvParameter);
static void IRAM_ATTR gpio_isr_handler(void *arg);

void app_main(void)
{
    xTaskCreate(Task_LED, "Task_LED", 2048, NULL, 2, NULL);
    printf("Task_LED Iniciada com sucesso");
}

/*Cada vez */
static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    // identifica qual botão foi precionado
    if (BUTTON_1 == (uint32_t)arg)
    {
        // caso o BUTTON_1 estiver precionado, faz a leitura e o acionamento do led.
        if (gpio_get_level((uint32_t)arg) == 0)
        {
            gpio_set_level(LED_1, cnt % 2);
        }
    }
    else if (BUTTON_2 == (uint32_t)arg)
    {
        if (gpio_get_level((uint32_t)arg) == 0)
        {
            gpio_set_level(LED_2, cnt % 2);
        }
    }
    cnt++;
}

void Task_LED(void *pvParameter)
{
    gpio_config_t io_conf;

    // configura os leds como saida
    io_conf.intr_type = GPIO_INTR_DISABLE; // Desabilita o recurso de interrupção neste descritor.
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;
    gpio_config(&io_conf);

    /*
    GPIO_INTR_DESABLE = 0,  /!< Disable GPIO interrupt
    GPIO_INTR_POSEDGE = 1,  /!< GPIO interrupt type : rising edge - borda ascendente
    GPIO_INTR_NEGEDGE = 2,  /!< GPIO interrupt type : falling edge - borda descendente
    GPIO_INTR_AMYEDGE = 3,  /!< GPIO interrupt tupe : both rising and falling edge - borda ascendente e descendente
    */

    // configura o descritor das Entradas (Botoes)
    io_conf.intr_type = GPIO_INTR_NEGEDGE; // interrupção externa das GPIOs habilitada e conf. para disparo na descida
    io_conf.mode = GPIO_MODE_INPUT;        // configura como saida
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    /*
     *habilita a interrupção externa das GPIOs.
     *Ao utilizar a função gpio_install_isr_service todas as interrupções de GPIO do descritor vão chamar a mesma
     *iunterrupção. A função de callback (retornos de chamada) que será chamada ára cada interrupção é definida em
     *gpio_isr_handler_add.
     *O flag ESP_INTR_FLAG_DEFALT tem a ver com a alocação do vetor de interrupção, que neste caso o valor Zero
     *(0) informa para alocar no setor de interrupção não compartilhado de nível 1, 2 e 3.
     */

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // Registra a interrupção externa de BUTTON_1
    gpio_isr_handler_add(BUTTON_1, gpio_isr_handler, (void *)BUTTON_1);

    // Registra a interrupção externa de BUTTON_2
    gpio_isr_handler_add(BUTTON_2, gpio_isr_handler, (void *)BUTTON_2);

    printf("Interrupcao das GPIOs configurada. \n");

    while (1)
    {
        /*Aguardando a interrupção das gpios serem geradas */
        vTaskDelay(pdMS_TO_TICKS(30));
    }
}
