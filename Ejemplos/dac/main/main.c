#include <stdio.h>
//incluimos las librerias de los perifericos
#include "driver/gpio.h"
#include "driver/dac_common.h"
//incluimos las librerias del rtos
#include "freertos/Freertos.h"
#include "freertos/task.h"

#define LED 2

uint8_t led_value=0;
uint8_t dac_value=0;
uint8_t signal_noise[153] = { 129,160,124,156,185,148,180,207,170,202,227,187,219,241,200,232,250,207,238,252,208,237,249,202,231,239,191,219,223,174,201,203,153,180,179,129,156,154,104,132,127,78,107,102,54,85,79,33,66,60,17,52,47,6,43,39,0,41,37,2,45,41,9,55,52,22,70,67,41,90,87,63,114,111,88,140,135,113,166,160,139,191,183,162,214,203,182,232,218,197,246,229,207,254,233,210,255,231,208,250,223,199,239,209,184,223,190,165,203,167,143,179,142,118,154,116,93,129,90,69,105,66,48,84,46,30,68,30,18,57,20,11,52,16,11,53,18,17,60,27,29,74,41,46,92,60,68,114,82,92,138,106,118};

esp_err_t Init_Config(void);
esp_err_t dac_gpio(void);
void app_main(void)
{

    Init_Config();

    for (;;)
    {
       

        for(dac_value=0;dac_value<153;dac_value++){
            
            vTaskDelay(12/portTICK_PERIOD_MS);
            dac_output_voltage(DAC_CHANNEL_1,signal_noise[dac_value]);
         }
         dac_gpio();
    }
    

}
esp_err_t Init_Config(void){

gpio_reset_pin(2);
gpio_set_direction(2,GPIO_MODE_OUTPUT);
dac_output_enable(DAC_CHANNEL_1);

return ESP_OK;
}
esp_err_t dac_gpio(void){
    led_value = !led_value;
   // dac_value = ~dac_value;

    gpio_set_level(2,led_value);

   

   return ESP_OK; 
}