/*
 *Descritor de Entrada e Saida do ESP32 com SDK IDF
 *
 */

/*Biblioteca padr�o de entrada/sa�da em C, usada para fun��es como printf(),
que permite imprimir informa��es no console. */
#include <stdio.h>

/*Cabe�alho principal do FreeRTOS, inclui defini��es b�sicas do sistema operacional
em tempo real usado para gerenciamento de tarefas, filas, e outros componentes.*/
#include "freertos/FreeRTOS.h"

/*Biblioteca espec�fica do FreeRTOS para manipula��o de tarefas,
permitindo criar, controlar e gerenciar tarefas (threads) no sistema.*/
#include "freertos/task.h"

/*Driver da ESP-IDF para controle dos GPIOs (General Purpose Input/Output),
permite configurar e manipular os pinos de entrada e sa�da do ESP32.*/
#include "driver/gpio.h"

/*Define o LED_1 como o pino GPIO 2, que ser� usado para controlar
um LED ou outro perif�rico.*/
#define LED_1 GPIO_NUM_2

/*Define o LED_2 como o pino GPIO 25, utilizado para controlar
outro LED ou perif�rico.*/
#define LED_2 GPIO_NUM_25

/*Seleciona os pinos de sa�da GPIO. A express�o (1ULL << LED_1)
desloca 1 bit para a posi��o correspondente ao n�mero do pino LED_1 (GPIO 2),
e (1ULL << LED_2) faz o mesmo para o pino LED_2 (GPIO 25).
O operador | combina os dois valores, criando um bitmask que define ambos os pinos como sa�das.*/
#define GPIO_OUTPUT_PIN_SEL ((1ULL << LED_1) | (1ULL << LED_2))

/*Define o BUTTON_1 como o pino GPIO 12, que ser� usado para
controlar um bot�o ou outro perif�rico de entrada.*/
#define BUTTON_1 GPIO_NUM_12

/*Define o BUTTON_2 como o pino GPIO 14, utilizado para controlar
outro bot�o ou perif�rico de entrada.*/
#define BUTTON_2 GPIO_NUM_14

/*Seleciona os pinos de entrada GPIO. A express�o (1ULL << BUTTON_1)
desloca 1 bit para a posi��o correspondente ao n�mero do pino BUTTON_1 (GPIO 12),
e (1ULL << BUTTON_2) faz o mesmo para o pino BUTTON_2 (GPIO 14).
O operador | combina os dois valores, criando um bitmask que define ambos os pinos como entradas.*/
#define GPIO_INPUT_PIN_SEL ((1ULL << BUTTON_1) | (1ULL << BUTTON_2))

/*Prototipo de fun��o*/
void Task_LED(void *pvParameter);

/*fun��o principal*/
void app_main(void)
{
    xTaskCreate(Task_LED, "Task_LED", 2048, NULL, 2, NULL);
    printf("Task_LED Iniciada com Sucesso\n");
}

void Task_LED(void *pvParameter)
{
    // int cnt = 0;

    gpio_config_t io_conf; // Cria a Variavel Descritora para o Drive GPIO.

    /*Configura o descritor de Outputs (leds). */
    io_conf.intr_type = GPIO_INTR_DISABLE;      // Desabilita o recurso de interrup��o neste descritor.
    io_conf.mode = GPIO_MODE_OUTPUT;            // Configura como sa�da.
    io_conf.pin_bit_mask = GPIO_OUTPUT_PIN_SEL; // Informa quais os pinos que ser�o configurado pelo Drive.
    gpio_config(&io_conf);                      // Configura as GPIOs conforme configura��o do descritor.

    /*Configura o descritor das Inputs (Bot�es)*/
    io_conf.intr_type = GPIO_INTR_DISABLE;        // Desabilita o recurso de interrup��o neste descritor.
    io_conf.mode = GPIO_MODE_INPUT;               // Configura como Entrada
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;    // Informa quais os pinos que ser�o configurados no drive
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE; // ou GPIO_PULLDOWN_ENABLE
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;      // ou GPIO_PULLUP_DISABLE
    gpio_config(&io_conf);                        // Configura as GPIOs conforme configura��o do descritor.

    printf("Pisca LED 1 e LED 2\n");

    bool led_state = false;
    bool button_last_state1 = true; // Para verificar o estado anterior do bot�o
    bool button_last_state2 = true; // Para verificar o estado anterior do bot�o
    int debounce_delay = 50;        // Dura��o do debounce em milissegundos

    while (1)
    {
        // if ((gpio_get_level(BUTTON_1) == 0) || (gpio_get_level(BUTTON_2) == 0))
        // {
        //     gpio_set_level(LED_1, cnt % 2);
        //     gpio_set_level(LED_2, cnt % 2);
        //     cnt++;
        // }

        // L� o estado atual do bot�o
        bool button_current_state = gpio_get_level(BUTTON_1);
        bool button_current_state2 = gpio_get_level(BUTTON_2);

        // Verifica se houve uma transi��o de estado do bot�o
        if (button_last_state1 && !button_current_state)
        {
            // Inverte o estado do LED
            led_state = !led_state;
            gpio_set_level(LED_1, led_state);          // Atualiza o LED com o novo estado
            vTaskDelay(pdMS_TO_TICKS(debounce_delay)); // Aguarda para evitar m�ltiplas leituras
        }

        // Verifica se houve uma transi��o de estado do bot�o
        if (button_last_state2 && !button_current_state2)
        {
            // Inverte o estado do LED
            led_state = !led_state;
            gpio_set_level(LED_2, led_state);          // Atualiza o LED com o novo estado
            vTaskDelay(pdMS_TO_TICKS(debounce_delay)); // Aguarda para evitar m�ltiplas leituras
        }

        // Armazena o estado atual do bot�o para a pr�xima verifica��o
        button_last_state1 = button_current_state;
        button_last_state2 = button_current_state2;

        // Atraso para n�o consumir CPU desnecessariamente
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
