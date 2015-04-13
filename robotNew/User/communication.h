#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "stm32f10x.h"
//*****************************************************************************
//      调参协议
//协议：头$+a为手臂舵机+r或l+1旋转角度+,+2旋转角度+,+3...+,+4...+,+5...+尾#
//			z为四个电机+q,w,e,r前后左右+速度0-999
//					   +t,y,u,i右上，左上，右下，左下+速度0-999
//					   +o,p右转,左转+角度0-360
//					   +s停止
//*****************************************************************************

extern int iValue[6]; 

uint32_t Pow(uint32_t Data,int8_t PowNum);
float getNumber(int start,int end);
void communicationProtocol(void);
void Kinect_Init(void);//体感的协议参数初始化
void Kinect_Analyze(void);//体感协议解析
void Motor_Analyze(void);//电机协议解析
void specialAction_Analyze(void); 
void steeringEngine_Analyze(void); 
void function_Analyze(void);
 
#endif
