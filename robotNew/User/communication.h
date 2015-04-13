#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "stm32f10x.h"
//*****************************************************************************
//      ����Э��
//Э�飺ͷ$+aΪ�ֱ۶��+r��l+1��ת�Ƕ�+,+2��ת�Ƕ�+,+3...+,+4...+,+5...+β#
//			zΪ�ĸ����+q,w,e,rǰ������+�ٶ�0-999
//					   +t,y,u,i���ϣ����ϣ����£�����+�ٶ�0-999
//					   +o,p��ת,��ת+�Ƕ�0-360
//					   +sֹͣ
//*****************************************************************************

extern int iValue[6]; 

uint32_t Pow(uint32_t Data,int8_t PowNum);
float getNumber(int start,int end);
void communicationProtocol(void);
void Kinect_Init(void);//��е�Э�������ʼ��
void Kinect_Analyze(void);//���Э�����
void Motor_Analyze(void);//���Э�����
void specialAction_Analyze(void); 
void steeringEngine_Analyze(void); 
void function_Analyze(void);
 
#endif
