#include "stm32l476xx.h"
#include "stm32l476xx_i2c_driver.h"
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pI2Cx == I2C1)
        {
            RCC->APB1ENR1 |= (1 << 21);
        }
        else if(pI2Cx == I2C2)
        {
            RCC->APB1ENR1 |= (1 << 22);
        }
        else if(pI2Cx == I2C3)
        {
            RCC->APB1ENR1 |= (1 << 23);
        }
    }
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    /* Disable Peripheral */
    pI2CHandle->pI2Cx->CR1 &= ~(1 << I2C_CR1_PE_Pos);

    /*
     * TIMINGR
     * 100KHz
     * PCLK1 = 80MHz
     */

    if(pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_SM)
    {
        pI2CHandle->pI2Cx->TIMINGR = 0x10909CEC;
    }
    else if(pI2CHandle->I2C_Config.I2C_SCLSpeed == I2C_SCL_SPEED_FM)
    {
        pI2CHandle->pI2Cx->TIMINGR = 0x00702991;
    }

    /* Own Address */
    pI2CHandle->pI2Cx->OAR1 =
            (1 << 10) |
            (pI2CHandle->I2C_Config.I2C_DeviceAddress << 1);

    /* Enable Peripheral */
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_PE_Pos);
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len,uint8_t SlaveAddr)
{
    /* Wait until BUSY flag reset */
    while(pI2CHandle->pI2Cx->ISR &
            (1 << I2C_ISR_BUSY_Pos));

    /* Clear CR2 */
    pI2CHandle->pI2Cx->CR2 = 0;

    /*
     * Slave address
     */
    pI2CHandle->pI2Cx->CR2 |= (SlaveAddr << 1);

    /*
     * Number of bytes
     */
    pI2CHandle->pI2Cx->CR2 |=  (Len << I2C_CR2_NBYTES_Pos);

    /*
     * AUTOEND
     */
    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_AUTOEND_Pos);

    /*
     * Generate START
     */
    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_START_Pos);

    while(Len > 0)
    {
        /*
         * Wait until TXIS set
         */
        while(!(pI2CHandle->pI2Cx->ISR &
                (1 << I2C_ISR_TXIS_Pos)))
        {
            /*
             * Check NACK
             */
            if(pI2CHandle->pI2Cx->ISR &
               (1 << I2C_ISR_NACKF_Pos))
            {
                /*
                 * Clear NACK
                 */
                pI2CHandle->pI2Cx->ICR |= (1 << I2C_ICR_NACKCF_Pos);

                /*
                 * Clear STOP
                 */
                pI2CHandle->pI2Cx->ICR |= (1 << I2C_ICR_STOPCF_Pos);

                return;
            }
        }

        /*
         * Write data
         */
        pI2CHandle->pI2Cx->TXDR = *pTxBuffer;

        pTxBuffer++;
        Len--;
    }

    /*
     * Wait for STOPF
     */
    while(!(pI2CHandle->pI2Cx->ISR & (1 << I2C_ISR_STOPF_Pos)));

    /*
     * Clear STOP flag
     */
    pI2CHandle->pI2Cx->ICR |= (1 << I2C_ICR_STOPCF_Pos);
}
void I2C_MasterReceiveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
    while(pI2CHandle->pI2Cx->ISR &
            (1 << I2C_ISR_BUSY_Pos));

    pI2CHandle->pI2Cx->CR2 = 0;

    pI2CHandle->pI2Cx->CR2 |= (SlaveAddr << 1);

    /* Read mode */
    pI2CHandle->pI2Cx->CR2 |= (1 << I2C_CR2_RD_WRN_Pos);

    pI2CHandle->pI2Cx->CR2 |=
            (Len << I2C_CR2_NBYTES_Pos);

    pI2CHandle->pI2Cx->CR2 |=
            (1 << I2C_CR2_AUTOEND_Pos);

    /* Generate START */
    pI2CHandle->pI2Cx->CR2 |=
            (1 << I2C_CR2_START_Pos);

    while(Len > 0)
    {
        /* Wait until RXNE */
    	while(!(pI2CHandle->pI2Cx->ISR &
    	        (1 << I2C_ISR_RXNE_Pos)))
    	{
    	    if(pI2CHandle->pI2Cx->ISR &
    	       (1 << I2C_ISR_NACKF_Pos))
    	    {
    	        pI2CHandle->pI2Cx->ICR |= (1 << I2C_ICR_NACKCF_Pos);
                pI2CHandle->pI2Cx->ICR |= (1 << I2C_ICR_STOPCF_Pos);
    	        return;
    	    }
    	}

        *pRxBuffer = pI2CHandle->pI2Cx->RXDR;

        pRxBuffer++;
        Len--;
    }

    /* Wait STOPF */
    while(!(pI2CHandle->pI2Cx->ISR &
            (1 << I2C_ISR_STOPF_Pos)));

    /* Clear STOP */
    pI2CHandle->pI2Cx->ICR |=
            (1 << I2C_ICR_STOPCF_Pos);
}
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle,
                             uint8_t *pTxBuffer,
                             uint32_t Len,
                             uint8_t SlaveAddr)
{
    uint8_t busystate =
            pI2CHandle->TxRxState;

    if(busystate != I2C_BUSY_IN_TX)
    {
        pI2CHandle->pTxBuffer = pTxBuffer;
        pI2CHandle->TxLen = Len;

        pI2CHandle->TxRxState =
                I2C_BUSY_IN_TX;

        /*
         * Wait BUSY reset
         */
        while(pI2CHandle->pI2Cx->ISR &
                (1 << I2C_ISR_BUSY_Pos));

        /*
         * Configure CR2
         */
        pI2CHandle->pI2Cx->CR2 = 0;

        pI2CHandle->pI2Cx->CR2 |=
                (SlaveAddr << 1);

        pI2CHandle->pI2Cx->CR2 |=
                (Len << I2C_CR2_NBYTES_Pos);

        pI2CHandle->pI2Cx->CR2 |=
                (1 << I2C_CR2_AUTOEND_Pos);

        /*
         * Enable interrupts
         */
        pI2CHandle->pI2Cx->CR1 |=
                (1 << I2C_CR1_TXIE_Pos);

        pI2CHandle->pI2Cx->CR1 |=
                (1 << I2C_CR1_STOPIE_Pos);

        pI2CHandle->pI2Cx->CR1 |=
                (1 << I2C_CR1_NACKIE_Pos);

        /*
         * Generate START
         */
        pI2CHandle->pI2Cx->CR2 |=
                (1 << I2C_CR2_START_Pos);
    }

    return busystate;
}
