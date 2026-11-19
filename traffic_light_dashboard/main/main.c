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
#include "sdkconfig.h"

#define RED_LIGHT_PIN 2
#define YELLOW_LIGHT_PIN 4
#define GREEN_LIGHT_PIN 5

void app_main(void)
{
    gpio_pad_select_gpio(RED_LIGHT_PIN);
    gpio_set_direction(RED_LIGHT_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(YELLOW_LIGHT_PIN);
    gpio_set_direction(YELLOW_LIGHT_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(GREEN_LIGHT_PIN);
    gpio_set_direction(GREEN_LIGHT_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        // Turn on red light
        printf("Red light is on\n");
        gpio_set_level(RED_LIGHT_PIN, 1);
        gpio_set_level(YELLOW_LIGHT_PIN, 0);
        gpio_set_level(GREEN_LIGHT_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(5000));

        // Turn on yellow light
        printf("Yellow light is on\n");
        gpio_set_level(RED_LIGHT_PIN, 0);
        gpio_set_level(YELLOW_LIGHT_PIN, 1);
        gpio_set_level(GREEN_LIGHT_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));

        // Turn on green light
        printf("Green light is on\n");
        gpio_set_level(RED_LIGHT_PIN, 0);
        gpio_set_level(YELLOW_LIGHT_PIN, 0);
        gpio_set_level(GREEN_LIGHT_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

int main()
{
    app_main();
    return 0;
}
