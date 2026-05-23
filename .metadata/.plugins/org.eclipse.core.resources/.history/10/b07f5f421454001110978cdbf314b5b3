#ifndef INC_STM32L476XX_UART_DRIVER_H_
#define INC_STM32L476XX_UART_DRIVER_H_

/* CR1 */

#define USART_CR1_UE_Pos        0
#define USART_CR1_RE_Pos        2
#define USART_CR1_TE_Pos        3

/* ISR */

#define USART_ISR_TXE_Pos       7
#define USART_ISR_TC_Pos        6
#define USART_ISR_RXNE_Pos      5

void UART2_GPIOInits(void);
void UART2_Init(void);

void UART_SendData(uint8_t *pTxBuffer,
                   uint32_t Len);


#endif /* INC_STM32L476XX_UART_DRIVER_H_ */
