#ifndef __PWMMOTER_H_
#define __PWMMOTER_H_

#include "stm32f10x.h"

/*1为前面的电机		   TIM3 CCR1->PA6 GPIO->PC0
 *2为后面的电机		   TIM3 CCR2->PA7 GPIO->PC1
 *3为左面的电机		   TIM3 CCR3->PB0 GPIO->PC2
 *4为右面的电机		   TIM3 CCR3->PB1 GPIO->PC3
 *往左为正转
 *往前为正转
 */
#define MORTOR_SPEED 200 //范围在0-400
#define ZHENG_ZHUAN 1
#define FAN_ZHUAN   0
#define MORTOR_START 1
#define MORTOR_STOP 0
#define MORTOR_TIEBIAN_DECREASE -250 //贴边时的速度

extern int moterState;//0为停止，1为往前，2为往后，3为往左，4为往右
					    //5为右上，6为左上，7为右下，8为左下
						//9为右转，10为左转
void motor1(u8 dir, u8 state, int speed_add);	  //moter1为前面的电机
void motor2(u8 dir, u8 state, int speed_add);	  //moter2为后面的电机
void motor3(u8 dir, u8 state, int speed_add);	  //moter3为左面的电机
void motor4(u8 dir, u8 state, int speed_add);	  //moter4为右面的电机

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
