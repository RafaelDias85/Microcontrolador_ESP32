/*
    MODO STATION (Cliente)
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "freertos/event_groups.h"
// Esta biblioteca faz parte do FreeRTOS e permite o uso de grupos de eventos (event groups).
// Grupos de eventos s�o conjuntos de bits usados para sinalizar e sincronizar eventos entre diferentes tarefas no FreeRTOS.
// Eles permitem que uma ou mais tarefas esperem que certos eventos aconte�am (representados por bits sendo definidos).
// Voc� pode definir ou limpar bits de eventos, e as tarefas podem ser bloqueadas at� que os eventos desejados ocorram.
// Fun��es principais incluem xEventGroupCreate(), xEventGroupSetBits(), xEventGroupWaitBits(), entre outras.

#include "esp_wifi.h"
// Esta biblioteca cont�m todas as fun��es e defini��es relacionadas ao controle do Wi-Fi no ESP32.
// Ela permite configurar o modo de opera��o (station, access point, ou ambos), conectar-se a redes Wi-Fi,
// definir SSID e senha, gerenciar canais, controlar o estado da conex�o, e outros aspectos do Wi-Fi.
// Fun��es comuns incluem esp_wifi_init(), esp_wifi_start(), esp_wifi_connect(), entre outras.

#include "esp_event_loop.h"
// Esta biblioteca � usada para gerenciar o loop de eventos no ESP32. Quando o Wi-Fi est� ativado,
// v�rios eventos, como conex�o, desconex�o, IP atribu�do, entre outros, s�o gerados.
// O "event loop" processa e lida com esses eventos de forma ass�ncrona.
// Isso permite que o sistema reaja a mudan�as sem bloquear o fluxo principal do programa.

#include "esp_system.h"
// Fornece acesso a v�rias funcionalidades do sistema do ESP32, como informa��es de hardware,
// reinicializa��o do dispositivo, gerenciamento de mem�ria e fun��es relacionadas ao controle do sistema.
// Pode ser usada para acessar dados sobre o chip, reiniciar o dispositivo com esp_restart(),
// obter informa��es sobre a vers�o do SDK, entre outras fun��es do sistema.

#include "esp_log.h"
// Esta biblioteca � usada para gerar logs durante a execu��o do programa. � �til para depura��o e monitoramento.
// Ela permite exibir mensagens de diferentes n�veis de severidade, como: ESP_LOGI (Informa��es),
// ESP_LOGW (Avisos), ESP_LOGE (Erros) e ESP_LOGD (Depura��o).
// Usar esp_log ajuda a monitorar o comportamento do c�digo e detectar falhas ou anomalias.

#include "nvs_flash.h"
// Esta biblioteca � respons�vel pelo sistema de armazenamento n�o vol�til (NVS - Non-Volatile Storage).
// O NVS � usado para armazenar dados que devem persistir entre reinicializa��es, como configura��es de Wi-Fi ou chaves de seguran�a.
// Inclui fun��es para inicializar, ler, escrever e apagar dados armazenados na mem�ria flash do ESP32.
// Fun��es principais incluem nvs_flash_init(), nvs_open(), nvs_set(), nvs_get(), e nvs_commit().

#include "lwip/err.h"
// Faz parte do LwIP (Lightweight IP), uma biblioteca leve para gerenciamento de protocolos de rede, usada no ESP32.
// Este cabe�alho define os c�digos de erro da pilha TCP/IP para ajudar no tratamento de erros relacionados � rede.
// Os c�digos de erro s�o usados por fun��es que retornam valores para indicar falhas durante opera��es de rede, como problemas com sockets, tempo de resposta ou conex�es falhadas.

#include "lwip/sys.h"
// Tamb�m faz parte do LwIP e fornece abstra��es para fun��es de sistema usadas pela pilha TCP/IP.
// Ele lida com opera��es b�sicas como cria��o de threads, mutexes, timers, e filas de mensagens (message queues), todos usados no gerenciamento da pilha de rede.
// Fornece compatibilidade com diferentes sistemas operacionais, incluindo o FreeRTOS, para garantir que a pilha de rede funcione corretamente.

/*Define*/
#define EXAMPLE_ESP_WIFI_SSID "RAFA E IZA"
#define EXEMPLE_ESP_WIFI_PASS "03110823"

/*MACROS*/

/* Vari�veis Globais */

static EventGroupHandle_t wifi_event_group;
// Handle para o grupo de eventos do FreeRTOS que ser� utilizado para
// sincronizar eventos relacionados � conex�o WiFi. O EventGroup permite
// que v�rias tarefas possam esperar por mudan�as no estado da conex�o.

const int WIFI_CONNECTED_BIT = BIT0;
// Constante que representa um bit espec�fico no EventGroup, utilizado para
// indicar se o ESP32 est� conectado � rede WiFi. O bit � definido como BIT0,
// que corresponde ao primeiro bit em uma m�scara de bits.

static const char *TAG = "WIFI: ";
// Tag de log utilizada para identificar mensagens relacionadas � conex�o
// WiFi no console. Essa tag ajuda na depura��o, facilitando a busca por
// logs espec�ficos do m�dulo WiFi.


/*Prototipos de fun��es*/
static esp_err_t event_handler( void *ctx, system_event_t *event);
void wifi_init_sta();
void Task_IP(void *pvParameter);

void app_main(void)
{
    /*
        Inicializacao da memoria nao volatil para armazenamento de dados (Non-volatile store (NVS)).
        **Nescess�rio para realiza��o da calibra��o do PHY.
    */

    /*
        Event Group do FreeRTOS
        S� podemos enviar ou ler alguma informa��o TCP quando a rede WIFI estiver configurada, ou seja,
        somente ap�s o aceite de conexao e a libera��o do IP pelo reteador da rede (nos casos de IPs Dinamicos).
    */

    /* Configura a rede WIFI*/
}

/*Fun��es*/
