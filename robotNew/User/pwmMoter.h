#ifndef __PWMMOTER_H_
#define __PWMMOTER_H_

#include "stm32f10x.h"

/*1Ϊǰ��ĵ��		   TIM3 CCR1->PA6 GPIO->PC0
 *2Ϊ����ĵ��		   TIM3 CCR2->PA7 GPIO->PC1
 *3Ϊ����ĵ��		   TIM3 CCR3->PB0 GPIO->PC2
 *4Ϊ����ĵ��		   TIM3 CCR3->PB1 GPIO->PC3
 *����Ϊ��ת
 *��ǰΪ��ת
 */
#define MORTOR_SPEED 200 //��Χ��0-400
#define ZHENG_ZHUAN 1
#define FAN_ZHUAN   0
#define MORTOR_START 1
#define MORTOR_STOP 0
#define MORTOR_TIEBIAN_DECREASE -250 //����ʱ���ٶ�

extern int moterState;//0Ϊֹͣ��1Ϊ��ǰ��2Ϊ����3Ϊ����4Ϊ����
					    //5Ϊ���ϣ�6Ϊ���ϣ�7Ϊ���£�8Ϊ����
						//9Ϊ��ת��10Ϊ��ת
void motor1(u8 dir, u8 state, int speed_add);	  //moter1Ϊǰ��ĵ��
void motor2(u8 dir, u8 state, int speed_add);	  //moter2Ϊ����ĵ��
void motor3(u8 dir, u8 state, int speed_add);	  //moter3Ϊ����ĵ��
void motor4(u8 dir, u8 state, int speed_add);	  //moter4Ϊ����ĵ��

void motor_straight(int speed);
void motor_back(int speed);
void motor_left(int speed);
void motor_right(int speed);

void motor_stop(void);
void motor_stopRightLeft(void);
void motor_stopStraightBack(void);

void motor_rightStraight(int speed);
void motor_leftStraight(int speed);
void motor_leftBack(int speed);
void motor_rightBack(int speed);

void motor_leftRound(int angel);
void motor_rightRound(int angel);
void motor_leftRound1(void);
void motor_rightRound1(void);

void moter_1_1(void);

void TIM3GPIO_Init(void);
void Tim3_Configuration(void);
void CarGPIO_Init(void);
void Car_Init(void);

#endif
