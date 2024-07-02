/*
 * macros.h
 *
 * Created: 7/1/2024 7:29:40 PM
 *  Author: ismail
 */ 


#ifndef MACRO_H_
#define MACRO_H_

#define SET_BIT(Reg, Bit_Num) (Reg |= (1 << Bit_Num))
#define CLR_BIT(Reg, Bit_Num) (Reg &= ~(1 << Bit_Num))
#define TOGGLE_BIT(Reg, Bit_Num) (Reg ^= (1 << Bit_Num))
#define READ_BIT(Reg, Bit_Num) ((Reg >> Bit_Num) & 1)

#endif /* MACRO_H_ */