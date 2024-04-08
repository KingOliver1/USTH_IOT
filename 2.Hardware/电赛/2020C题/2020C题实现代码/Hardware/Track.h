#ifndef __TRACK_H
#define __TRACK_H

void Infrared_init(void);
void Track(void);
int Infrared_Track(void);
extern int Left_AD,Left_Max,Left_Span,Left_Threshold;
extern int Right_AD,Right_Max,Right_Span,Right_Threshold;
extern int Data_In,Right_Data_Out,D_AD_VALUE,Left_Data_Out,Mid_AD;

#endif
