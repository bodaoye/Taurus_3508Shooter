#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "stm32f4xx_hal.h"
#include "usart.h"

		/* 函数声明 */
	/* 串口中断功能函数 */
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
	/* 串口空闲中断判断 */
void USER_UART_IDLECallback(UART_HandleTypeDef *huart);
	/* 串口初始化 */
void USER_UART_Init(void);

		/* 宏定义声明 */
	/* 串口号 */
#define 	DBUS_HUART      huart1
	/* 缓存区长度 */
#define  DMA_DBUS_LEN		18

#endif

