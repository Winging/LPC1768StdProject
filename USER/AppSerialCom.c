#include "AppSerialCom.h"
#include "RingBuffer.h"
#include "PacketAnalysis.h"


//����
extern Ring_Buffer_T bufSerialRec;//���ڽ��ջ�����
extern OS_EVENT * semSerialCommand;//�Ƿ��д������ݰ���Ҫ���� ��ʼΪ0
static void UART_IntErr(uint8_t bLSErrType);
static void UART_IntReceive(void);
/*
*@��������ʼ������
*@������void
*@���أ���
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
*@�����������ж�
*@������void
*@���أ���
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

//���������ж�ʱ���ã��������Ƿ���8�ֽ��жϺ���ã����߳�ʱ�����
void UART_IntReceive(void)
{
	uint8_t rlen;//�������ݵĳ���
	uint8_t chars[16];
	uint8_t index = 0;	
	//����һ���ַ�
	rlen = UART_Receive((LPC_UART_TypeDef *)_LPC_UART,chars,16,NONE_BLOCKING);
	for(index=0;index<rlen;index++)
	{
		//my_printf("%d ",chars[index]);
		
		if(! ISBufFull(&bufSerialRec))
		{
			//���������δ�� 
			BufPush(&bufSerialRec,chars[index]);
		}
		//��ð�����λ
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
*@���� �� ����ͨ�ŷ��ͽӿڣ��ṩ��ͨ�����ڸ���λ������ͬ�����ĵĽӿڣ������������ͣ���Ϊ�������ݲ���
*@������strָ���͵��ַ�����len ���͵ĳ��ȣ�
*���أ���
*/
void UartSend(uint8_t* str,uint32_t len)
{
	UART_Send((LPC_UART_TypeDef *)_LPC_UART,str,len,BLOCKING);
}

