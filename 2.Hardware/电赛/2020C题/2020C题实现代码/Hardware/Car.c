#include "stm32f10x.h"                  // Device header
#include "motor.h"

void Car_init(void)
{
	
	motor_init();

}

void Go_Ahead(void)
{
	
	Motor_SetAhead_LeftSpeed(3600);
	Motor_SetAhead_RightSpeed(3600);
	Motor_SetBack_LeftSpeed(3600);
	Motor_SetBack_RightSpeed(3600);

}

void Go_Back(void)
{
	
	
	Motor_SetAhead_LeftSpeed(-3600);
	Motor_SetAhead_RightSpeed(-3600);
	Motor_SetBack_LeftSpeed(-3600);
	Motor_SetBack_RightSpeed(-3600);

}

void Turn_Left(void)
{
	
	Motor_SetAhead_LeftSpeed(0);
	Motor_SetBack_LeftSpeed(0);
	Motor_SetAhead_RightSpeed(3600);
	Motor_SetBack_RightSpeed(3600);
	

}

void Turn_Right(void)
{
	
	Motor_SetAhead_LeftSpeed(3600);
	Motor_SetBack_LeftSpeed(3600);
	Motor_SetAhead_RightSpeed(0);
	Motor_SetBack_RightSpeed(0);

}

void Slef_Left(void)
{
	
	Motor_SetAhead_LeftSpeed(-3600);
	Motor_SetBack_LeftSpeed(-3600);
	Motor_SetAhead_RightSpeed(3600);
	Motor_SetBack_RightSpeed(3600);
//	Motor_SetLeftSpeed(-50);
//	Motor_SetRightSpeed(50);
	
}

void Slef_Right(void)
{
	
	Motor_SetAhead_LeftSpeed(3600);
	Motor_SetBack_LeftSpeed(3600);
	Motor_SetAhead_RightSpeed(-3600);
	Motor_SetBack_RightSpeed(-3600);
//	Motor_SetLeftSpeed(50);
//	Motor_SetRightSpeed(-50);
	
}

void Car_Stop(void)
{
	
	Motor_SetAhead_LeftSpeed(0);
	Motor_SetBack_LeftSpeed(0);
	Motor_SetAhead_RightSpeed(0);
	Motor_SetBack_RightSpeed(0);
//	Motor_SetLeftSpeed(0);
//	Motor_SetRightSpeed(0);

}
