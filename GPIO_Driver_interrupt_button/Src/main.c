#include "stm32l476xx_gpio_driver.h"
#include "stm32l476xx.h"

#include <stdint.h>
#include<string.h>
void delay(void){
	for(uint32_t i = 0; i < 500000/2; i++){
		;
	}
}
void  EXTI15_10_IRQHandler(void){
	   delay();
    	GPIO_IRQHandling(GPIO_PIN_NO_13);
    	GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);
    }

int main(void)
{
    GPIO_Handle_t GpioLed,GPIOBtn;
    memset(&GpioLed,0,sizeof(GpioLed));
    memset(&GPIOBtn,0,sizeof(GPIOBtn));
    GpioLed.pGPIOx = GPIOA;
    GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
    GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_Init(&GpioLed);

    GPIOBtn.pGPIOx = GPIOC;
    GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
//    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
//    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

       GPIO_PeriClockControl(GPIOC,ENABLE);
       GPIO_Init(&GPIOBtn);
       GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10,15);
    GPIO_IRQITConfig(IRQ_NO_EXTI15_10,ENABLE);


    while(1){
//    	if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) == 0){
//    	    		delay();
//    	    		GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);
//    	}
    }

    return 0;
}

