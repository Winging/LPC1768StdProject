#ifndef __APPSERIALCOM_H__
#define __APPSERIALCOM_H__
#include "includes.h"
#define UARTNum 2
#define UARTPortRX 0
#define UARTPinRX 11
#define UARTFuncRX 1 
#define UARTPortTX 0
#define UARTPinTX 10
#define UARTFuncTX 1 
#define UARTPinMode 0
#define UARTOpendrain 0

//定义相关
#if (UARTNum == 0)
#define	_LPC_UART			LPC_UART0
#define _UART_IRQ			UART0_IRQn
#define _UART_IRQHander		UART0_IRQHandler
#elif (UARTNum == 1)
#define	_LPC_UART			LPC_UART1
#define _UART_IRQ			UART1_IRQn
#define _UART_IRQHander		UART1_IRQHandler
#elif (UARTNum == 2)
#define	_LPC_UART			LPC_UART2
#define _UART_IRQ			UART2_IRQn
#define _UART_IRQHander		UART2_IRQHandler
#elif (UARTNum == 3)
#define	_LPC_UART			LPC_UART3
#define _UART_IRQ			UART3_IRQn
#define _UART_IRQHander		UART3_IRQHandler
#endif
/*
*@描述：初始化串口
*@参数：void
*@返回：无
*/
void InitUart(void);
/*
*@描述：串口中断
*@参数：void
*@返回：无
*/
void _UART_IRQHander(void);
/*
*@描述 ： 串口通信发送接口
*@参数：str指向发送的字符串，len 发送的长度；采用阻塞发送;
*返回：无
*/
void UartSend(uint8_t* str,uint32_t len);
#endif
