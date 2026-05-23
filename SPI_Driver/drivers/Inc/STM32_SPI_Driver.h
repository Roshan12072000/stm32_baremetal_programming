#ifndef INC_STM32_SPI_DRIVER_H_
#define INC_STM32_SPI_DRIVER_H_

#include "stm32l476xx.h"

typedef struct
{
   volatile uint8_t SPI_DeviceMode;      // Master / Slave
   volatile uint8_t SPI_BusConfig;       // Full duplex / Half duplex / Simplex
   volatile uint8_t SPI_SclkSpeed;       // Clock speed
   volatile uint8_t SPI_DFF;             // 8-bit / 16-bit
   volatile uint8_t SPI_CPOL;            // Clock polarity
   volatile uint8_t SPI_CPHA;            // Clock phase
   volatile uint8_t SPI_SSM;             // Software slave management

}SPI_Config_t;

typedef struct
{
    SPI_RegDef_t *pSPIx;     // Holds SPI peripheral base address

    SPI_Config_t SPIConfig;  // Holds SPI configuration settings

}SPI_Handle_t;

// SPI BUSConfig
#define SPI_DEVICE_MODE_MASTER 		1
#define SPI_DEVICE_MODE_SLAVE		0

#define SPI_BUS_CONFIG_FD				1
#define SPI_BUS_CONFIG_HD				2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY	3

// SPI_SclkSpeed
#define SPI_SCLK_SPEED_DIV2      0
#define SPI_SCLK_SPEED_DIV4      1
#define SPI_SCLK_SPEED_DIV8      2
#define SPI_SCLK_SPEED_DIV16     3
#define SPI_SCLK_SPEED_DIV32     4
#define SPI_SCLK_SPEED_DIV64     5
#define SPI_SCLK_SPEED_DIV128    6
#define SPI_SCLK_SPEED_DIV256    7

//DFF
#define	SPI_DFF_8BITS	7
#define	SPI_DFF_16BITS	15

//CPOL
#define SPI_CPOL_HIGH	1
#define	SPI_CPOL_LOW	0

//CPOL
#define	SPI_CPHA_HIGH	1
#define	SPI_CPHA_LOW	0


// SSM
#define SPI_SSM_EN	1
#define	SPI_SSM_DI	0

//SPI related status flagss definations
#define SPI_TXE_FLAG 	(1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG 	(1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG 	(1 << SPI_SR_BUSY)

//for SPI Dff
#define SPI_CR2_DS        8
//peripheral clock setup
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi);

// Init and De-init
void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

// Data send and receive
void SPI_SendData(SPI_RegDef_t *pSPIx,uint8_t *pTxBuffer,uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len);

//IRQ Configuration and ISR handling
void SPI_IRQITConfig(uint8_t IRQNumber,uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority);

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx,uint8_t EnOrDi);
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx,uint32_t FlagName);
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);
#endif /* INC_STM32_SPI_DRIVER_H_ */
