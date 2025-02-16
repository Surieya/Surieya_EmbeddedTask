/**
 * @file binary_semaphore.c
 * @brief FreeRTOS Binary Semaphore Example
 * 
 * This file demonstrates the use of a binary semaphore in FreeRTOS 
 * with three tasks: High-Priority, Medium-Priority, and Low-Priority.
 */

 #include "cmsis_os.h"
 #include "main.h"
 
 /** @brief UART handle for debug messages */
 UART_HandleTypeDef huart2;
 
 /** @brief Task handles */
 osThreadId HighTaskHandle;
 osThreadId LowTaskHandle;
 
 /** @brief Binary Semaphore handle */
 osSemaphoreId BinSemHandle;
 
 /** Function prototypes */
 void Starthightask(void const * argument);
 void Startlowtask(void const * argument);
 
 int main(void)
 {
   /* Initialize HAL and peripherals (omitted) */
 
   /** 
    * @brief Create a binary semaphore
    */
   osSemaphoreDef(BinSem);
   BinSemHandle = osSemaphoreCreate(osSemaphore(BinSem), 1);
 
   /** 
    * @brief Create tasks with different priorities
    */
   osThreadDef(HighTask, Starthightask, osPriorityAboveNormal, 0, 128);
   HighTaskHandle = osThreadCreate(osThread(HighTask), NULL);
 
   osThreadDef(LowTask, Startlowtask, osPriorityBelowNormal, 0, 128);
   LowTaskHandle = osThreadCreate(osThread(LowTask), NULL);
 
   /* Start the RTOS scheduler */
   osKernelStart();
 
   /* Infinite loop (should never reach here) */
   while (1);
 }
 
 /**
  * @brief High-Priority Task
  *
  * This task waits for the semaphore, acquires it when available,
  * performs some actions, and then releases it.
  *
  * @param argument Unused parameter
  */
 void Starthightask(void const * argument)
 {
   for(;;)
   {
     HAL_UART_Transmit(&huart2, (uint8_t *)"Entered HighTask and waiting for Semaphore\n", 44, 100);
 
     osSemaphoreWait(BinSemHandle, osWaitForever);
 
     HAL_UART_Transmit(&huart2, (uint8_t *)"Semaphore acquired by HIGH Task\n", 34, 100);
     HAL_UART_Transmit(&huart2, (uint8_t *)"Leaving HighTask and releasing Semaphore\n\n", 46, 100);
 
     osSemaphoreRelease(BinSemHandle);
     osDelay(500);
   }
 }
 
 /**
  * @brief Low-Priority Task
  *
  * This task also waits for the semaphore, but only releases it
  * after a button press is detected.
  *
  * @param argument Unused parameter
  */
 void Startlowtask(void const * argument)
 {
   for(;;)
   {
     HAL_UART_Transmit(&huart2, (uint8_t *)"Entered LOWTask and waiting for semaphore\n", 43, 100);
 
     osSemaphoreWait(BinSemHandle, osWaitForever);
 
     HAL_UART_Transmit(&huart2, (uint8_t *)"Semaphore acquired by LOW Task\n", 33, 100);
 
     while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));  // Wait for button press
 
     HAL_UART_Transmit(&huart2, (uint8_t *)"Leaving LOWTask and releasing Semaphore\n\n", 44, 100);
 
     osSemaphoreRelease(BinSemHandle);
     osDelay(500);
   }
 }
 