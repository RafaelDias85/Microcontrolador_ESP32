/*
 * Exemplo de uso de GPIOs para piscar LEDs
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

/* Definição dos LEDs como GPIOs */
#define LED_1 GPIO_NUM_2  //(pino 2 para o LED 1)
#define LED_2 GPIO_NUM_25 // (pino 25 para o LED 2)

/* Máscara de seleção dos pinos de saída para LEDs */
#define GPIO_OUTPUT_PIN_SEL ((1ULL << LED_1) | (1ULL << LED_2))

/* Declaração da função da tarefa que vai controlar os LEDs */
void Task_LED(void *pvParameter);

/* Função principal que inicializa o aplicativo */
void app_main()
{
    /* Cria a tarefa que pisca os LEDs */
    xTaskCreate(Task_LED, "Task_LED", 2048, NULL, 2, NULL);
    printf("Task_LED iniciada com sucesso.\n");
}

/* Função da tarefa responsável por piscar os LEDs */
void Task_LED(void *pvParameter)
{
    int cnt = 0; // Contador para alternar o estado dos LEDs

    /* Configuração do descritor de GPIO */
    gpio_config_t io_conf; // Declara a variável que vai armazenar a configuração do GPIO

    /* Desabilita interrupções para este descritor de GPIO */
    io_conf.intr_type = GPIO_INTR_DISABLE;

    /* Configura o GPIO como saída */
    io_conf.mode = GPIO_MODE_OUTPUT;

    /* Informa os pinos (LED_1 e LED_2) que serão configurados como saída */
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;

    /*
        Configurações de Pull-Up e Pull-Down são utilizadas apenas para entradas (GPIOs de entrada).
        Como os pinos configurados são de saída, essas configurações não são necessárias e permanecem comentadas.
    */
    // io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;  // ou GPIO_PULLDOWN_ENABLE
    // io_conf.pull_up_en = GPIO_PULLUP_DISABLE;      // ou GPIO_PULLUP_ENABLE

    /* Aplica a configuração aos GPIOs especificados */
    gpio_config(&io_conf);

    /* Imprime no console uma mensagem informando que os LEDs vão piscar */
    printf("Pisca LED_1 e LED_2\n");

    /* Loop infinito para piscar os LEDs */
    while (1)
    {
        /* Define o nível lógico dos LEDs (alternando entre ligado e desligado) */
        gpio_set_level(LED_1, cnt % 2); // Define o nível do LED 1
        gpio_set_level(LED_2, cnt % 2); // Define o nível do LED 2
        cnt++;                          // Incrementa o contador para alternar o estado dos LEDs

        /* Aguarda 300 milissegundos antes de repetir o ciclo */
        vTaskDelay(300 / portTICK_PERIOD_MS);
    }
}
