/*
    MODO STATION (Cliente)
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "freertos/event_groups.h"
// Esta biblioteca faz parte do FreeRTOS e permite o uso de grupos de eventos (event groups).
// Grupos de eventos são conjuntos de bits usados para sinalizar e sincronizar eventos entre diferentes tarefas no FreeRTOS.
// Eles permitem que uma ou mais tarefas esperem que certos eventos aconteçam (representados por bits sendo definidos).
// Você pode definir ou limpar bits de eventos, e as tarefas podem ser bloqueadas até que os eventos desejados ocorram.
// Funções principais incluem xEventGroupCreate(), xEventGroupSetBits(), xEventGroupWaitBits(), entre outras.

#include "esp_wifi.h"
// Esta biblioteca contém todas as funções e definições relacionadas ao controle do Wi-Fi no ESP32.
// Ela permite configurar o modo de operação (station, access point, ou ambos), conectar-se a redes Wi-Fi,
// definir SSID e senha, gerenciar canais, controlar o estado da conexão, e outros aspectos do Wi-Fi.
// Funções comuns incluem esp_wifi_init(), esp_wifi_start(), esp_wifi_connect(), entre outras.

#include "esp_event_loop.h"
// Esta biblioteca é usada para gerenciar o loop de eventos no ESP32. Quando o Wi-Fi está ativado,
// vários eventos, como conexão, desconexão, IP atribuído, entre outros, são gerados.
// O "event loop" processa e lida com esses eventos de forma assíncrona.
// Isso permite que o sistema reaja a mudanças sem bloquear o fluxo principal do programa.

#include "esp_system.h"
// Fornece acesso a várias funcionalidades do sistema do ESP32, como informações de hardware,
// reinicialização do dispositivo, gerenciamento de memória e funções relacionadas ao controle do sistema.
// Pode ser usada para acessar dados sobre o chip, reiniciar o dispositivo com esp_restart(),
// obter informações sobre a versão do SDK, entre outras funções do sistema.

#include "esp_log.h"
// Esta biblioteca é usada para gerar logs durante a execução do programa. É útil para depuração e monitoramento.
// Ela permite exibir mensagens de diferentes níveis de severidade, como: ESP_LOGI (Informações),
// ESP_LOGW (Avisos), ESP_LOGE (Erros) e ESP_LOGD (Depuração).
// Usar esp_log ajuda a monitorar o comportamento do código e detectar falhas ou anomalias.

#include "nvs_flash.h"
// Esta biblioteca é responsável pelo sistema de armazenamento não volátil (NVS - Non-Volatile Storage).
// O NVS é usado para armazenar dados que devem persistir entre reinicializações, como configurações de Wi-Fi ou chaves de segurança.
// Inclui funções para inicializar, ler, escrever e apagar dados armazenados na memória flash do ESP32.
// Funções principais incluem nvs_flash_init(), nvs_open(), nvs_set(), nvs_get(), e nvs_commit().

#include "lwip/err.h"
// Faz parte do LwIP (Lightweight IP), uma biblioteca leve para gerenciamento de protocolos de rede, usada no ESP32.
// Este cabeçalho define os códigos de erro da pilha TCP/IP para ajudar no tratamento de erros relacionados à rede.
// Os códigos de erro são usados por funções que retornam valores para indicar falhas durante operações de rede, como problemas com sockets, tempo de resposta ou conexões falhadas.

#include "lwip/sys.h"
// Também faz parte do LwIP e fornece abstrações para funções de sistema usadas pela pilha TCP/IP.
// Ele lida com operações básicas como criação de threads, mutexes, timers, e filas de mensagens (message queues), todos usados no gerenciamento da pilha de rede.
// Fornece compatibilidade com diferentes sistemas operacionais, incluindo o FreeRTOS, para garantir que a pilha de rede funcione corretamente.

/*Define*/
#define EXAMPLE_ESP_WIFI_SSID "RAFA E IZA"
#define EXEMPLE_ESP_WIFI_PASS "03110823"

/*MACROS*/

/* Variáveis Globais */

static EventGroupHandle_t wifi_event_group;
// Handle para o grupo de eventos do FreeRTOS que será utilizado para
// sincronizar eventos relacionados à conexão WiFi. O EventGroup permite
// que várias tarefas possam esperar por mudanças no estado da conexão.

const int WIFI_CONNECTED_BIT = BIT0;
// Constante que representa um bit específico no EventGroup, utilizado para
// indicar se o ESP32 está conectado à rede WiFi. O bit é definido como BIT0,
// que corresponde ao primeiro bit em uma máscara de bits.

static const char *TAG = "WIFI: ";
// Tag de log utilizada para identificar mensagens relacionadas à conexão
// WiFi no console. Essa tag ajuda na depuração, facilitando a busca por
// logs específicos do módulo WiFi.


/*Prototipos de funções*/
static esp_err_t event_handler( void *ctx, system_event_t *event);
void wifi_init_sta();
void Task_IP(void *pvParameter);

void app_main(void)
{
    /*
        Inicializacao da memoria nao volatil para armazenamento de dados (Non-volatile store (NVS)).
        **Nescessário para realização da calibração do PHY.
    */

    /*
        Event Group do FreeRTOS
        Só podemos enviar ou ler alguma informação TCP quando a rede WIFI estiver configurada, ou seja,
        somente após o aceite de conexao e a liberação do IP pelo reteador da rede (nos casos de IPs Dinamicos).
    */

    /* Configura a rede WIFI*/
}

/*Funções*/
