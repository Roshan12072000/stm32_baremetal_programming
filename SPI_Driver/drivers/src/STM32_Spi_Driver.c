#include "stm32l476xx.h"
#include "STM32_SPI_Driver.h"

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        // Set SPE bit
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);
    }
    else
    {
        // Clear SPE bit
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
    }
}

//peripheral clock setup
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi){
		  if(EnorDi == ENABLE)
		    {
		        if(pSPIx == SPI1)
		            SPI1_PCLK_EN();

		        else if(pSPIx == SPI2)
		            SPI2_PCLK_EN();

		        else if(pSPIx == SPI3)
		            SPI3_PCLK_EN();
		    }
		    else
		    {
		        if(pSPIx == SPI1)
		            SPI1_PCLK_DI();

		        else if(pSPIx == SPI2)
		            SPI2_PCLK_DI();

		        else if(pSPIx == SPI3)
		            SPI3_PCLK_DI();
		    }
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    uint32_t tempreg1 = 0;
    uint32_t tempreg2 = 0;

    //1. Configure device mode
    tempreg1 |= (pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR);

    //2. Configure bus config
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        tempreg1 &= ~(1 << SPI_CR1_BIDIMODE);
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        tempreg1 |= (1 << SPI_CR1_BIDIMODE);
    }
    else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
    {
        tempreg1 &= ~(1 << SPI_CR1_BIDIMODE);

        tempreg1 |= (1 << SPI_CR1_RXONLY);
    }

    //3. Configure baud rate
    tempreg1 |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR);

    //4. Configure CPOL
    tempreg1 |= (pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL);

    //5. Configure CPHA
    tempreg1 |= (pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA);

    //6. Configure SSM
    tempreg1 |= (pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM);

    //7. Configure Data Size (DS bits in CR2)
    tempreg2 |= (pSPIHandle->SPIConfig.SPI_DFF << SPI_CR2_DS);

    // IMPORTANT for 8-bit RXNE
    tempreg2 |= (1 << SPI_CR2_FRXTH);

    //Write to registers
    pSPIHandle->pSPIx->CR1 = tempreg1;
    pSPIHandle->pSPIx->CR2 = tempreg2;
}


void SPI_DeInit(SPI_RegDef_t *pSPIx){
	    if(pSPIx == SPI1)
	    {
	        SPI1_REG_RESET();
	    }
	    else if(pSPIx == SPI2)
	    {
	        SPI2_REG_RESET();
	    }
	    else if(pSPIx == SPI3)
	    {
	        SPI3_REG_RESET();
	    }
}
uint8_t	 SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
	if(pSPIx->SR & FlagName)
	return FLAG_SET;
	return FLAG_RESET;
}

// this is blocking call
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len)
{
    while(Len > 0)
    {
        // Wait until TXE = 1
        while(!(pSPIx->SR & (1 << SPI_SR_TXE)));

        // Send dummy byte
        *((volatile uint8_t*)&pSPIx->DR) = 0xFF;

        // Wait until RXNE = 1
        while(!(pSPIx->SR & (1 << SPI_SR_RXNE)));

        // Read received byte
        *pRxBuffer = *((volatile uint8_t*)&pSPIx->DR);

        pRxBuffer++;
        Len--;
    }

    // Wait until SPI not busy
    while(pSPIx->SR & (1 << SPI_SR_BUSY));
}
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
    volatile uint8_t temp;

    while(Len > 0)
    {
        // Wait until TXE = 1
        while(!(pSPIx->SR & (1 << SPI_SR_TXE)));

        // Send byte
        *((volatile uint8_t*)&pSPIx->DR) = *pTxBuffer;

        // Wait until RXNE = 1
        while(!(pSPIx->SR & (1 << SPI_SR_RXNE)));

        // Clear received dummy byte
        temp = *((volatile uint8_t*)&pSPIx->DR);

        (void)temp;

        pTxBuffer++;
        Len--;
    }

    // Wait until SPI not busy
    while(pSPIx->SR & (1 << SPI_SR_BUSY));
}
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
    }
}
