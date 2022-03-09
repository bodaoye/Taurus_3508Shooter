#include "bsp_uart.h"
#include "remote_msg.h"
#include "string.h"
 /** 
  * @file bsp_uart.c
  * @version 2.1
  * @date March,8th,2022
	*
  * @brief  底层串口配置
	*
  *	@author JFG
  *
 */

/* 全局变量与结构体 */
uint8_t dma_dbus_rec_buf[DMA_DBUS_LEN];

 /**
  * @brief  各个串口功能函数
  * @param 	UART_HandleTypeDef *huart
  * @retval 无
  */
void USER_UART_IDLECallback(UART_HandleTypeDef *huart) {
	
		/* DBUS串口 */
	if(huart->Instance == USART1) {
		
		rc_callback_handler(&rc, dma_dbus_rec_buf);/* 遥控器数据解算 */
		memset(dma_dbus_rec_buf, 0, DMA_DBUS_LEN);/* 清空缓存区 */
		HAL_UART_Receive_DMA(&DBUS_HUART, dma_dbus_rec_buf, DMA_DBUS_LEN);
	}
}


/**
  * @brief 串口空闲中断（需在it.c中每个串口的中断中调用该函数）
  * @param UART_HandleTypeDef *huart
  * @retval 无
  */
void USER_UART_IRQHandler(UART_HandleTypeDef *huart) {
	
	if(RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))   //判断是否是空闲中断
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart);                     //清除空闲中断标志（否则会一直不断进入中断）
		HAL_UART_DMAStop(huart);															//停止本次DMA运输
		USER_UART_IDLECallback(huart);                        //调用串口功能函数
	}
}


/**
* @brief 串口初始化:使能串口空闲中断,开启串口DMA接收
* @param  无
* @retval 无
*/
void USER_UART_Init(void) {
	
	__HAL_UART_ENABLE_IT(&DBUS_HUART, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&DBUS_HUART, dma_dbus_rec_buf, DMA_DBUS_LEN);
}

