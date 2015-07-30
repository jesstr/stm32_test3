#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "main.h"


/*  USART2 global interrupt handler  */
void USART2_IRQHandler(void)
{
	// TODO check if irq is Rx
	 /* RXNE is automaticaly cleared by DMA read */
	//if ((USART3->SR & USART_FLAG_RXNE) != (u16)RESET)

	static int out_index = 0;													/* FIFO out pointer */
	int in_index = UART_RX_BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel6);	/* FIFO in pointer */
	int data_count;																/* Number of data to transfer */

	/* Calculate number of data to transfer */
	if (in_index - out_index < 0) {
		data_count = UART_RX_BUF_SIZE - out_index + in_index;
	}
	else {
		data_count = in_index - out_index;
	}

	/* Write to DMA number of data will be transfered */
	DMA1_Channel2->CNDTR = data_count;
	/* Write to DMA pointer to data will be transfered */
	/* TODO test case if out_index was overflowed */
	DMA1_Channel2->CMAR = (uint32_t)&Uart2_RxBuf[out_index];

	/* Move FIFO out index */
	out_index = in_index;

	/* Run DMA data transfer */
	DMA_Cmd(DMA1_Channel2, ENABLE);

	/* LED8 blinks on data transfer */
	LED8_ON;
}


/*  USART3 global interrupt handler  */
void USART3_IRQHandler(void)
{
	// TODO check if irq is Rx
	/* RXNE is automaticaly cleared by DMA read */
//  if ((USART3->SR & USART_FLAG_RXNE) != (u16)RESET)

	static int out_index = 0;													/* FIFO out pointer */
	int in_index = UART_RX_BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel3);	/* FIFO in pointer */
	int data_count;																/* Number of data to transfer */

	/* Calculate number of data to transfer */
	if (in_index - out_index < 0) {
		data_count = UART_RX_BUF_SIZE - out_index + in_index;
	}
	else {
		data_count = in_index - out_index;
	}

	/* Write to DMA number of data will be transfered */
	DMA1_Channel7->CNDTR = data_count;
	/* Write to DMA pointer to data will be transfered */
	DMA1_Channel7->CMAR = (uint32_t)&Uart3_RxBuf[out_index];

	/* Move FIFO out index */
	out_index = in_index;

	/* Run DMA data transfer */
	DMA_Cmd(DMA1_Channel7, ENABLE);

	/* LED9 blinks on data transfer */
	LED9_ON;
}


/* DMA1_Channel2 interrupt handler */
void DMA1_Channel2_IRQHandler(void)
{
    /* Disable DMA1_Channel2 transfer*/
    DMA_Cmd(DMA1_Channel2, DISABLE);
    /*  Clear DMA1_Channel2 Transfer Complete Flag*/
    DMA_ClearFlag(DMA1_FLAG_TC2);
    /* LED9 blinks on data transfer */
    LED8_OFF;
}


/* DMA1_Channel7 interrupt handler */
void DMA1_Channel7_IRQHandler(void)
{
    /* Disable DMA1_Channel7 transfer*/
    DMA_Cmd(DMA1_Channel7, DISABLE);
    /*  Clear DMA1_Channel7 Transfer Complete Flag*/
    DMA_ClearFlag(DMA1_FLAG_TC7);
    /* LED9 blinks on data transfer */
    LED9_OFF;
}
