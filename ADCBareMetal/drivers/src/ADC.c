#include "stm32l476xx.h"
#include "stm32l476xx_gpio_driver.h"

void ADC_GPIO_Init(void)
{
    GPIO_Handle_t ADC_Pin;

    GPIOC_PCLK_EN();

    ADC_Pin.pGPIOx = GPIOC;

    ADC_Pin.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    ADC_Pin.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ANALOG;
    ADC_Pin.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
    ADC_Pin.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    ADC_Pin.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    ADC_Pin.GPIO_PinConfig.GPIO_PinAltFunMode = 0;

    GPIO_Init(&ADC_Pin);
}

void ADC1_Init(void)
{
    /* Enable ADC peripheral clock */
    ADC1_PCLK_EN();

    /* ADC clock source = SYSCLK */
    RCC->CCIPR &= ~(3 << 28);
    RCC->CCIPR |=  (3 << 28);

    /* Exit Deep Power Down */
    ADC1->CR &= ~(1 << 29);

    /* Enable ADC Voltage Regulator */
    ADC1->CR |= (1 << 28);

    /* Wait regulator startup */
    for(volatile uint32_t i = 0; i < 10000; i++);

    /* Start Calibration */
    ADC1->CR |= (1 << 31);

    /* Wait until calibration complete */
    while(ADC1->CR & (1 << 31));

    /* Sampling Time for Channel 1 = 640.5 cycles */
    ADC1->SMPR1 &= ~(7 << 3);
    ADC1->SMPR1 |=  (7 << 3);

    /* Sequence length = 1 conversion */
    ADC1->SQR1 &= ~(0xF << 0);

    /* SQ1 = Channel 1 (PC0 = ADC123_IN1) */
    ADC1->SQR1 &= ~(0x1F << 6);
    ADC1->SQR1 |=  (1 << 6);

    /* Enable ADC */
    ADC1->CR |= (1 << 0);

    /* Wait until ADC Ready */
    while(!(ADC1->ISR & (1 << 0)));
}

uint16_t ADC_Read(void)
{
    /* Start conversion */
    ADC1->CR |= (1 << 2);

    /* Wait for End Of Conversion */
    while(!(ADC1->ISR & (1 << 2)));

    /* Return conversion result */
    return (uint16_t)ADC1->DR;
}
