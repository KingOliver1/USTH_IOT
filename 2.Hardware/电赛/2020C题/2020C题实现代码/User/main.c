#include "stm32f10x.h"                  // Device header
#include "Track.h"
#include "motor.h"
#include "Encoder.h"
#include "Control.h"
#include "Timer.h"
#include "OLED.h"
#include "Serial.h"


int main(void)
{	TargetPositin=100;
	CurrentPosition=0;//由于全局变量的原因，在main函数启动前该变量应该主动清零，否则进中断后，该变量未清零将会造成参数混乱
	PWM_MAX=7200;
	PWM_MIN=-7200;
	Position_KP=0.08,Position_KI=0,Position_KD=78;//位置式PID参数
	Velocity_KP=1.008,Velocity_KI=0.006;//增量式PID参数
	OLED_Init();
	Timer7_Init();
	motor_init();
	Encoder_init();
	Serial_Init();
//	Infrared_init();

	OLED_ShowString(1 ,1, "ALSpeed:");
	OLED_ShowString(2 ,1, "ARSpeed:");
	OLED_ShowString(3 ,1, "BLSpeed:");
	OLED_ShowString(4 ,1, "BRSpeed:");

	Motor_SetAhead_LeftSpeed(3000);
	Motor_SetAhead_RightSpeed(3000);
	Motor_SetBack_LeftSpeed(3000);
	Motor_SetBack_RightSpeed(3000);
	while(1)
	{
		OLED_ShowSignedNum(1, 8, a[0], 7);
		OLED_ShowSignedNum(2, 8, a[2], 7);
		OLED_ShowSignedNum(3, 8, a[1], 7);
		OLED_ShowSignedNum(4, 8, a[3], 7);	
		
//		Track();

	}

}





