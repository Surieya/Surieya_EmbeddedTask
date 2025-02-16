/**
 * @file freertos_queue.c
 * @brief FreeRTOS Queue Implementation with Sender and Receiver Tasks
 *
 * This file demonstrates a simple FreeRTOS queue example where two sender tasks
 * send structured messages to a receiver task using a queue.
 *
 * @author Your Name
 * @date 2025-02-13
 */

 #include "main.h"
 #include "cmsis_os.h"
 
 /**
  * @brief FreeRTOS Queue Handle
  */
 xQueueHandle St_Queue_Handler;
 
 /**
  * @brief Task Handles
  */
 xTaskHandle Sender1_Task_Handler;
 xTaskHandle Sender2_Task_Handler;
 xTaskHandle Reciver_Task_Handler;
 
 /**
  * @struct my_struct
  * @brief Structure to hold message data
  */
 typedef struct {
     char *str;        /**< Pointer to string message */
     int counter;      /**< Counter value */
     uint16_t large_val; /**< Large numerical value */
 } my_struct;
 
 /**
  * @brief Sender1 Task Function Prototype
  * @param args Pointer to task arguments
  */
 void Sender1_Task(void *args);
 
 /**
  * @brief Sender2 Task Function Prototype
  * @param args Pointer to task arguments
  */
 void Sender2_Task(void *args);
 
 /**
  * @brief Receiver Task Function Prototype
  * @param args Pointer to task arguments
  */
 void Reciver_Task(void *args);
 
 /**
  * @brief Main function initializes the system and creates tasks and queue.
  * @return int (should never return)
  */
 int main(void) {
     HAL_Init();
     SystemClock_Config();
     MX_GPIO_Init();
     MX_USART2_UART_Init();
 
     // Create a queue with a capacity of 2 elements of type my_struct
     St_Queue_Handler = xQueueCreate(2, sizeof(my_struct));
 
     // Create sender and receiver tasks
     xTaskCreate(Sender1_Task, "Task1", 128, NULL, 2, &Sender1_Task_Handler);
     xTaskCreate(Sender2_Task, "Task2", 128, NULL, 2, &Sender2_Task_Handler);
     xTaskCreate(Reciver_Task, "Receiver", 128, NULL, 1, &Reciver_Task_Handler);
 
     // Start the FreeRTOS scheduler
     vTaskStartScheduler();
 
     while (1);
 }
 
 /**
  * @brief Sender1 Task - Sends a structured message to the queue
  * @param args Pointer to task arguments
  */
 void Sender1_Task(void *args) {
     my_struct *ptrtoStruct;
     uint32_t TickDelay = pdMS_TO_TICKS(2000);
     int indx1 = 0;
 
     while (1) {
         ptrtoStruct = pvPortMalloc(sizeof(my_struct));
 
         ptrtoStruct->counter = 1 + indx1;
         ptrtoStruct->large_val = 1000 + indx1 * 100;
         ptrtoStruct->str = "Hello from Sender 1";
 
         if (xQueueSend(St_Queue_Handler, &ptrtoStruct, portMAX_DELAY) == pdPASS) {
             char *msg = "Sent message from Sender1\n";
             HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
         }
 
         indx1++;
         vTaskDelay(TickDelay);
     }
 }
 
 /**
  * @brief Sender2 Task - Sends a structured message to the queue
  * @param args Pointer to task arguments
  */
 void Sender2_Task(void *args) {
     my_struct *ptrtoStruct;
     uint32_t TickDelay = pdMS_TO_TICKS(2000);
     int indx2 = 0;
 
     while (1) {
         ptrtoStruct = pvPortMalloc(sizeof(my_struct));
 
         ptrtoStruct->counter = 1 + indx2;
         ptrtoStruct->large_val = 1000 + indx2 * 200;
         ptrtoStruct->str = "Hello from Sender 2";
 
         if (xQueueSend(St_Queue_Handler, &ptrtoStruct, portMAX_DELAY) == pdPASS) {
             char *msg = "Sent message from Sender2\n";
             HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
         }
 
         indx2++;
         vTaskDelay(TickDelay);
     }
 }
 
 /**
  * @brief Receiver Task - Receives messages from the queue and prints them
  * @param args Pointer to task arguments
  */
 void Reciver_Task(void *args) {
     my_struct *rpttoStruct;
     uint32_t Delay = pdMS_TO_TICKS(3000);
     char *ptr;
 
     while (1) {
         if (xQueueReceive(St_Queue_Handler, &rpttoStruct, portMAX_DELAY) == pdPASS) {
             ptr = pvPortMalloc(100 * sizeof(char));
             sprintf(ptr, "Received \n Counter:%d \n Large_val:%u \n Str:%s \n\n",
                     rpttoStruct->counter, rpttoStruct->large_val, rpttoStruct->str);
             HAL_UART_Transmit(&huart2, (uint8_t*)ptr, strlen(ptr), HAL_MAX_DELAY);
             vPortFree(ptr);
         }
         vPortFree(rpttoStruct);
         vTaskDelay(Delay);
     }
 }
 