#ifndef __ENCODER_H
#define __ENCODER_H

void Encoder_init(void);
int16_t Encoder_Get3(void);
int16_t Encoder_Get4(void);
int16_t Encoder_Get5(void);
int16_t Encoder_Get8(void);
extern int16_t Speed[4];

#endif
