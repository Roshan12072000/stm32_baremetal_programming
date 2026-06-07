/*
 * ADC.h
 *
 *  Created on: Jun 5, 2026
 *      Author: User
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#define GPIO_MODE_ANALOG    3
uint16_t ADC_Read(void);
void ADC1_Init(void);
void ADC_GPIO_Init(void);

#endif /* INC_ADC_H_ */
