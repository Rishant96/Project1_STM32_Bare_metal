#ifndef STM32F103_H
#define STM32F103_H

#define PERIPH_BASE 	((uint32_t)0x40000000)
#define APB2_BASE         (PERIPH_BASE + 0x00010000)
#define AHB_BASE    	(PERIPH_BASE + 0x00020000)

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_t;

#define RCC               ((RCC_t *)(AHB_BASE + 0x1000))


#define RCC_CR_HSION      (1U << 0)
#define RCC_CR_HSIRDY     (1U << 1)
#define RCC_CR_HSEON      (1U << 16)
#define RCC_CR_HSERDY     (1U << 17)
#define RCC_CR_PLLON      (1U << 24)
#define RCC_CR_PLLRDY     (1U << 25)


#define RCC_CFGR_SW_HSI   (0U << 0)
#define RCC_CFGR_SW_HSE   (1U << 0)
#define RCC_CFGR_SW_PLL   (2U << 0)
#define RCC_CFGR_SWS_MASK (3U << 2)
#define RCC_CFGR_SWS_PLL  (2U << 2)
#define RCC_CFGR_PPRE1_Pos 8U
#define RCC_CFGR_PPRE1_DIV2  (4U << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PLLSRC   (1U << 16)
#define RCC_CFGR_PLLMUL9  (7U << 18)

#define RCC_APB2ENR_AFIOEN   (1U << 0)
#define RCC_APB2ENR_IOPAEN   (1U << 2)
#define RCC_APB2ENR_IOPBEN   (1U << 3)
#define RCC_APB2ENR_IOPCEN   (1U << 4)
#define RCC_APB2ENR_USART1EN (1U << 14)


typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_t;

#define GPIOA             ((GPIO_t *)(APB2_BASE + 0x0800))
#define GPIOB             ((GPIO_t *)(APB2_BASE + 0x0C00))
#define GPIOC             ((GPIO_t *)(APB2_BASE + 0x1000))


typedef struct {
    volatile uint32_t ACR;          /* 0x00 */
    volatile uint32_t KEYR;         /* 0x04 */
    volatile uint32_t OPTKEYR;      /* 0x08 */
    volatile uint32_t SR;           /* 0x0C */
    volatile uint32_t CR;           /* 0x10 */
    volatile uint32_t AR;           /* 0x14 */
    volatile uint32_t _reserved;    /* 0x18 */
    volatile uint32_t OBR;          /* 0x1C */
    volatile uint32_t WRPR;         /* 0x20 */
} FLASH_t;

#define FLASH_R					 ((FLASH_t *)0x40022000)
#define FLASH_ACR_LATENCY_2WS    (2U << 0U) /* 2 wait states for frequencies 48-72 MHz */
#define FLASH_ACR_PRFTBE  		 (1U << 4U) /* enabling Prefetch buffer improves performance */


typedef struct {
    volatile uint32_t SR; 
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_t;

#define USART1            ((USART_t *)(APB2_BASE + 0x3800))

#define USART_SR_TXE      (1U << 7)

#endif