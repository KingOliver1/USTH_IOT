#include "stm32f10x.h"                  // Device header
int16_t Speed[4];
void Encoder_init(void)
{	
	//初始化外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，输入编码器的脉冲数据
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//上拉输入，输入编码器的脉冲数据
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision =TIM_CKD_DIV1 ;
	TIM_TimeBaseInitStruct.TIM_CounterMode =TIM_CounterMode_Up ;
	TIM_TimeBaseInitStruct.TIM_Period =65536-1 ;
	TIM_TimeBaseInitStruct.TIM_Prescaler =1-1 ;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICStructInit(&TIM_ICInitStruct); 
	TIM_ICInitStruct.TIM_Channel =TIM_Channel_1 ;
	TIM_ICInitStruct.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	TIM_ICInit(TIM5, &TIM_ICInitStruct);
	TIM_ICInit(TIM8, &TIM_ICInitStruct);
	
	TIM_ICInitStruct.TIM_Channel =TIM_Channel_2 ;
	TIM_ICInitStruct.TIM_ICFilter = 0xF;
	TIM_ICInit(TIM3, &TIM_ICInitStruct);
	TIM_ICInit(TIM4, &TIM_ICInitStruct);
	TIM_ICInit(TIM5, &TIM_ICInitStruct);
	TIM_ICInit(TIM8, &TIM_ICInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_EncoderInterfaceConfig(TIM5,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	TIM_EncoderInterfaceConfig(TIM8,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	TIM_Cmd(TIM5,ENABLE);
	TIM_Cmd(TIM8,ENABLE);
}

int16_t Encoder_Get3(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return Temp;
}	
int16_t Encoder_Get4(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM4);
	TIM_SetCounter(TIM4,0);
	return Temp;
}	
int16_t Encoder_Get5(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM5);
	TIM_SetCounter(TIM5,0);
	return Temp;
}	
int16_t Encoder_Get8(void)
{
	int16_t Temp;
	Temp = TIM_GetCounter(TIM8);
	TIM_SetCounter(TIM8,0);
	return Temp;
}	

void TIM6_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
	{
		Speed [0]=  Encoder_Get3();
		Speed [1]=  Encoder_Get4();
		Speed [2]=  Encoder_Get5();
		Speed [3]=  Encoder_Get8();
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	}
}
