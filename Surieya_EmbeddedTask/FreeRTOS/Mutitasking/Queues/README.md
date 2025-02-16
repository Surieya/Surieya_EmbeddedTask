# FreeRTOS Queue Implementation

## Overview
This project demonstrates the implementation of a FreeRTOS queue with multiple sender tasks and a receiver task. The senders enqueue messages, and the receiver processes them sequentially. The communication occurs through a FreeRTOS queue, and messages are displayed via UART.

## Features
- FreeRTOS queue for inter-task communication
- Two sender tasks generating structured messages
- A receiver task that processes and prints messages via UART
- Dynamic memory allocation using `pvPortMalloc` and `vPortFree`
- Configurable delay between message transmissions

## Components
- **Queue:** A FreeRTOS queue (`St_Queue_Handler`) with a capacity of two elements
- **Tasks:**
  - `Sender1_Task`: Sends messages with incrementing values
  - `Sender2_Task`: Sends messages with different incrementing values
  - `Reciver_Task`: Receives messages and prints them via UART

## Hardware Requirements
- STM32 microcontroller (tested on STM32F4 series)
- UART communication setup

## Software Requirements
- FreeRTOS
- STM32 HAL libraries

## Implementation Details
### Queue Data Structure
```c
typedef struct{
    char *str;
    int counter;
    uint16_t large_val;
} my_struct;
```
### Task Execution Flow
1. `Sender1_Task` and `Sender2_Task` allocate memory and populate the structure.
2. The message is enqueued using `xQueueSend`.
3. `Reciver_Task` dequeues the message, processes it, prints via UART, and frees allocated memory.

## UART Output Example
```
Sent message from Sender1
Sent message from Sender2
Received
Counter: 1
Large_val: 1000
Str: Hello from Sender 1

Received
Counter: 1
Large_val: 1000
Str: Hello from Sender 2
```

## How to Run
1. Initialize hardware and peripherals.
2. Compile and flash the firmware onto the STM32 board.
3. Monitor UART output using a terminal emulator.

## Possible Enhancements
- Implement memory allocation checks to prevent failures
- Add message prioritization
- Use static memory allocation for efficiency
