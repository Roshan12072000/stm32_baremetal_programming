#ifndef INC_STM32L476XX_H_
#define INC_STM32L476XX_H_

#include <stdint.h>

//ARM Cortex Mx Processor NVIC ISERx register Addresses
#define NVIC_ISER0      ((volatile uint32_t*)0xE000E100)
#define NVIC_ISER1      ((volatile uint32_t*)0xE000E104)
#define NVIC_ISER2      ((volatile uint32_t*)0xE000E108)
#define NVIC_ISER3      ((volatile uint32_t*)0xE000E10C)

//ARM Cortex Mx Processor NVIC ISERx register Addresses
#define NVIC_ICER0      ((volatile uint32_t*)0xE000E180)
#define NVIC_ICER1      ((volatile uint32_t*)0xE000E184)
#define NVIC_ICER2      ((volatile uint32_t*)0xE000E188)
#define NVIC_ICER3      ((volatile uint32_t*)0xE000E18C)

#define NVIC_PR_BASE_ADDR      ((volatile uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED			4

#define FLASH_BASEADDR		0x08000000U
#define SRAM1_BASEADDR		0x20000000U
#define SRAM2_BASEADDR		0x20040000U
#define ROM 				0x1FFF0000U
#define SRAM				SRAM1_BASEADDR


#define APB1PERIPH_BASEADDR		0x40000000U
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x48000000U

#define GPIOA_BASEADDR			0x48000000U // In AHB2
#define GPIOB_BASEADDR			0x48000400U //
#define GPIOC_BASEADDR			0x48000800U
#define GPIOD_BASEADDR			0x48000C00U
#define GPIOE_BASEADDR			0x48001000U
#define GPIOF_BASEADDR			0x48001400U
#define GPIOG_BASEADDR			0x48001800U
#define GPIOH_BASEADDR			0x48001C00U
#define GPIOI_BASEADDR			0x48002000U
#define RCC_BASEADDR			0x40021000U


//  BASE address of peripherals which are hanging on APB1 bus
#define SPI2_BASEADDR 		0x40003800U
#define SPI3_BASEADDR		0x40003C00U
#define USART2_BASEADDR		0x40004400U
#define USART3_BASEADDR		0x40004800U
#define I2C1_BASEADDR		0x40005400U
#define I2C2_BASEADDR		0x40005800U
#define I2C3_BASEADDR		0x40005C00U

// BASE address of peripherals whihc are hanging on APB2
#define EXTI_BASEADDR		0x40010400U
#define TIM1_BASEADDR		0x40012C00U
#define SPI1_BASEADDR		0x40013000U
#define UART1_BASEADDR		0x40013800U
#define SYSCFG_BASEADDR		0x40010000U

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_RegDef_t;


typedef struct
{
    volatile uint32_t CR;            // 0x00
    volatile uint32_t ICSCR;         // 0x04
    volatile uint32_t CFGR;          // 0x08
    volatile uint32_t PLLCFGR;       // 0x0C
    volatile uint32_t PLLSAI1CFGR;   // 0x10
    volatile uint32_t PLLSAI2CFGR;   // 0x14
    volatile uint32_t CIER;          // 0x18
    volatile uint32_t CIFR;          // 0x1C
    volatile uint32_t CICR;          // 0x20

    uint32_t RESERVED0;              // 0x24

    volatile uint32_t AHB1RSTR;      // 0x28
    volatile uint32_t AHB2RSTR;      // 0x2C
    volatile uint32_t AHB3RSTR;      // 0x30

    uint32_t RESERVED1;              // 0x34

    volatile uint32_t APB1RSTR1;     // 0x38
    volatile uint32_t APB1RSTR2;     // 0x3C
    volatile uint32_t APB2RSTR;      // 0x40

    uint32_t RESERVED2;				//  0x44

    volatile uint32_t AHB1ENR;       // 0x48
    volatile uint32_t AHB2ENR;       // 0x4C
    volatile uint32_t AHB3ENR;       // 0x50

    uint32_t RESERVED3;              // 0x54

    volatile uint32_t APB1ENR1;      // 0x58
    volatile uint32_t APB1ENR2;      // 0x5C
    volatile uint32_t APB2ENR;       // 0x60

    uint32_t RESERVED4;              // 0x64

    volatile uint32_t AHB1SMENR;     // 0x68
    volatile uint32_t AHB2SMENR;     // 0x6C
    volatile uint32_t AHB3SMENR;     // 0x70

    uint32_t RESERVED5;              // 0x74

    volatile uint32_t APB1SMENR1;    // 0x78
    volatile uint32_t APB1SMENR2;    // 0x7C
    volatile uint32_t APB2SMENR;     // 0x80

    uint32_t RESERVED6;              // 0x84

    volatile uint32_t CCIPR;         // 0x88

    uint32_t RESERVED7;              // 0x8C

    volatile uint32_t BDCR;          // 0x90
    volatile uint32_t CSR;           // 0x94
    volatile uint32_t CRRCR;         // 0x98
    volatile uint32_t CCIPR2;        // 0x9C

} RCC_RegDef_t;

