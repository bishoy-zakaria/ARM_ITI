#ifndef LIN_SLAVE_H
#define LIN_SLAVE_H


typedef enum
{
	LIN_Slave_Ready=0,
	LIN_Slave_Bussy
}LIN_Slave_Status_t;

void LIN_Slave_Task(void);
void LIN_Slave_Check_ID(u8 Slave_RX_ID);
void LIN_Slave_Response(void);
LIN_Slave_Status_t LIN_Slave_GetStatus(void);


#endif
