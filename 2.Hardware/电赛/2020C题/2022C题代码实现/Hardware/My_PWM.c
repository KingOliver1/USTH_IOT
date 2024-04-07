#include "stm32f10x.h"                  // Device header

void My_PWM_init(void)
{
	//初始化外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//重映射PA15和PB3并解除JTAG调试功能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	

	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出，片上外设TIM控制
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出，片上外设TIM控制
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//配置定时器时钟源
	TIM_InternalClockConfig(TIM2);
	
	//初始化时基单元
	/*由于电机是由线圈和磁铁组成的转动时会有噪声，
	所以控制PWM的输出频率大于人耳的听觉频率。*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStruct.TIM_Period = 7200-1;				//ARR  PWM:Freq:72MHZ/(PSC+1)/(ARR+1)
	TIM_TimeBaseInitStruct.TIM_Prescaler =1-1 ;			//PSC 
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//初始化输出比较单元
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;
	TIM_OC1Init(TIM2,&TIM_OCInitStruct);
    TIM_OC2Init(TIM2,&TIM_OCInitStruct);
	TIM_OC4Init(TIM2,&TIM_OCInitStruct);
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);
	
	//定时器使能
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);

}

void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2,Compare);

}
void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);
}

void PWM_SetCompare4(uint16_t Compare)
{
	TIM_SetCompare4(TIM2, Compare);
}
