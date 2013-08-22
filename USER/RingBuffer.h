#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__
#include "includes.h"
#ifndef RING_BUFSIZE
#define RING_BUFSIZE 512
#endif
typedef struct
{
	__IO uint32_t head;                /*!< UART  ring buffer head index */
    __IO uint32_t tail;                /*!< UART  ring buffer tail index */
	     uint8_t  buf[RING_BUFSIZE];  /*!< UART  data ring buffer */
} Ring_Buffer_T;
static __INLINE void BufInit(Ring_Buffer_T * buffer)
{
	buffer->head = 0;
	buffer->tail = 0;
}
static __INLINE uint8_t ISBufFull(Ring_Buffer_T * buffer)
{
	
	return (((buffer->tail +1)%RING_BUFSIZE) == buffer->head)?1:0;
}
static __INLINE uint8_t ISBufEmpty(Ring_Buffer_T * buffer)
{
	
	return (((buffer->head)%RING_BUFSIZE) == buffer->tail)?1:0;
}
static __INLINE void BufPush(Ring_Buffer_T * buffer,uint8_t ch)
{
	buffer->buf[buffer->tail] = ch;
	buffer->tail = buffer->tail + 1;
	if(buffer->tail>=RING_BUFSIZE) buffer->tail =0;
}
static __INLINE uint8_t BufPop(Ring_Buffer_T * buffer)
{
	uint8_t ch;
	ch = buffer->buf[buffer->head];
	buffer->head = buffer->head + 1;
	if(buffer->head>=RING_BUFSIZE) buffer->head = 0;
	return ch;
}
static __INLINE uint32_t BufLen(Ring_Buffer_T * buffer)
{
	if(buffer->tail>buffer->head)
		return (buffer->tail-buffer->head);
	else 
		return (buffer->head - buffer->tail);
}
#endif
