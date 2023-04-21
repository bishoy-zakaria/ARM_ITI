/**************************************************/
/*				File name: Bit_Math.h    	      */ 
/*				Author: Bishoy Zakaria      	  */
/*				Date: 1/12/2022                	  */
/*				company: ITI            		  */
/**************************************************/
#include "STD_Types.h"

#define REG_Size           	 		8                    									//define the maximum size of the register by bits
#define SET_BIT(REG,BIT)			(REG |= (1<<(BIT)))   									//set the bit in the register 
#define CLR_BIT(REG,BIT)			(REG &= ~(1<<(BIT))) 									//clear the bit in the register 
#define TGL_BIT(REG,BIT)			(REG ^=(1<<BIT)) 	 									//toggel the bit in the reg
#define GET_BIT(REG,BIT)			((1)&(REG>>BIT))	 									//get the bit in register
#define SET_HIG_NIB(REG)			(REG |= ((15u)<<4))  									//set the high nipples in the register
#define CLR_HIG_NIB(REG)			(REG &= ~((15u)<<4))  									//clear the high nipples in the register
#define GET_HIG_NIB(REG)			((REG&((15u)<<4))>>4)  									//get the high nipples in the register
#define TGL_HIG_NIB(REG)			(REG ^= ((15u)<<4))   									// toggel the high nipples in the register
#define SET_LOW_NIB(REG)			(REG |= (15u))        									//set the low nipples in the register
#define CLR_LOW_NIB(REG)			(REG &= ~(15u))	  	  									//clear the low nipples in the register
#define GET_LOW_NIB(REG)			(REG & (15u))	  	  									//get the low nipples in the register
#define TGL_LOW_NIB(REG)			(REG ^= (15u))        									// toggel the low nipples in the register
#define ASSIGN_REG(REG,VALUE)		(REG = VALUE)		  									//Assign a value in the register
#define SHIFT_RIGHT(REG,VALUE)		(REG = REG>>VALUE)                 						//shift right the register
#define SHIFT_LIFT(REG,VALUE)		(REG = REG<<VALUE)                 						//shift left the register
#define CLR_RIGHT_SHIFT(REG,VALUE)	(REG = ((REG >> VALUE) | (REG << (REG_Size - VALUE))))  //circular right the register 
#define CLR_LEFT_SHIFT(REG,VALUE)	(REG = ((REG << VALUE) | (REG >> (REG_Size - VALUE))))  //circular left the register 

/*assign the high nipple wih value*/
#define ASSIGN_HIG_NIB(REG,VALUE)	do{\
									if(VALUE<=15){\
									CLR_HIG_NIB(REG);\
									(REG |= (VALUE<<4));}\
									}while(0)
										
/*assign the low nipple wih value*/
#define ASSIGN_LOW_NIB(REG,VALUE)	do \
									{\
										if(VALUE<=15){\
											CLR_LOW_NIB(REG);\
										(REG |= (VALUE));}\
									}while(0)
										
									
u32 WriteBinaryVal(u32 reg ,u32 value, u32 startbit, u32 len);									