// Exti peripheral registeer defination structure
typedef struct
{
	volatile uint32_t IMR1;      // 0x00 Interrupt mask register 1
	volatile uint32_t EMR1;      // 0x04 Event mask register 1
	volatile uint32_t RTSR1;     // 0x08 Rising trigger selection register 1
	volatile uint32_t FTSR1;     // 0x0C Falling trigger selection register 1
	volatile uint32_t SWIER1;    // 0x10 Software interrupt event register 1
	volatile uint32_t PR1;       // 0x14 Pending register 1

	uint32_t RESERVED1[2];       // 0x18 - 0x1C

	volatile uint32_t IMR2;      // 0x20 Interrupt mask register 2
	volatile uint32_t EMR2;      // 0x24 Event mask register 2
	volatile uint32_t RTSR2;     // 0x28 Rising trigger selection register 2
	volatile uint32_t FTSR2;     // 0x2C Falling trigger selection register 2
	volatile uint32_t SWIER2;    // 0x30 Software interrupt event register 2
	volatile uint32_t PR2;       // 0x34 Pending register 2

} EXTI_RegDef_t;

// SYS Configuration peripheral register difination structure
typedef struct
{
	volatile uint32_t MEMRMP;        // 0x00 Memory remap register
	volatile uint32_t CFGR1;         // 0x04 Configuration register 1
	volatile uint32_t EXTICR[4];       // 0x08 External interrupt configuration register 1
	//volatile uint32_t EXTICR2;       // 0x0C External interrupt configuration register 2
	//volatile uint32_t EXTICR3;       // 0x10 External interrupt configuration register 3
	//volatile uint32_t EXTICR4;       // 0x14 External interrupt configuration register 4
	volatile uint32_t SCSR;          // 0x18 SRAM2 control and status register
	volatile uint32_t CFGR2;         // 0x1C Configuration register 2
	volatile uint32_t SWPR;          // 0x20 SRAM2 write protection register
	volatile uint32_t SKR;           // 0x24 SRAM2 key register
	volatile uint32_t SWPR2;         // 0x28 SRAM2 write protection register 2

} SYSCFG_RegDef_t;

// SPI Configuration peripheral register difination structure
typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;

}SPI_RegDef_t;

/* SPI_CR1 register bit position definitions */

#define SPI_CR1_CPHA          0
#define SPI_CR1_CPOL          1
#define SPI_CR1_MSTR          2
#define SPI_CR1_BR            3
#define SPI_CR1_SPE           6
#define SPI_CR1_LSBFIRST      7
#define SPI_CR1_SSI           8
#define SPI_CR1_SSM           9
#define SPI_CR1_RXONLY        10
#define SPI_CR1_CRCL          11
#define SPI_CR1_CRCNEXT       12
#define SPI_CR1_CRCEN         13
#define SPI_CR1_BIDIOE        14
#define SPI_CR1_BIDIMODE      15

