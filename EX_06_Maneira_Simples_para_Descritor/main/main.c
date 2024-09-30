#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Defini��o dos pinos dos LEDs
#define LED_1 GPIO_NUM_33
#define LED_2 GPIO_NUM_25
// M�scara de sele��o dos pinos de sa�da (LEDs)
#define GPIO_OUTPUT_PIN_SEL ((1ULL << LED_1) | (1ULL << LED_2))

// Defini��o dos pinos dos bot�es (BT_1 e BT_2)
#define BT_1 GPIO_NUM_12
#define BT_2 GPIO_NUM_14
// M�scara de sele��o dos pinos de entrada (bot�es)
#define GPIO_INPUT_PIN_SEL ((1ULL << BT_1) | (1ULL << BT_2))

// Defini��o da flag padr�o de interrup��o
#define ESP_INTR_FLAG_DEFAULT 0

// Vari�veis vol�teis usadas como contadores para os bot�es
volatile int cnt_1 = 0;
volatile int cnt_2 = 0;

// Prot�tipos das fun��es
static void IRAM_ATTR gpio_isr_handler(void *arg); // Handler de interrup��o de GPIO
void Task_LED(void *pvParameter);                  // Fun��o da task que controla os LEDs

// Fun��o principal (entry point do programa)
void app_main(void)
{
    // Cria��o da task "Task_LED" com uma pilha de 2048 bytes, prioridade 3
    xTaskCreate(Task_LED, "Task_LED", 2048, NULL, 3, NULL);
    printf("Task_LED Iniciada com sucesso\n");
}

// Fun��o que trata a interrup��o (ISR) dos bot�es
static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    // Verifica se a interrup��o foi causada pelo bot�o BT_1
    if (BT_1 == (uint32_t)arg)
    {
        // Se o n�vel do pino for 0 (bot�o pressionado)
        if (gpio_get_level((uint32_t)arg) == 0)
        {
            // Alterna o estado do LED_1 com base no contador cnt_1 (usando m�dulo 2)
            gpio_set_level(LED_1, cnt_1 % 2);
        }
    }
    // Verifica se a interrup��o foi causada pelo bot�o BT_2
    else if (BT_2 == (uint32_t)arg)
    {
        // Se o n�vel do pino for 0 (bot�o pressionado)
        if (gpio_get_level((uint32_t)arg) == 0)
        {
            // Alterna o estado do LED_2 com base no contador cnt_2 (usando m�dulo 2)
            gpio_set_level(LED_2, cnt_2 % 2);
        }
    }
    // Incrementa os contadores para cada acionamento de bot�o
    cnt_1++;
    cnt_2++;
}

// Task que configura os LEDs e bot�es, al�m de gerenciar o loop de controle dos LEDs
void Task_LED(void *pvParameter)
{
    // Configura��o dos pinos de sa�da (LEDs)
    gpio_config_t io_config = {
        .intr_type = GPIO_INTR_DISABLE,     // Desabilita interrup��es
        .mode = GPIO_MODE_OUTPUT,           // Define o modo de opera��o como sa�da
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL // Seleciona os pinos a serem configurados como sa�da
    };
    gpio_config(&io_config); // Aplica a configura��o dos LEDs

    // Configura��o dos pinos de entrada (bot�es)
    gpio_config_t io_config2 = {
        .intr_type = GPIO_INTR_NEGEDGE,        // Interrup��o na borda de descida (quando o bot�o � pressionado)
        .mode = GPIO_MODE_INPUT,               // Define o modo de opera��o como entrada
        .pin_bit_mask = GPIO_INPUT_PIN_SEL,    // Seleciona os pinos a serem configurados como entrada
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // Desabilita pull-down (n�o necess�rio)
        .pull_up_en = GPIO_PULLUP_ENABLE       // Habilita pull-up interno (mant�m o pino em n�vel alto quando o bot�o n�o est� pressionado)
    };
    gpio_config(&io_config2); // Aplica a configura��o dos bot�es

    // Instala o servi�o de interrup��o para os GPIOs
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // Adiciona o manipulador de interrup��o para o bot�o BT_1
    gpio_isr_handler_add(BT_1, gpio_isr_handler, (void *)BT_1);

    // Adiciona o manipulador de interrup��o para o bot�o BT_2
    gpio_isr_handler_add(BT_2, gpio_isr_handler, (void *)BT_2);

    printf("Pisca LED_1 e LED_2 \n");

    // Loop infinito para manter a task ativa (no caso, faz um delay de 300 ms repetidamente)
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(30)); // Delay de 300 ms para evitar sobrecarregar o sistema
    }
}
