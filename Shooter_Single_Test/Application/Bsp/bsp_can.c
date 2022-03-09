/**
  * @file bap_can.h
  * @version 2.1
  * @date March,8th,2022
  *
  * @brief  底层can通讯的配置，包括发送数据帧，CAN滤波组，接受中断回调函数
  *
  *	@author JFG
  *
  */
#include "can.h"


CAN_TxHeaderTypeDef Tx1Message;
CAN_RxHeaderTypeDef Rx1Message;

uint8_t CAN1_Rx_data[8];
uint8_t CAN1_Tx_data[8];


/**
  * @brief     CAN接受中断回调函数
  * @param     CAN_Rx_data ：CAN节点反馈的数据帧
  * @attention 
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan == &hcan1)
	{
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &Rx1Message, CAN1_Rx_data);
		switch (Rx1Message.StdId)
		{
			
		}
		__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	}

}

/**
  * @brief  send calculated current to motor
  * @param  CAN1 motor current
  */
void can1_send_message(int16_t TX_ID, int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{
	uint8_t FreeTxNum = 0; 
	
	Tx1Message.StdId = TX_ID;
	Tx1Message.IDE 	 = CAN_ID_STD;
	Tx1Message.RTR   = CAN_RTR_DATA;
  Tx1Message.DLC   = 0x08;

	CAN1_Tx_data[0] = iq1 >> 8;
	CAN1_Tx_data[1] = iq1;
	CAN1_Tx_data[2] = iq2 >> 8 ;
	CAN1_Tx_data[3] = iq2;
	CAN1_Tx_data[4] = iq3 >> 8;
	CAN1_Tx_data[5] = iq3;
	CAN1_Tx_data[6] = iq4 >> 8;
	CAN1_Tx_data[7] = iq4;
	
	/* 查询发送邮箱是否为空 */
	FreeTxNum = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);  
	while(FreeTxNum == 0) 
	{  
    FreeTxNum = HAL_CAN_GetTxMailboxesFreeLevel(&hcan1);  
  }
	
	HAL_CAN_AddTxMessage(&hcan1, &Tx1Message, CAN1_Tx_data, (uint32_t*)CAN_TX_MAILBOX0);
}

/**
  * @brief  init the can transmit and receive
  * @param  None
  */
void can_device_init(void)
{
  /* can filter config */
  CAN_FilterTypeDef  can_filter;

	can_filter.FilterBank           = 0;
  can_filter.FilterMode           = CAN_FILTERMODE_IDMASK;
  can_filter.FilterScale          = CAN_FILTERSCALE_32BIT;
  can_filter.FilterIdHigh         = 0x0000;
  can_filter.FilterIdLow          = 0x0000;
  can_filter.FilterMaskIdHigh     = 0x0000;
  can_filter.FilterMaskIdLow      = 0x0000;
  can_filter.FilterFIFOAssignment = CAN_FilterFIFO0;
	can_filter.SlaveStartFilterBank = 0;  
  can_filter.FilterActivation     = ENABLE;

  HAL_CAN_ConfigFilter(&hcan1, &can_filter);
  while (HAL_CAN_ConfigFilter(&hcan1, &can_filter) != HAL_OK);

  can_filter.FilterBank           = 14;

	HAL_Delay(100);

	/* start the can transmit and receive */
	HAL_CAN_Start(&hcan1);
 	HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);

}
