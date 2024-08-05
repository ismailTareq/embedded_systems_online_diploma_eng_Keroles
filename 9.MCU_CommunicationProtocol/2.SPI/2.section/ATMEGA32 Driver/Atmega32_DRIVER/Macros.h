/*
 * Macros.h
 *
 * Created: 7/4/2024 3:59:38 PM
 *  Author: ismail
 */ 


#ifndef MACROS_H_
#define MACROS_H_
//---------------------------------------

//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define SET_BIT(REG,BIT_NUM)    REG|=(1<<BIT_NUM)
#define CLR_BIT(REG,BIT_NUM)    REG&=(~(1<<BIT_NUM))
#define TOG_BIT(REG,BIT_NUM)    REG^=(1<<BIT_NUM)
#define READ_BIT(REG,BIT_NUM)    ((REG>>BIT_NUM)&1)

#define BIT_IS_SET(REG,BIT)     (REG & (1<<BIT))
#define BIT_IS_CLEAR(REG,BIT)   (!(REG & (1<<BIT)))

//---------------------------------------
typedef unsigned char ReturnType;

#define E_OK         (ReturnType)0x01
#define E_NOT_OK     (ReturnType)0x00
#endif /* MACROS_H_ */