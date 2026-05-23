#include "stm32l476xx_gpio_driver.h"
#include "STM32_SPI_Driver.h"
#include "stm32l476xx_i2c_driver.h"
#include <stdint.h>
#include <string.h>

SPI_Handle_t SPI1Handle;
I2C_Handle_t I2C1Handle;

volatile uint8_t FlashState = FLASH_IDLE;

uint8_t cmd_buf[4];
uint8_t *g_txBuffer;
uint8_t *g_rxBuffer;
volatile uint16_t g_rxLen;
volatile uint16_t g_txLen;

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

void W25Q_Write_IT(uint32_t addr, uint8_t *data, uint16_t len);
void W25Q_Read_IT(uint32_t addr, uint8_t *data, uint16_t len);

void I2C1_GPIOInits(void);
void I2C1_Inits(void);

char tx_buf[] = "Hello this is from Flash Memory";
char rx_buf[50];



void SPI1_IRQHandler(void)
{
    SPI_IRQHandling(&SPI1Handle);
}
uint8_t reg_addr = 0x00;
uint8_t sensor_data;int lux;
int main(void)
{

	char msg[] =
	        "UART Polling Test\r\n";

	    UART2_GPIOInits();

	    UART2_Init();

	    while(1)
	    {
	        UART_SendData((uint8_t*)msg,
	                      strlen(msg));

	        delay();
	    }
}
void delay(void)
{
    for(uint32_t i = 0; i < 500000/2; i++);
}

/*********************************************************************
 *                      I2C GPIO INIT
 *********************************************************************/

void I2C1_GPIOInits(void)
{

	GPIOB_PCLK_EN();
    GPIO_Handle_t I2CPins;

    /*
     * PB8  -> I2C1_SCL
     * PB9  -> I2C1_SDA
     */

    I2CPins.pGPIOx = GPIOB;

    I2CPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
    I2CPins.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
    I2CPins.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    I2CPins.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    I2CPins.GPIO_PinConfig.GPIO_PinAltFunMode = 4;

    /* SCL */
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    GPIO_Init(&I2CPins);

    /* SDA */
    I2CPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
    GPIO_Init(&I2CPins);
}

/*********************************************************************
 *                      I2C INIT
 *********************************************************************/

void I2C1_Inits(void)
{
	 I2C1_PCLK_EN();

    I2C1Handle.pI2Cx = I2C1;

    I2C1Handle.I2C_Config.I2C_ACKControl = I2C_ACK_ENABLE;

    I2C1Handle.I2C_Config.I2C_SCLSpeed =I2C_SCL_SPEED_SM;

    I2C1Handle.I2C_Config.I2C_DeviceAddress =0x61;

    I2C_Init(&I2C1Handle);
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
//    SPI_Handle_t SPI1Handle;

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
void W25Q_Write_IT(uint32_t addr,
                   uint8_t *data,
                   uint16_t len)
{
    // Store user buffer
    g_txBuffer = data;
    g_txLen = len;

    FlashState = FLASH_WRITE_CMD;

    // Write enable first
    W25Q_WriteEnable();

    // Prepare command
    cmd_buf[0] = 0x02;

    cmd_buf[1] = (addr >> 16) & 0xFF;
    cmd_buf[2] = (addr >> 8) & 0xFF;
    cmd_buf[3] = addr & 0xFF;

    CS_LOW();

    // Send command + address
    SPI_SendDataIT(&SPI1Handle, cmd_buf, 4);
}

/****************************************************************
 * READ DATA
 ***************************************************************/
void W25Q_Read_IT(uint32_t addr,
                  uint8_t *data,
                  uint16_t len)
{
    g_rxBuffer = data;
    g_rxLen = len;


    FlashState = FLASH_READ_CMD;

    cmd_buf[0] = 0x03;
    cmd_buf[1] = (addr >> 16) & 0xFF;
    cmd_buf[2] = (addr >> 8) & 0xFF;
    cmd_buf[3] = addr & 0xFF;

    CS_LOW();

    SPI_SendDataIT(&SPI1Handle, cmd_buf, 4);
}
void SPI_ApplicationEventCallback(
                    SPI_Handle_t *pSPIHandle,
                    uint8_t AppEv)
{
    if(AppEv == SPI_EVENT_TX_CMPLT)
    {
        // READ: command phase complete
        if(FlashState == FLASH_READ_CMD)
        {
            FlashState = FLASH_READ_DATA;

            SPI_ReceiveDataIT(&SPI1Handle,
                              g_rxBuffer,
                              g_rxLen);
        }

        // WRITE: command phase complete
        else if(FlashState == FLASH_WRITE_CMD)
        {
            FlashState = FLASH_WRITE_DATA;

            SPI_SendDataIT(&SPI1Handle,
                           g_txBuffer,
                           g_txLen);
        }

        // WRITE DATA complete
        else if(FlashState == FLASH_WRITE_DATA)
        {
            while(SPI1->SR & (1 << SPI_SR_BUSY));

            CS_HIGH();

            FlashState = FLASH_IDLE;
        }
    }

    else if(AppEv == SPI_EVENT_RX_CMPLT)
    {
        if(FlashState == FLASH_READ_DATA)
        {
            while(SPI1->SR & (1 << SPI_SR_BUSY));

            CS_HIGH();

            FlashState = FLASH_IDLE;
        }
    }

    else if(AppEv == SPI_EVENT_OVR_ERR)
    {
        // Handle SPI error
    }
}
