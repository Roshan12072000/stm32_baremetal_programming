#include "stm32l476xx_gpio_driver.h"
#include "stm32l476xx.h"

#include <stdint.h>
//
//#if !defined(__SOFT_FP__) && defined(__ARM_FP)
//  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
//#endif
void delay(void){
	for(uint32_t i = 0; i < 500000/2; i++){
		;
	}
}
int main(void)
{
    GPIO_Handle_t GpioLed,GPIOBtn;
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
    GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

       GPIO_PeriClockControl(GPIOC,ENABLE);
       GPIO_Init(&GPIOBtn);
    while(1){
    	if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13) == 0){
    		delay();
    		GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);
    	}


//    	GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);
//    	delay();
    }
    return 0;
}
