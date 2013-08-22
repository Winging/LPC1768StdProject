#include "emac.h"
#include "lpc17xx_emac.h"
#include "lpc17xx_pinsel.h"
#include <string.h>
#include <stdio.h>
#include "includes.h"
#include "debug_frmwrk.h"
#include "AppDebug.h"
#include "AppGlobal.h"

#include <stdio.h>
/*mac address ***************************************************************/

/* This is the MAC address of LPC17xx */
/* 0C 1D 12 E0 1F 10*/
#ifdef MCB_LPC_1768
unsigned char EMAC_ADDR0;		
unsigned char EMAC_ADDR1;		
unsigned char EMAC_ADDR2;		
unsigned char EMAC_ADDR3;		
unsigned char EMAC_ADDR4;		
unsigned char EMAC_ADDR5;		
#elif defined(IAR_LPC_1768)
unsigned char EMAC_ADDR0;		
unsigned char EMAC_ADDR1;		
unsigned char EMAC_ADDR2;		
unsigned char EMAC_ADDR3;		
unsigned char EMAC_ADDR4;		
unsigned char EMAC_ADDR5;	
#endif

/* Example group ----------------------------------------------------------- */
/** @defgroup EMAC_uIP	uIP
 * @ingroup EMAC_Examples
 * @{
 */




/* Init the LPC17xx ethernet */
BOOL_8 tapdev_init(void)
{
	/* EMAC configuration type */
	EMAC_CFG_Type Emac_Config;
	/* pin configuration */
	PINSEL_CFG_Type PinCfg;
	uint8_t EMACAddr[6];
	const uint8_t * serialMac = 0;//为了提高网络初始化的实时性，先将序列号转化为MAC地址存储在全局变量之中
	
	
#if AUTO_NEGOTIATION_ENA != 0
	Emac_Config.Mode = EMAC_MODE_AUTO;
#else
	#if (FIX_SPEED == SPEED_100)
		#if (FIX_DUPLEX == FULL_DUPLEX)
			Emac_Config.Mode = EMAC_MODE_100M_FULL;
		#elif (FIX_DUPLEX == HALF_DUPLEX)
			Emac_Config.Mode = EMAC_MODE_100M_HALF;
		#else
			#error Does not support this duplex option
		#endif
	#elif (FIX_SPEED == SPEED_10)
		#if (FIX_DUPLEX == FULL_DUPLEX)
				Emac_Config.Mode = EMAC_MODE_10M_FULL;
		#elif (FIX_DUPLEX == HALF_DUPLEX)
				Emac_Config.Mode = EMAC_MODE_10M_HALF;
		#else
			#error Does not support this duplex option
		#endif
	#else
		#error Does not support this speed option
	#endif
#endif

	/*
	 * Enable P1 Ethernet Pins:
	 * P1.0 - ENET_TXD0
	 * P1.1 - ENET_TXD1
	 * P1.4 - ENET_TX_EN
	 * P1.8 - ENET_CRS
	 * P1.9 - ENET_RXD0
	 * P1.10 - ENET_RXD1
	 * P1.14 - ENET_RX_ER
	 * P1.15 - ENET_REF_CLK
	 * P1.16 - ENET_MDC
	 * P1.17 - ENET_MDIO
	 */
	PinCfg.Funcnum = 1;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Portnum = 1;

	PinCfg.Pinnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 4;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 8;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 9;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 10;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 14;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 15;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 16;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 17;
	PINSEL_ConfigPin(&PinCfg);
	
	EMACAddr[0] = serialMac[0];
	EMACAddr[1] = serialMac[1];
	EMACAddr[2] = serialMac[2];
	EMACAddr[3] = serialMac[3];
	EMACAddr[4] = serialMac[4];
	EMACAddr[5] = serialMac[5];
	my_printf("MAC addr: %d-%d-%d-%d-%d-%d \n\r", \
			 EMACAddr[0],  EMACAddr[1],  EMACAddr[2], \
			  EMACAddr[3],  EMACAddr[4],  EMACAddr[5]);
	Emac_Config.Mode = EMAC_MODE_AUTO;
	Emac_Config.pbEMAC_Addr = EMACAddr;
	// Initialize EMAC module with given parameter
	_DBG_("INIT PINS AND PORT");
	
	if (EMAC_Init(&Emac_Config) == ERROR){
		return (FALSE);
	}
		
	_DBG_("Init EMAC complete");
	serialMac = YF_Global_GetSerialMac();
	EMAC_ADDR5 = serialMac[5];
	EMAC_ADDR4 = serialMac[4];
	EMAC_ADDR3 = serialMac[3];
	EMAC_ADDR2 = serialMac[2];
	EMAC_ADDR1 = serialMac[1];
	EMAC_ADDR0 = serialMac[0];
	
	return (TRUE);
}

/* receive an Ethernet frame from MAC/DMA controller */
UNS_32 tapdev_read(void * pPacket)
{
	UNS_32 Size = EMAC_MAX_PACKET_SIZE;
	UNS_32 in_size;
	EMAC_PACKETBUF_Type RxPack;

	// Check Receive status
	if (EMAC_CheckReceiveIndex() == FALSE){
		return (0);
	}

	// Get size of receive data
	in_size = EMAC_GetReceiveDataSize() + 1;

	Size = MIN(Size,in_size);

	// Setup Rx packet
	RxPack.pbDataBuf = (uint32_t *)pPacket;
	RxPack.ulDataLen = Size;
	EMAC_ReadPacketBuffer(&RxPack);

	// update receive status
	EMAC_UpdateRxConsumeIndex();
	return(Size);
}

/* transmit an Ethernet frame to MAC/DMA controller */
BOOL_8 tapdev_send(void *pPacket, UNS_32 size)
{
	EMAC_PACKETBUF_Type TxPack;

	// Check size
	if(size == 0){
		return(TRUE);
	}

	// check Tx Slot is available
	if (EMAC_CheckTransmitIndex() == FALSE){
		return (FALSE);
	}

	size = MIN(size,EMAC_MAX_PACKET_SIZE);

	// Setup Tx Packet buffer
	TxPack.ulDataLen = size;
	TxPack.pbDataBuf = (uint32_t *)pPacket;
	EMAC_WritePacketBuffer(&TxPack);
	EMAC_UpdateTxProduceIndex();

	return(TRUE);
}

/*
 * @}
 */