/* SPI_CR2 register bit position definitions */

#define SPI_CR2_RXDMAEN       0
#define SPI_CR2_TXDMAEN       1
#define SPI_CR2_SSOE          2
#define SPI_CR2_NSSP          3
#define SPI_CR2_FRF           4
#define SPI_CR2_ERRIE         5
#define SPI_CR2_RXNEIE        6
#define SPI_CR2_TXEIE         7
#define SPI_CR2_DS            8
#define SPI_CR2_FRXTH         12
#define SPI_CR2_LDMA_RX       13
#define SPI_CR2_LDMA_TX       14

/* SPI_SR register bit position definitions */

#define SPI_SR_RXNE           0
#define SPI_SR_TXE            1
#define SPI_SR_CRCERR         4
#define SPI_SR_MODF           5
#define SPI_SR_OVR            6
#define SPI_SR_BUSY           7
#define SPI_SR_FRE            8
#define SPI_SR_FRLVL          9
#define SPI_SR_FTLVL          11

// Peripheral defination
#define GPIOA		((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB		((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC		((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD		((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE		((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF		((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG		((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH		((GPIO_RegDef_t*)GPIOH_BASEADDR)
#define GPIOI 		((GPIO_RegDef_t*)GPIOI_BASEADDR)
#define RCC 		((RCC_RegDef_t*)RCC_BASEADDR)
#define EXTI		((EXTI_RegDef_t*)EXTI_BASEADDR)
#define SYSCFG		((SYSCFG_RegDef_t*)SYSCFG_BASEADDR)
#define SPI1		((SPI_RegDef_t*)SPI1_BASEADDR)
#define SPI2		((SPI_RegDef_t*)SPI2_BASEADDR)
#define SPI3		((SPI_RegDef_t*)SPI3_BASEADDR)

// Clock enable macros for gpiox peripherals
#define GPIOA_PCLK_EN()	(RCC->AHB2ENR |= (1 << 0))
#define GPIOB_PCLK_EN()	(RCC->AHB2ENR |= (1 << 1))
#define GPIOC_PCLK_EN()	(RCC->AHB2ENR |= (1 << 2))
#define GPIOD_PCLK_EN()	(RCC->AHB2ENR |= (1 << 3))
#define GPIOE_PCLK_EN()	(RCC->AHB2ENR |= (1 << 4))
#define GPIOF_PCLK_EN()	(RCC->AHB2ENR |= (1 << 5))
#define GPIOG_PCLK_EN()	(RCC->AHB2ENR |= (1 << 6))
#define GPIOH_PCLK_EN()	(RCC->AHB2ENR |= (1 << 7))
#define GPIOI_PCLK_EN()	(RCC->AHB2ENR |= (1 << 8))

//Clock Enable  Macros for I2C Peripheral
#define I2C1_PCLK_EN()	(RCC->APB1ENR1 |= (1 << 21))
#define I2C2_PCLK_EN()	(RCC->APB1ENR1 |= (1 << 22))
#define I2C3_PCLK_EN()	(RCC->APB1ENR1 |= (1 << 23))

//Clock Enable  Macros for SPI Peripheral
#define SPI1_PCLK_EN()	(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()	(RCC->APB1ENR1 |= (1 << 14))
#define SPI3_PCLK_EN()	(RCC->APB1ENR1 |= (1 << 15))

//Clock Enable  Macros for UARTx Peripheral
#define USART2_PCLK_EN()	(RCC->APB1ENR1 |= (1 << 17))
#define USART3_PCLK_EN()	(RCC->APB1ENR1 |= (1 << 18))
#define UART1_PCLK_EN()	(RCC->APB2ENR |= (1 << 14))

//Clock Enable  Macros for SYSCFG Peripheral
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1 << 0))


//Clock Disable Macros for GPIOx peripherals
#define GPIOA_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()	(RCC->AHB2ENR &= ~(1 << 8))

