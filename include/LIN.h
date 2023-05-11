#ifndef LIN_H
#define LIN_H


typedef enum
{
	LIN_Master=0,
	LIN_Slave
}LIN_Mode_t;

typedef enum
{
	LIN_Ready=0,
	LIN_Bussy
}LIN_Status_t;

void LIN_Master_Task(void);
LIN_Status_t LIN_Get_Status(void);

#endif
