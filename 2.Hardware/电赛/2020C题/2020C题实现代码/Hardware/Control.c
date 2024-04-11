#include "stm32f10x.h"                  // Device header
#include "Encoder.h"
#include "motor.h"
#include "Serial.h"
int a[4];
float  TargetPositin,CurrentPosition;//目标位置，实际位置
int TargetVelocity,CurrentVelocity;//目标速度，实际速度
float Position_KP,Position_KI,Position_KD;//位置式PID参数
float Velocity_KP,Velocity_KI;//增量式PID参数

int TargetP = 1000 ;//测试参数，设置了一个目标脉冲数
int TargetV = 10;
int Position_Out,Velocity_Out;//位置环速度环输出量
int motorAL,motorBL;
int motorAR,motorBR;

int Position_PID(float  CurrentPosition,float TargetPositin)//位置式PID
{
	static float Bias,ControlOutput,Integral_bias,Last_bias;
	Bias=TargetPositin-CurrentPosition;
	Integral_bias+=Bias;
	ControlOutput= Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(Bias-Last_bias);
	Last_bias=Bias;
	return ControlOutput;
}

int Incremental_PI(int CurrentVelocity,int TargetVelocity)//增量式PID
{
	static float Bias,ControlVelocity,Last_bias;
	Bias=TargetVelocity-CurrentVelocity;
	ControlVelocity+= Velocity_KP*(Bias-Last_bias)+Velocity_KI*Bias;
	Last_bias=Bias;
	return ControlVelocity;
}

void TIM7_IRQHandler(void)
{
	
	int PWM_Out;
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) == SET)
	{
		
		//1.采集编码器数据
		a[0]=Encoder_Get3();
		a[1]=Encoder_Get4();
		a[2]=Encoder_Get5();
		a[3]=Encoder_Get8();
		float S = ((a[1]+a[2]+a[3]+a[0])/4)*6.5*3.14*0.001*0.5;// s=v*t v= n*Π*l n为电机转速，
		CurrentPosition +=S; //获取编码器的脉冲数并更新当前脉冲数

		CurrentVelocity=(a[1]+a[2]+a[3]+a[0])/4*6.5*3.14*0.001;
		//2.将数据压入闭环控制中，计算输出量
		
		Position_Out=Position_PID(CurrentPosition,TargetP);//外环控制，输出量为内环的输入量
		Velocity_Out=Incremental_PI(CurrentVelocity,Position_Out);//内环控制的输出量为总输出量
		
		PWM_Out = Velocity_Out*1000/(6.5*3.14);//最终输出
		
		//3.把输出量加载到电机上
		
		motorAL = PWM_Out;
		motorAR = PWM_Out;
		motorBL = PWM_Out;
		motorBR = PWM_Out;
		
		Limit(&motorAL,&motorAR,&motorBL,&motorBR); //PWM限幅
		
		//加载到电机上
		Motor_SetAhead_LeftSpeed(motorAL);
		Motor_SetAhead_RightSpeed(motorAR);
		Motor_SetBack_LeftSpeed(motorBL);
		Motor_SetBack_RightSpeed(motorBR);
		Serial_Printf("any:%f\n",CurrentPosition);//通过串口把当前位置输出到VOFA上，通过全局变量k在main里面调参
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	}
}