//Clock Diable  Macros for I2C Peripheral
#define I2C1_PCLK_DI()	(RCC->APB1ENR1 &= ~(1 << 21))
#define I2C2_PCLK_DI()	(RCC->APB1ENR1 &= ~(1 << 22))
#define I2C3_PCLK_DI()	(RCC->APB1ENR1 &= ~(1 << 23))

//Clock Disable  Macros for SPI Peripheral
#define SPI1_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()	(RCC->APB1ENR1 &= ~(1 << 14))
#define SPI3_PCLK_DI()	(RCC->APB1ENR1 &= ~(1 << 15))

//Clock Disable  Macros for UARTx Peripheral
#define USART2_PCLK_DI()	(RCC->APB1ENR1 &= ~(1 << 17))
#define USART3_PCLK_DI()	(RCC->APB1ENR1 &= ~(1 << 18))
#define UART1_PCLK_DI()		(RCC->APB2ENR &= ~(1 << 14))

//Clock Disable  Macros for SYSCFG Peripheral
#define SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 0))


// Macros to reset GPIOx peripherals
#define GPIOA_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 0)); (RCC->AHB2RSTR &= ~(1 << 0));}while(0)
#define GPIOB_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 1)); (RCC->AHB2RSTR &= ~(1 << 1));}while(0)
#define GPIOC_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 2)); (RCC->AHB2RSTR &= ~(1 << 2));}while(0)
#define GPIOD_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 3)); (RCC->AHB2RSTR &= ~(1 << 3));}while(0)
#define GPIOE_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 4)); (RCC->AHB2RSTR &= ~(1 << 4));}while(0)
#define GPIOF_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 5)); (RCC->AHB2RSTR &= ~(1 << 5));}while(0)
#define GPIOG_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 6)); (RCC->AHB2RSTR &= ~(1 << 6));}while(0)
#define GPIOH_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 7)); (RCC->AHB2RSTR &= ~(1 << 7));}while(0)
#define GPIOI_REG_RESET() 	do{(RCC->AHB2RSTR |= (1 << 8)); (RCC->AHB2RSTR &= ~(1 << 8));}while(0)

// RESET SPIx peripherals
#define SPI1_REG_RESET() \
do{ \
(RCC->APB2RSTR |= (1 << 12)); \
(RCC->APB2RSTR &= ~(1 << 12)); \
}while(0)

#define SPI2_REG_RESET() \
do{ \
(RCC->APB1RSTR1 |= (1 << 14)); \
(RCC->APB1RSTR1 &= ~(1 << 14)); \
}while(0)

#define SPI3_REG_RESET() \
do{ \
(RCC->APB1RSTR1 |= (1 << 15)); \
(RCC->APB1RSTR1 &= ~(1 << 15)); \
}while(0)

// returns port code for given GPIOx base address
#define GPIO_BASEADDR_TO_CODE(x)  ((x == GPIOA) ? 0 : \
                                   (x == GPIOB) ? 1 : \
                                   (x == GPIOC) ? 2 : \
                                   (x == GPIOD) ? 3 : \
                                   (x == GPIOE) ? 4 : \
                                   (x == GPIOF) ? 5 : \
                                   (x == GPIOG) ? 6 : \
                                   (x == GPIOH) ? 7 : 0)

// IRQ number of stm32l476rg
#define IRQ_NO_EXTI0         6
#define IRQ_NO_EXTI1         7
#define IRQ_NO_EXTI2         8
#define IRQ_NO_EXTI3         9
#define IRQ_NO_EXTI4         10
#define IRQ_NO_EXTI9_5       23
#define IRQ_NO_EXTI15_10     40

// genereic macros
#define ENABLE 			1
#define DISABLE 		0
#define SET				ENABLE
#define RESET			DISABLE
#define	GPIO_PIN_SET 	SET
#define	GPIO_PIN_RESET 	RESET
#define FLAG_RESET 		RESET
#define FLAG_SET 		SET

#endif /* INC_STM32L476XX_H_ */
