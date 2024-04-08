#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
#include "motor.h"

int TargetPositin,CurrentPosition;//目标位置，实际位置
int TargetVelocity,CurrentVelocity;//目标速度，实际速度
int Position_KP,Position_KI,Position_KD;//位置式PID参数
int Velocity_KP,Velocity_KI;//增量式PID参数

int TargetP = 100 ;//测试参数，目标距离100cm

int Position_Out,Velocity_Out;//位置环速度环输出量
int motorAL,motorBL;
int motorAR,motorBR;

int Position_PID(int CurrentPosition,int TargetPositin)//位置式PID
{
	static float Bias,ControlOutput,Integral_bias,Last_bias;
	Bias=TargetPositin-CurrentPosition;
	Integral_bias+=Bias;
	ControlOutput= Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_bias);
	return ControlOutput;
}

int Incremental_PI(int CurrentVelocity,int TargetVelocity)//增量式PID
{
	static float Bias,ControlVelocity,Last_bias;
	Bias=TargetVelocity-CurrentVelocity;
	ControlVelocity= Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;
	Last_bias+=Bias;
	return ControlVelocity;
}

void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
	{
		int PWM_Out;
		CurrentPosition=0;
		//1.采集编码器数据
		
		float S = (Speed[1]+Speed[2]+Speed[3]+Speed[0])/4*6.5*3.14*1;// s=v*t v= n*Π*l n为电机转速，
		CurrentPosition +=S;  //s为走过的路程，即在一次中断时间内走过的距离
		CurrentVelocity=(Speed[1]+Speed[2]+Speed[3]+Speed[0])/4;
		//2.将数据压入闭环控制中，计算输出量
		
		Position_Out=Position_PID(CurrentPosition,TargetP);//外环控制，输出量为内环的输入量
		Velocity_Out=Incremental_PI(CurrentVelocity,Position_Out);//内环控制，输出量为期望控制速度
		
		PWM_Out = Velocity_Out;//最终输出
		
		//3.把输出量加载到电机上
		
		motorAL = PWM_Out;
		motorAR = PWM_Out;
		motorBL = PWM_Out;
		motorBR = PWM_Out;
		
		Limit(&motorAL,&motorAR,&motorBL,&motorBR); //PWM限幅
		
		//加载到电机上
//		Motor_SetAhead_LeftSpeed(motorAL);
//		Motor_SetAhead_RightSpeed(motorAR);
		Motor_SetBack_LeftSpeed(motorBL);
		Motor_SetBack_RightSpeed(motorBR);
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}
}
