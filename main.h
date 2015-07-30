#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define LED9_ON		GPIOC->BSRR = GPIO_Pin_9; 	/*LED9 switch on, connected to PC9 */
#define LED9_OFF	GPIOC->BRR = GPIO_Pin_9;	/*LED9 switch off, connected to PC9 */
#define LED8_ON		GPIOC->BSRR = GPIO_Pin_8;	/*LED8 switch on, connected to PC9 */
#define LED8_OFF	GPIOC->BRR = GPIO_Pin_8;	/*LED8 switch off, connected to PC9 */

#define UART_RX_BUF_SIZE	64	/* UARTs Rx FIFO buffer size */


extern unsigned char Uart2_RxBuf[UART_RX_BUF_SIZE]; /* UART2 Rx FIFO buffer */
extern unsigned char Uart3_RxBuf[UART_RX_BUF_SIZE]; /* UART3 Rx FIFO buffer */


#endif /* __MAIN_H */
