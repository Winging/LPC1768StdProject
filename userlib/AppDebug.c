#include "AppDebug.h"

/* ������ض���***********************************************/
void uip_log(char *m)
{
    _DBG("uIP log message: ");
    _DBG(m);
    _DBG_("");
}

/* nxp lib ����ѡ��***********************************/
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line)
{
	
}
#endif
