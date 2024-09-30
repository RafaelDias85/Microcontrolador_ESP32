#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Definição dos pinos dos LEDs
#define LED_1 GPIO_NUM_33
#define LED_2 GPIO_NUM_25
// Máscara de seleção dos pinos de saída (LEDs)
#define GPIO_OUTPUT_PIN_SEL ((1ULL << LED_1) | (1ULL << LED_2))

// Definição dos pinos dos botões (BT_1 e BT_2)
#define BT_1 GPIO_NUM_12
#define BT_2 GPIO_NUM_14
// Máscara de seleção dos pinos de entrada (botões)
#define GPIO_INPUT_PIN_SEL ((1ULL << BT_1) | (1ULL << BT_2))

// Definição da flag padrão de interrupção
#define ESP_INTR_FLAG_DEFAULT 0

// Variáveis voláteis usadas como contadores para os botões
volatile int cnt_1 = 0;
volatile int cnt_2 = 0;

// Protótipos das funções
static void IRAM_ATTR gpio_isr_handler(void *arg); // Handler de interrupção de GPIO
void Task_LED(void *pvParameter);                  // Função da task que controla os LEDs

// Função principal (entry point do programa)
void app_main(void)
{
    // Criação da task "Task_LED" com uma pilha de 2048 bytes, prioridade 3
    xTaskCreate(Task_LED, "Task_LED", 2048, NULL, 3, NULL);
    printf("Task_LED Iniciada com sucesso\n");
}

// Função que trata a interrupção (ISR) dos botões
static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    // Verifica se a interrupção foi causada pelo botão BT_1
    if (BT_1 == (uint32_t)arg)
    {
        // Se o nível do pino for 0 (botão pressionado)
        if (gpio_get_level((uint32_t)arg) == 0)
        {
            // Alterna o estado do LED_1 com base no contador cnt_1 (usando módulo 2)
            gpio_set_level(LED_1, cnt_1 % 2);
        }
    }
    // Verifica se a interrupção foi causada pelo botão BT_2
    else if (BT_2 == (uint32_t)arg)
    {
        // Se o nível do pino for 0 (botão pressionado)
        if (gpio_get_level((uint32_t)arg) == 0)
        {
            // Alterna o estado do LED_2 com base no contador cnt_2 (usando módulo 2)
            gpio_set_level(LED_2, cnt_2 % 2);
        }
    }
    // Incrementa os contadores para cada acionamento de botão
    cnt_1++;
    cnt_2++;
}

// Task que configura os LEDs e botões, além de gerenciar o loop de controle dos LEDs
void Task_LED(void *pvParameter)
{
    // Configuração dos pinos de saída (LEDs)
    gpio_config_t io_config = {
        .intr_type = GPIO_INTR_DISABLE,     // Desabilita interrupções
        .mode = GPIO_MODE_OUTPUT,           // Define o modo de operação como saída
        .pin_bit_mask = GPIO_OUTPUT_PIN_SEL // Seleciona os pinos a serem configurados como saída
    };
    gpio_config(&io_config); // Aplica a configuração dos LEDs

    // Configuração dos pinos de entrada (botões)
    gpio_config_t io_config2 = {
        .intr_type = GPIO_INTR_NEGEDGE,        // Interrupção na borda de descida (quando o botão é pressionado)
        .mode = GPIO_MODE_INPUT,               // Define o modo de operação como entrada
        .pin_bit_mask = GPIO_INPUT_PIN_SEL,    // Seleciona os pinos a serem configurados como entrada
        .pull_down_en = GPIO_PULLDOWN_DISABLE, // Desabilita pull-down (não necessário)
        .pull_up_en = GPIO_PULLUP_ENABLE       // Habilita pull-up interno (mantém o pino em nível alto quando o botão não está pressionado)
    };
    gpio_config(&io_config2); // Aplica a configuração dos botões

    // Instala o serviço de interrupção para os GPIOs
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

    // Adiciona o manipulador de interrupção para o botão BT_1
    gpio_isr_handler_add(BT_1, gpio_isr_handler, (void *)BT_1);

    // Adiciona o manipulador de interrupção para o botão BT_2
    gpio_isr_handler_add(BT_2, gpio_isr_handler, (void *)BT_2);

    printf("Pisca LED_1 e LED_2 \n");

    // Loop infinito para manter a task ativa (no caso, faz um delay de 300 ms repetidamente)
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(30)); // Delay de 300 ms para evitar sobrecarregar o sistema
    }
}
