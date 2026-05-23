#include "stm32l476xx_gpio_driver.h"
#include "STM32_SPI_Driver.h"
#include <stdint.h>
#include <string.h>

#define CS_LOW()   GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, GPIO_PIN_RESET)
#define CS_HIGH()  GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, GPIO_PIN_SET)

void SPI_GPIO_Init(void);
void SPI1_Inits(void);

void delay(void);

void W25Q_WriteEnable(void);
uint8_t W25Q_ReadStatus(void);
void W25Q_WaitBusy(void);

void W25Q_ReadID(void);
void W25Q_EraseSector(uint32_t addr);

void W25Q_Write(uint32_t addr, uint8_t *data, uint16_t len);
void W25Q_Read(uint32_t addr, uint8_t *data, uint16_t len);

char tx_buf[] = "Hello Flash Memory";
char rx_buf[50];

int main(void)
{
    SPI_GPIO_Init();

    SPI1_Inits();

    // Enable SPI1 Peripheral
    SPI_PeripheralControl(SPI1, ENABLE);

    delay();

    W25Q_ReadID();

    // Erase sector 0
    W25Q_EraseSector(0x000000);

    // Write data
    W25Q_Write(0x000000, (uint8_t*)tx_buf, strlen(tx_buf)+1);

    // Read data
    W25Q_Read(0x000000, (uint8_t*)rx_buf, strlen(tx_buf)+1);

    while(1)
    {

    }

    return 0;
}

void delay(void)
{
    for(uint32_t i = 0; i < 500000/2; i++);
}

/****************************************************************
 * SPI GPIO INIT
 ***************************************************************/
void SPI_GPIO_Init(void)
{
    GPIO_Handle_t SPIPins;

    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_PeriClockControl(GPIOB, ENABLE);

    // PA5 -> SCK
    SPIPins.pGPIOx = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = 5;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    GPIO_Init(&SPIPins);

    // PA6 -> MISO
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    GPIO_Init(&SPIPins);

    // PA7 -> MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_7;
    GPIO_Init(&SPIPins);

    // PB6 -> CS
    SPIPins.pGPIOx = GPIOB;
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    SPIPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    SPIPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    SPIPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    GPIO_Init(&SPIPins);

    CS_HIGH();
}

/****************************************************************
 * SPI INIT
 ***************************************************************/
void SPI1_Inits(void)
{
    SPI_Handle_t SPI1Handle;

    SPI_PeriClockControl(SPI1, ENABLE);

    SPI1Handle.pSPIx = SPI1;

    SPI1Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
    SPI1Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI1Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;
    SPI1Handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
    SPI1Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI1Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI1Handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

    SPI_Init(&SPI1Handle);

    // SSI = 1
    SPI_SSIConfig(SPI1, ENABLE);
}

/****************************************************************
 * WRITE ENABLE
 ***************************************************************/
void W25Q_WriteEnable(void)
{
    uint8_t cmd = 0x06;

    CS_LOW();

    SPI_SendData(SPI1, &cmd, 1);

    while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

    CS_HIGH();
}

/****************************************************************
 * READ STATUS REGISTER
 ***************************************************************/
uint8_t W25Q_ReadStatus(void)
{
    uint8_t cmd = 0x05;
    uint8_t status = 0;

    CS_LOW();

    SPI_SendData(SPI1, &cmd, 1);

    SPI_ReceiveData(SPI1, &status, 1);

    while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

    CS_HIGH();

    return status;
}

/****************************************************************
 * WAIT UNTIL FLASH FREE
 ***************************************************************/
void W25Q_WaitBusy(void)
{
    while(W25Q_ReadStatus() & 0x01);
}

/****************************************************************
 * READ JEDEC ID
 ***************************************************************/
uint8_t id[3];
void W25Q_ReadID(void)
{
    uint8_t cmd = 0x9F;
//    uint8_t id[3];

    CS_LOW();

    SPI_SendData(SPI1, &cmd, 1);

    SPI_ReceiveData(SPI1, id, 3);

    while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

    CS_HIGH();

    // Expected:
    // EF 40 16 for W25Q32
}

/****************************************************************
 * ERASE SECTOR
 ***************************************************************/
void W25Q_EraseSector(uint32_t addr)
{
    uint8_t cmd[4];

    W25Q_WriteEnable();

    cmd[0] = 0x20;

    cmd[1] = (addr >> 16) & 0xFF;
    cmd[2] = (addr >> 8) & 0xFF;
    cmd[3] = addr & 0xFF;

    CS_LOW();

    SPI_SendData(SPI1, cmd, 4);

    while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

    CS_HIGH();

    W25Q_WaitBusy();
}

/****************************************************************
 * WRITE DATA
 ***************************************************************/
void W25Q_Write(uint32_t addr, uint8_t *data, uint16_t len)
{
    uint8_t cmd[4];

    W25Q_WriteEnable();

    cmd[0] = 0x02;

    cmd[1] = (addr >> 16) & 0xFF;
    cmd[2] = (addr >> 8) & 0xFF;
    cmd[3] = addr & 0xFF;

    CS_LOW();

    SPI_SendData(SPI1, cmd, 4);

    SPI_SendData(SPI1, data, len);

    while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

    CS_HIGH();

    W25Q_WaitBusy();
}

/****************************************************************
 * READ DATA
 ***************************************************************/
void W25Q_Read(uint32_t addr, uint8_t *data, uint16_t len)
{
    uint8_t cmd[4];

    cmd[0] = 0x03;

    cmd[1] = (addr >> 16) & 0xFF;
    cmd[2] = (addr >> 8) & 0xFF;
    cmd[3] = addr & 0xFF;

    CS_LOW();

    SPI_SendData(SPI1, cmd, 4);

    SPI_ReceiveData(SPI1, data, len);

    while(SPI_GetFlagStatus(SPI1, SPI_BUSY_FLAG));

    CS_HIGH();
}
