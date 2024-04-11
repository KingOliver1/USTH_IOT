#include "stm32f10x.h"                  // Device header
#include "Car.h"

int Left_AD,Left_Max,Left_Span,Left_Threshold;
int Right_AD,Right_Max,Right_Span,Right_Threshold;
int Data_In,Right_Data_Out,D_AD_VALUE,Left_Data_Out,Mid_AD;

void Infrared_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_Init(GPIOC,&GPIO_InitStruct);

	Car_init();
}

void Track(void)
{
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&
		   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&
		   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0&&
		   GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==0)
		{
			TIM_Cmd(TIM7, ENABLE);
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==1)
		{	TIM_Cmd(TIM7, DISABLE);
			Car_Stop();
		
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==1)
		{	TIM_Cmd(TIM7, DISABLE);
			Slef_Right();
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==0)
		{	TIM_Cmd(TIM7, DISABLE);
			Turn_Right();
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==1)
		{	TIM_Cmd(TIM7, DISABLE);
			Turn_Right();
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==0)
		{	TIM_Cmd(TIM7, DISABLE);
			Slef_Left();
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==0)
		{	TIM_Cmd(TIM7, DISABLE);
			Turn_Left();
		}
		else if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==1&&
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)==0&&
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)==0)
		{	TIM_Cmd(TIM7, DISABLE);
			Turn_Left();
		}
}

int Infrared_Track(void)
{
	int Data;
	Data_In = Right_AD - Left_AD+D_AD_VALUE;
	Right_Data_Out = (2*Right_Max -Right_AD )*2-Right_Span ;
	Right_Span = (2*Right_Max - Right_AD )*2-(Right_AD - Left_AD+D_AD_VALUE);
	Left_Data_Out = -(2*Left_Max - Left_AD )*2+Left_Span;
	Left_Span = (2*Left_Max - Left_AD )*2-(Left_AD-Right_AD+D_AD_VALUE);
	if(Data_In>=0&&Mid_AD<=Right_Threshold)
	{
		Data =Right_Data_Out;
	}
	else if (Data_In<=0&&Mid_AD<=Left_Threshold)
	{
		Data =Left_Data_Out;
	}
	else if (Right_Threshold<Mid_AD<Right_Threshold)
	{
		Data =Data_In;
	}
	return Data;
}
