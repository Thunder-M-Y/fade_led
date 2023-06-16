#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "driver/gpio.h"


#define LED_PIN GPIO_NUM_4
#define LED_SPEED_MODE LEDC_LOW_SPEED_MODE
#define LED_CHANNEL LEDC_CHANNEL_0
void app_main(void)
{
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // pwm
    ledc_timer_config_t timer_cnf={0};
    timer_cnf.speed_mode = LEDC_LOW_SPEED_MODE;
    timer_cnf.duty_resolution = LEDC_TIMER_13_BIT;
    timer_cnf.timer_num = LEDC_TIMER_0;
    timer_cnf.freq_hz = 1000;
    ledc_timer_config(&timer_cnf);

    ledc_channel_config_t pwm_cnf={0};
    pwm_cnf.speed_mode = LEDC_LOW_SPEED_MODE;
    pwm_cnf.timer_sel = LEDC_TIMER_0;
    pwm_cnf.channel = LEDC_CHANNEL_0;
    pwm_cnf.gpio_num = LED_PIN;
    ledc_channel_config(&pwm_cnf);

    ledc_fade_func_install(0);
    while (1)
    {
        ledc_set_fade_with_time(LED_SPEED_MODE, LED_CHANNEL, 8192, 4000);
        ledc_fade_start(LED_SPEED_MODE, LED_CHANNEL, LEDC_FADE_WAIT_DONE);
        vTaskDelay(pdMS_TO_TICKS(2000));

        ledc_set_fade_with_time(LED_SPEED_MODE, LED_CHANNEL, 0, 4000);
        ledc_fade_start(LED_SPEED_MODE, LED_CHANNEL, LEDC_FADE_WAIT_DONE);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}