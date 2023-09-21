#define PERIPH_BASE      ((unsigned int)0x40000000)
	
#define APB2PERIPH_BASE  (PERIPH_BASE + 0x00010000)

#define GPIOB_BASE       (APB2PERIPH_BASE + 0x0C00)
#define GPIOE_BASE       (APB2PERIPH_BASE + 0x1800)

#define GPIOB_CRL 	 	 *(unsigned int*)(GPIOB_BASE+0x00)
#define GPIOB_CRH 	 	 *(unsigned int*)(GPIOB_BASE+0x04)
#define GPIOB_IDR 	 	 *(unsigned int*)(GPIOB_BASE+0x08)
#define GPIOB_ODR 	 	 *(unsigned int*)(GPIOB_BASE+0x0C)
#define GPIOB_BSRR 	 	 *(unsigned int*)(GPIOB_BASE+0x10)
#define GPIOB_BRR 	 	 *(unsigned int*)(GPIOB_BASE+0x14)
#define GPIOB_LCKR 	 	 *(unsigned int*)(GPIOB_BASE+0x18)

#define GPIOE_CRL 	 	 *(unsigned int*)(GPIOE_BASE+0x00)
#define GPIOE_CRH 	 	 *(unsigned int*)(GPIOE_BASE+0x04)
#define GPIOE_IDR 	 	 *(unsigned int*)(GPIOE_BASE+0x08)
#define GPIOE_ODR 	 	 *(unsigned int*)(GPIOE_BASE+0x0C)
#define GPIOE_BSRR 	 	 *(unsigned int*)(GPIOE_BASE+0x10)
#define GPIOE_BRR 	 	 *(unsigned int*)(GPIOE_BASE+0x14)
#define GPIOE_LCKR 	 	 *(unsigned int*)(GPIOE_BASE+0x18)


#define AHBPERIPH_BASE   (PERIPH_BASE + 0x20000)

#define RCC_BASE 		 (AHBPERIPH_BASE + 0x1000)
#define RCC_APB2ENR 	 *(unsigned int*)(RCC_BASE+0x18)
