/* Traffic Light Dashboard
You will be creating a web dashboard for N number of traffic lights.
Your project must
-Connect 2 traffic lights and change the active light in a similar (but faster) pattern to a real light.
-Communicate via MQTT to a “broker”
-The broker will communicate to a server that serves up HTML status page for the lights. You may use whatever language and framework you like for the admin dash.
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BLINK_GPIO GPIO_NUM_32
#define BLINK_PERIOD_MS 1000

static const char *TAG = "blink";

void app_main(void)
{

    gpio_reset_pin(BLINK_GPIO);
    ESP_ERROR_CHECK(gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT));

    uint32_t level = 0;
    while (1)
    {
        ESP_LOGI(TAG, "Turning the LED %s", level ? "ON" : "OFF");
        gpio_set_level(BLINK_GPIO, level);
        level = !level;
        vTaskDelay(pdMS_TO_TICKS(BLINK_PERIOD_MS));
    }
}