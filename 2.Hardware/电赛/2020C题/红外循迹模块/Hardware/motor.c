#include "stm32f10x.h"                  // Device header
#include "My_PWM.h"
void motor_init(void)
{
	//初始化外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ; //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ; //推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//初始化PWM
	My_PWM_init();
}

void Motor_SetAhead_LeftSpeed(int16_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		PWM_SetCompare1(Speed);
	}
	else if(Speed==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		PWM_SetCompare1(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		PWM_SetCompare1(-Speed);
	}
}

//设置右边电机速度
void Motor_SetAhead_RightSpeed(int16_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		PWM_SetCompare2(Speed);
	}
	else if(Speed==0)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		PWM_SetCompare2(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		PWM_SetCompare2(-Speed);
	}
}

//设置后左边电机速度
void Motor_SetBack_LeftSpeed(int16_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		PWM_SetCompare3(Speed);
	}
	else if(Speed==0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		PWM_SetCompare3(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(-Speed);
	}
}

//设置后右边电机速度
void Motor_SetBack_RightSpeed(int16_t Speed)
{
	if (Speed > 0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		GPIO_ResetBits(GPIOC,GPIO_Pin_5);
		PWM_SetCompare4(Speed);
	}
	else if(Speed==0)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_4);
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		PWM_SetCompare4(Speed);
	}
	else
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_5);
		GPIO_ResetBits(GPIOC,GPIO_Pin_4);
		PWM_SetCompare4(-Speed);
	}
}

//限幅函数
void Limit(int *motorAL,int *motorAR,int* motorBL,int* motorBR)
{
	if(*motorAL > 7200) *motorAL=7200;
	if(*motorAL <-7200) *motorAL=-7200;
	
	if(*motorAR > 7200) *motorAR=7200;
	if(*motorAR <-7200) *motorAR=-7200;
	
	if(*motorBL > 7200) *motorBL=7200;
	if(*motorBL <-7200) *motorBL=-7200;
	
	if(*motorBR > 7200) *motorBR=7200;
	if(*motorBR <-7200) *motorBR=-7200;
	
}
