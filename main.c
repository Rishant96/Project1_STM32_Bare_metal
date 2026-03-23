#include "MCU_STM32.h"

static inline void uart_putc(char c)
{
    while (!(USART1->SR & USART_SR_TXE));
    USART1->DR = (uint32_t)c;
}

static inline void uart_write(const char *s)
{
    while (*s) {
        uart_putc(*s++);
    }
}

static void clock_init(void)
{
	FLASH_R->ACR = FLASH_ACR_LATENCY_2WS | FLASH_ACR_PRFTBE;
	
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));
	
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL9;
	
	/* Turn on PLL and wait */
	while (!(RCC->CR & RCC_CR_PLLRDY));
	
	/* Switch system clock to PLL */
	RCC->CFGR = (RCC->CFGR & ~(3U << 0)) | RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS_MASK) != RCC_CFGR_SWS_PLL);
}

static void gpio_init(void)
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN
				  |  RCC_APB2ENR_IOPCEN
				  |  RCC_APB2ENR_AFIOEN
				  |  RCC_APB2ENR_USART1EN;
	
	/* Setup Pin 13 */
	GPIOC->CRH &= ~(0xFU << 20);
	GPIOC->CRH &=  (0x2U << 20);
	
	/* Setup Pin 0 */
	GPIOA->CRL &= ~(0xFU << 0);
	GPIOA->CRL |=  (0x8U << 0);
	GPIOA->ODR |=  (1U << 0);	/* Pull-up*/
	
	/* Setup Pin 9 */
	GPIOA->CRH &= ~(0xFU << 4);
	GPIOA->CRH |=  (0xBU << 4);
}

int main(void)
{
	clock_init();
	gpio_init();
	
	uart_write("Project 1 - Bare Metal STM32 Programming\r\n");
	
	for (;;) { } /* Using interrupts for flow control */
}