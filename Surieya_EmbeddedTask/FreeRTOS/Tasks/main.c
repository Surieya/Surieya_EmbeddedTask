#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_hal.h" // Include the HAL driver for your STM32 MCU (adjust as per your STM32 series)

// Task handle for the created task
TaskHandle_t myTaskHandle = NULL;

// Function prototype
void MyTaskFunction(void *pvParameters){
   int cnt = (int*) pvParameters;
   while(1){
     printf("hello World! : %d\r\n",count++);
     //task Delay 1s
     vTaskDelay(1000);
     
     
     
     if(cnt == 150){
        vTaskDelete(myTaskHandle);
     }
     
     
   }
}

int main(void)
{
    
    int pass = 100;
    xTaskCreate(MyTaskFunction, "MyTask", 128, (void*) pass, tskIDLE_PRIORITY, &myTaskHandle)
    vTaskStartScheduler();
    
 } 