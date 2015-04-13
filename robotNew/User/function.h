#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "stm32f10x.h"

#define LIST1_NUM         50			//����һ���������

#define DJ1_INIT_DUTY     75
#define DJ2_INIT_DUTY     78
#define DJ3_INIT_DUTY     75
#define DJ4_INIT_DUTY     75
#define DJ5_INIT_DUTY     75
#define DJ6_INIT_DUTY     75
#define DJ7_INIT_DUTY     75
#define DJ8_INIT_DUTY     75
#define DJ9_INIT_DUTY     75
#define DJ10_INIT_DUTY    75
#define DJ11_INIT_DUTY    75
#define DJ12_INIT_DUTY    75
/*
 * ������
 * ��12�����
 * �����ֵ������ٵ�ͷ
 * �Ҽ�ǰ��->0 �Ҽ�����->1 ����->2 ������->3 ����צ->4
 * ���ǰ��->5 �������->6 ����->7 ������->8 ����צ->9
 * ͷ������ת->10 ͷǰ���ͷ->11
 */

//�����б�ṹ��
typedef struct
{
  	uint32_t Start_Time; //�����ʼʱ��            
	uint32_t End_Time; 	 //�������ʱ��
	u8 Start_Duty;		 //�����ʼ��PWM
	u8 End_Duty;		 //���������PWM
	u8 DJ_Num;			 //�����	
	float add;			 //���ռ�ձ���ʱ��ı�����add*(��ǰʱ��-�ö����ʼʱ��)+�������PWM
}Move_List;

extern __IO u32 TimeAll;						//ȫ��ʱ�䣬��ϵͳʱ���л����
extern __IO u32 End_Num;						//���׶�������������
extern Move_List function_list1[LIST1_NUM];		//����1�б�

//������������б���
void Function_Add_Son(uint16_t Function_Num,uint32_t Start_Time_t, uint32_t End_Time_t, u8 Start_Duty_t, u8 End_Duty_t, u8 DJ_Num_t);
void Function_Add_All(void);//��ȫ��������ȫ������
void Function_Init(void);
void Function_Do(u32 time);
void steerMoter1(int delay);
void testAllFunction(void);
void displayAllSteer(void);
#endif
