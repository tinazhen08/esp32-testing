#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TL1_RED GPIO_NUM_32
#define TL1_YELLOW GPIO_NUM_33
#define TL1_GREEN GPIO_NUM_25

#define TL2_RED GPIO_NUM_26
#define TL2_YELLOW GPIO_NUM_27
#define TL2_GREEN GPIO_NUM_14

#define GREEN_MS 4000
#define YELLOW_MS 1500
#define ALL_RED_MS 1000

static const char *TAG = "traffic_lights";

void set_lights(int r1, int y1, int g1, int r2, int y2, int g2)
{
    gpio_set_level(TL1_RED, r1);
    gpio_set_level(TL1_YELLOW, y1);
    gpio_set_level(TL1_GREEN, g1);

    gpio_set_level(TL2_RED, r2);
    gpio_set_level(TL2_YELLOW, y2);
    gpio_set_level(TL2_GREEN, g2);
}

void app_main(void)
{

    gpio_num_t pins[] = {TL1_RED, TL1_YELLOW, TL1_GREEN, TL2_RED, TL2_YELLOW, TL2_GREEN};
    for (int i = 0; i < 6; i++)
    {
        gpio_reset_pin(pins[i]);
        ESP_ERROR_CHECK(gpio_set_direction(pins[i], GPIO_MODE_OUTPUT));
    }

    while (1)
    {
        ESP_LOGI(TAG, "Light 1: GREEN  | Light 2: RED");
        set_lights(0, 0, 1, 1, 0, 0);
        vTaskDelay(pdMS_TO_TICKS(GREEN_MS));

        ESP_LOGI(TAG, "Light 1: YELLOW | Light 2: RED");
        set_lights(0, 1, 0, 1, 0, 0);
        vTaskDelay(pdMS_TO_TICKS(YELLOW_MS));

        ESP_LOGI(TAG, "Light 1: RED    | Light 2: RED");
        set_lights(1, 0, 0, 1, 0, 0);
        vTaskDelay(pdMS_TO_TICKS(ALL_RED_MS));

        ESP_LOGI(TAG, "Light 1: RED    | Light 2: GREEN");
        set_lights(1, 0, 0, 0, 0, 1);
        vTaskDelay(pdMS_TO_TICKS(GREEN_MS));

        ESP_LOGI(TAG, "Light 1: RED    | Light 2: YELLOW");
        set_lights(1, 0, 0, 0, 1, 0);
        vTaskDelay(pdMS_TO_TICKS(YELLOW_MS));

        ESP_LOGI(TAG, "Light 1: RED    | Light 2: RED");
        set_lights(1, 0, 0, 1, 0, 0);
        vTaskDelay(pdMS_TO_TICKS(ALL_RED_MS));
    }
}
