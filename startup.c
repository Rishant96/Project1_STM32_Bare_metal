#include <stdint.h>

extern int main(void);

extern uint32_t _estack;
extern uint32_t _sdata, _edata;
extern uint32_t _sbss, _ebss;
extern uint32_t _etext;


/* Handlers */
void Reset_Handler(void);
void Default_Handler(void);

__attribute__((section(".isr_vector")))
const void *vector_table[] =
{
    &_estack,          /* Initial stack */
    Reset_Handler,     /* Reset */
    Default_Handler,   /* NMI */
    Default_Handler,   /* HardFault */
    0,0,0,0,0,0,0,
    Default_Handler,   /* SVC */
    0,0,
    Default_Handler,   /* PendSV */
    Default_Handler,   /* SysTick */

    /* External IRQs */
    /* 0..27 omitted */
    Default_Handler
};

void Reset_Handler(void)
{
    /* Copy data */
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    /* Zero BSS */
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;

    main();

    while (1);
}

void Default_Handler(void)
{
    while (1);
}
