#ifndef __MOTOR_H
#define __MOTOR_H

void motor_init(void);
void Motor_SetAhead_LeftSpeed(int16_t Speed);
void Motor_SetAhead_RightSpeed(int16_t Speed);
void Motor_SetBack_LeftSpeed(int16_t Speed);
void Motor_SetBack_RightSpeed(int16_t Speed);
void Limit(int *motorAL,int *motorAR,int* motorBL,int* motorBR);
	
#endif
