#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "stm32f4xx_hal.h"
#include "usart.h"

		/* �������� */
	/* �����жϹ��ܺ��� */
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
	/* ���ڿ����ж��ж� */
void USER_UART_IDLECallback(UART_HandleTypeDef *huart);
	/* ���ڳ�ʼ�� */
void USER_UART_Init(void);

		/* �궨������ */
	/* ���ں� */
#define 	DBUS_HUART      huart1
	/* ���������� */
#define  DMA_DBUS_LEN		18

#endif

