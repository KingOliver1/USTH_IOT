#include "stm32f10x.h"                  // Device header
#include "Car.h"
#include "Track.h"
#include "motor.h"
#include "Encoder.h"
#include "Control.h"
#include "Timer.h"
#include "OLED.h"

int main(void)
{	
	OLED_Init();
	Timer6_Init();
	motor_init();
	Encoder_init();
	
//	TIM6_IRQHandler();
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStruct);
//	
//	Infrared_init();
	OLED_ShowString(1 ,1, "ALSpeed:");
	OLED_ShowString(2 ,1, "ARSpeed:");
	OLED_ShowString(3 ,1, "BLSpeed:");
	OLED_ShowString(4 ,1, "BRSpeed:");
	
	OLED_ShowSignedNum(1, 8,Speed [0], 7);
	OLED_ShowSignedNum(2, 8, Speed [2], 7);
	OLED_ShowSignedNum(3, 8, Speed [1], 7);
	OLED_ShowSignedNum(4, 8, Speed [3], 7);
	
//	GPIO_InitTypeDef GPIO_InitStruct1;
//	GPIO_InitStruct1.GPIO_Pin = GPIO_Pin_15;
//	GPIO_InitStruct1.GPIO_Mode = GPIO_Mode_Out_PP ; //推挽输出
//	GPIO_InitStruct1.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStruct1);
	
	while(1)
	{
		OLED_ShowSignedNum(1, 8,Speed [0], 7);
		OLED_ShowSignedNum(2, 8, Speed [2], 7);
		OLED_ShowSignedNum(3, 8, Speed [1], 7);
		OLED_ShowSignedNum(4, 8, Speed [3], 7);
//		GPIO_ResetBits (GPIOA, GPIO_Pin_8);
//		GPIO_SetBits(GPIOB,GPIO_Pin_14);
//		GPIO_SetBits(GPIOB,GPIO_Pin_15);
//		Motor_SetAhead_LeftSpeed(6000);
//		Motor_SetAhead_RightSpeed(6000);
//		Motor_SetBack_LeftSpeed(6000);
//		Motor_SetBack_RightSpeed(6000);
		
		
	}

}





