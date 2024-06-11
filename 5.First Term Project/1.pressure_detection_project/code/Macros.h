#ifndef MACROS_H
#define	MACROS_H

#define GPIO_HIGH 1
#define GPIO_LOW 0

#define SET_BIT(REG,BIT_NUM)    REG|=(1<<BIT_NUM)
#define CLR_BIT(REG,BIT_NUM)    REG&=(~(1<<BIT_NUM))
#define TOG_BIT(REG,BIT_NUM)    REG^=(1<<BIT_NUM)
#define READ_BIT(REG,BIT_NUM)    ((REG>>BIT_NUM)&1)
 
#define BIT_IS_SET(REG,BIT)     (REG & (1<<BIT))
#define BIT_IS_CLEAR(REG,BIT)   (!(REG & (1<<BIT)))

#endif	// MACROS_H 

