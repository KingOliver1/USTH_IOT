#ifndef __CONTROL_H
#define __CONTROL_H

extern float Position_KP,Position_KI,Position_KD;//位置式PID参数
extern float Velocity_KP,Velocity_KI;//增量式PID参数
extern float TargetPositin,CurrentPosition;//期望位置，当前位置
extern int a[4];
#endif

