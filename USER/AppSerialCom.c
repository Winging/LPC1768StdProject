#include "AppSerialCom.h"
#include "RingBuffer.h"
#include "PacketAnalysis.h"


//声明
extern Ring_Buffer_T bufSerialRec;//串口接收缓冲区
extern OS_EVENT * semSerialCommand;//是否有串口数据包需要解析 初始为0
static void UART_IntErr(uint8_t bLSErrType);
static void UART_IntReceive(void);
/*
*@描述：初始化串口
*@参数：void
*@返回：无
*/
void InitUart(void)
{
	// UART Configuration structure variable
	UART_CFG_Type UARTConfigStruct;
	// UART FIFO configuration Struct variable
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	// Pin configuration for UART0
	PINSEL_CFG_Type PinCfg;
	/*
	 * Initialize UART pin connect
	 */
	PinCfg.OpenDrain = UARTOpendrain;
	PinCfg.Pinmode = UARTPinMode;
	PinCfg.Portnum = UARTPortTX;
	PinCfg.Pinnum = UARTPinTX;
	PinCfg.Funcnum = UARTFuncTX;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Portnum = UARTPortRX;
	PinCfg.Pinnum = UARTPinRX;
	PinCfg.Funcnum = UARTFuncRX;
	PINSEL_ConfigPin(&PinCfg);
	/* Initialize UART Configuration parameter structure to default state:
	 * Baudrate = 9600bps
	 * 8 data bit
	 * 1 Stop bit
	 * None parity
	 */
	UART_ConfigStructInit(&UARTConfigStruct);
	// Re-configure baudrate to 57600bps
	UARTConfigStruct.Baud_rate = 57600;
	// Initialize UART peripheral with given to corresponding parameter
	UART_Init((LPC_UART_TypeDef *)_LPC_UART, &UARTConfigStruct);
	/* Initialize FIFOConfigStruct to default state:
	 * 				- FIFO_DMAMode = DISABLE
	 * 				- FIFO_Level = UART_FIFO_TRGLEV0
	 * 				- FIFO_ResetRxBuf = ENABLE
	 * 				- FIFO_ResetTxBuf = ENABLE
	 * 				- FIFO_State = ENABLE
	 */
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);
	UARTFIFOConfigStruct.FIFO_Level = UART_FIFO_TRGLEV3;//8 character 
	// Initialize FIFO for UART0 peripheral
	UART_FIFOConfig((LPC_UART_TypeDef *)_LPC_UART, &UARTFIFOConfigStruct);


	// Enable UART Transmit
	UART_TxCmd((LPC_UART_TypeDef *)_LPC_UART, ENABLE);

    /* Enable UART Rx interrupt */
	UART_IntConfig((LPC_UART_TypeDef *)_LPC_UART, UART_INTCFG_RBR, ENABLE);
	/* Enable UART line status interrupt */
	UART_IntConfig((LPC_UART_TypeDef *)_LPC_UART, UART_INTCFG_RLS, DISABLE);
	/* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(_UART_IRQ, ((0x01<<3)|0x01));
	/* Enable Interrupt for UART channel */
    NVIC_EnableIRQ(_UART_IRQ);
	BufInit(&bufSerialRec);
	
}
/*
*@描述：串口中断
*@参数：void
*@返回：无
*/
void _UART_IRQHander(void)
{
	
	uint32_t intsrc, tmp, tmp1;
	//OSIntEnter();
	// Determine the interrupt source 
	intsrc = UART_GetIntId((LPC_UART_TypeDef *)_LPC_UART);
	
	tmp = intsrc & UART_IIR_INTID_MASK;
	
	// Receive Line Status
	if (tmp == UART_IIR_INTID_RLS){
		// Check line status
		tmp1 = UART_GetLineStatus((LPC_UART_TypeDef *)_LPC_UART);
		// Mask out the Receive Ready and Transmit Holding empty status
		tmp1 &= (UART_LSR_OE | UART_LSR_PE | UART_LSR_FE \
				| UART_LSR_BI | UART_LSR_RXFE);
		// If any error exist
		if (tmp1) {
				UART_IntErr(tmp1);
		}
	}

	// Receive Data Available or Character time-out
	if ((tmp == UART_IIR_INTID_RDA) || (tmp == UART_IIR_INTID_CTI)){
		UART_IntReceive();
		//UART_Receive((LPC_UART_TypeDef *)_LPC_UART,&tmpchar,1,BLOCKING);
	}

	// Transmit Holding Empty
	if (tmp == UART_IIR_INTID_THRE){
			//UART_IntTransmit();
		
	}
	//OSIntExit();
	
}

void UART_IntErr(uint8_t bLSErrType)
{
	// Loop forever
	while (1){
		// For testing purpose
	}
}

//发生接收中断时调用，基本上是发生8字节中断后调用，或者超时后调用
void UART_IntReceive(void)
{
	uint8_t rlen;//接收数据的长度
	uint8_t chars[16];
	uint8_t index = 0;	
	//接收一个字符
	rlen = UART_Receive((LPC_UART_TypeDef *)_LPC_UART,chars,16,NONE_BLOCKING);
	for(index=0;index<rlen;index++)
	{
		//my_printf("%d ",chars[index]);
		
		if(! ISBufFull(&bufSerialRec))
		{
			//如果缓冲区未满 
			BufPush(&bufSerialRec,chars[index]);
		}
		//获得包结束位
		if(chars[index] == PACKET_EOI)
		{
			//UART_Send((LPC_UART_TypeDef *)_LPC_UART,chars,index,BLOCKING);
			if(!ISBufEmpty(&bufSerialRec))
			{
				OSSemPost(semSerialCommand);
			}
		}
		
	}
}

/*
*@描述 ： 串口通信发送接口，提供给通过串口给上位机发送同样报文的接口；采用阻塞发送，因为发送数据不多
*@参数：str指向发送的字符串，len 发送的长度；
*返回：无
*/
void UartSend(uint8_t* str,uint32_t len)
{
	UART_Send((LPC_UART_TypeDef *)_LPC_UART,str,len,BLOCKING);
}

