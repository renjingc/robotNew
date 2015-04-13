#include "communication.h"
#include "pwmMoter.h"
#include "usart1.h"
#include "delay.h"
#include "usart1.h"
#include "stepperMoter.h"
#include "function.h"

int iValue[6];
int sValue[12];
extern __IO u8 receive_count;
extern __IO u8 receive_complete_flag;
extern __IO u8 receive_temp[30];
void Kinect_Init(void)
{
	int i;
	for(i=0;i<5;i++)
		iValue[i]=0;
}
//*****************************************************************************
//      数字转换
//*****************************************************************************
uint32_t Pow(uint32_t Data,int8_t PowNum)
{
  uint32_t temp = Data;
  if(PowNum == 0)
  {
    return 1;
  }
  while(PowNum > 1)
  {
    Data *= temp;
    PowNum--;
  }
  return Data;
}
float getNumber(int start,int end)
{
  uint32_t temp=0;
  float value=0.0;

  int8_t circleCnt=0;
  int8_t point=0; //用来记录浮点数的小数点位置

	for(circleCnt=start;circleCnt < end;circleCnt++)
	{
		if(receive_temp[circleCnt] != '.')
	    {
	    	temp = (receive_temp[circleCnt] - '0') + temp * 10;
	    }
	    else
	    {
	        point = circleCnt;
	    }
	}
	if(point)
	{
	    value = (float)temp / Pow(10,receive_count - point - 2);
	}
	else
	{
	    value=(float)temp;
	}
	return value;
}
//a体感时，1为左肩前后，2为左肩左右，3为左肘，4为右肩前后，5为右肩左右，6为右肘
void Kinect_Analyze(void)
{
  	int i,j;
  	float value=0.0;
  	int8_t circleCnt=0;
  	int douhao[5]={0,0,0,0,0};//记录逗号的位置
	int k=0;
	//GPIO_ResetBits(GPIOB, GPIO_Pin_5);	
	for(i=0;i<5;i++)
	{
		if(i==0)
			j=2;
		else
			j=douhao[i-1]+1;
		for(circleCnt=j;circleCnt<receive_count-1;circleCnt++)
		{
			if(receive_temp[circleCnt] == ',')
			{
				douhao[i]=circleCnt;
				k++;
				break;
			}
		}
	}
	if(k==5)
	{
		printf("Kinect communction OK!\r\n");
	}
	else
	{
		printf("Kinect communction error %d!\r\n",k);
		return;
	}
	//左肩前后1 
	value=getNumber(2,douhao[0]);
	if(value>=75&&value<=125)
	{
		iValue[0]=value;
	}
	else
	{
	}
	//左肩左右2
	value=getNumber(douhao[0]+1,douhao[1]);
	if(value<=77&&value>=41)
	{
		iValue[1]=value;
	}
	else
	{
	}
	//左肘3
	value=getNumber(douhao[1]+1,douhao[2]);
	if(value>=50&&value<=75)
	{
		iValue[2]=value;
	}
	else
	{
	}
	//右肩前后4 
	value=getNumber(douhao[2]+1,douhao[3]);
	if(value>=75&&value<=109)
	{
		iValue[3]=value;
	}
	else
	{
	}
	//左肩左右5
	value=getNumber(douhao[3]+1,douhao[4]);
	if(value>=75&&value<=109)
	{
		iValue[4]=value;
	}
	else
	{
	}
	//左肘6
	value=getNumber(douhao[4]+1,receive_count-1);
	if(value>=75&&value<=109)
	{
		iValue[5]=value;
	}
	else
	{
	}

	printf("%s\r\n",receive_temp);
	printf("1:%d\r\n",iValue[0]);
	printf("2:%d\r\n",iValue[1]);
	printf("3:%d\r\n",iValue[2]);
	printf("4:%d\r\n",iValue[3]);
	printf("5:%d\r\n",iValue[4]);
	printf("6:%d\r\n",iValue[5]);
	TIM_SetCompare1(TIM5,iValue[0]);
	TIM_SetCompare2(TIM5,iValue[1]);		
}
void Motor_Analyze(void)
{
	float value=0.0;
	if(receive_temp[2]=='s')
	{
		motor_stop();
		printf("Motor Stop!\r\n");
	}
	else if(receive_temp[2]=='q')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_straight((int)value);
		printf("Motor straight speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='w')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_back((int)value);
		printf("Motor back speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='e')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_left((int)value);
		printf("Motor left speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='r')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_right((int)value);
		printf("Motor right speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='t')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_rightStraight((int)value);
		printf("Motor rightstraight speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='y')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_leftStraight((int)value);
		printf("Motor leftstraight speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='u')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_rightBack((int)value);
		printf("Motor rightback speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='i')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_leftBack((int)value);
		printf("Motor leftback speed:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='o')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_rightRound((int)value);
		printf("Motor rightround angel:%d!\r\n",(int)value);
	}
	else if(receive_temp[2]=='p')
	{
		motor_stop();
		value=getNumber(3,receive_count-1);
		motor_leftRound((int)value);
		printf("Motor leftround angle:%d!\r\n",(int)value);
	}	 
	else if(receive_temp[2]=='a')
	{
		 motor_stop();
		 motor_leftRound1();
		 printf("Motor leftround still\r\n");
	}
	else if(receive_temp[2]=='d')
	{
		 motor_stop();
		 motor_rightRound1();
		 printf("Motor rightround still\r\n");
	}
	
}
void function_Analyze(void)
{
	 //清空动作列表，且恢复初始化
	 if(receive_temp[2]=='i')
	 {
	 	Function_Init();
	 }
	 //显示当前全部舵机的值
	 else if(receive_temp[2]=='@')
	 {
	 	 displayAllSteer();
	 }
	 //测试全部动作列表
	 else if(receive_temp[2]=='t')
	 {
	 	 testAllFunction();
	 }
	 //注册一个动作
	 else if(receive_temp[2]=='!')
	 {
	 	
	 }
}
void specialAction_Analyze(void)
{
	//执行拿杯子的动作
	if(receive_temp[2]=='1')
	{		
		printf("action:1\r\n");
	}
	//执行握手的动作
	else if(receive_temp[2]=='2')
	{
		printf("action:2\r\n");
	}
	//执行打招呼的动作
	else if(receive_temp[2]=='3')
	{
		printf("action:3\r\n");
	}
}
void steeringEngine_Analyze(void)
{
  	int i,j,x,y;
  	float value=0.0;
  	int8_t circleCnt=0;
  	int douhao[11]={0,0,0,0,0,0,0,0,0,0,0};//记录逗号的位置
	int k=0;	
	for(i=0;i<11;i++)
	{
		if(i==0)
			j=2;
		else
			j=douhao[i-1]+1;
		for(circleCnt=j;circleCnt<receive_count-1;circleCnt++)
		{
			if(receive_temp[circleCnt] == ',')
			{
				douhao[i]=circleCnt;
				k++;
				break;
			}
		}
	}
	if(k==11)
	{
		printf("steeringEngine communction OK!\r\n");
	}
	else
	{
		printf("steeringEngine communction error %d!\r\n",k);
		return;
	}
	for(i=0;i<12;i++)
	{
		if(i==0)
		{
			x=2;
			y=douhao[0];
		}
		else if(i==11)
		{
			x=douhao[10]+1;
			y=receive_count-1;
		}
		else
		{
			x=douhao[i-1]+1;
			y=douhao[i];
		}
		value=getNumber(x,y);
		if(value>=25&&value<=125)
		{
			sValue[i]=value;
		}
		else
		{
		}
	}
	printf("%s\r\n",receive_temp);
	for(i=0;i<12;i++)
	{
		printf("%d:%d\r\n",i,sValue[i]);
	}
	setAllSteeringEngine();
}
//*****************************************************************************
//      调参协议
//协议：头$+a为体感控制手臂舵机+1旋转角度+,+2旋转角度+,+3...+,+4...+,+5...+,+6...尾#
//		头$+z为控制四个电机+q,w,e,r前后左右+速度0-999				  +尾#
//					   	   +t,y,u,i右上，左上，右下，左下+速度0-999
//					       +o,p右转,左转+角度0-360
//					       +s停止
//					       +a,d左转,右转(一直转)																										  +尾#
//		头$+s为控制动作命令+i为初始化全部舵机值
//						   +@为打印全部舵机当前的值
//						   +t为测试当前全部动作
//						   +!为我发送的动作命令+,+Function_Num+,+Start_Time+,+End_Time+,+Start_Duty+,+End_Duty+,+DJ_Num
//		
//		头$+x为特殊命令+1为拿杯子												 尾#
//					   +2为握手
//					   +3为打招呼
//		头$+c为控制11个舵机命令+0号PWM值+,+1号PWM值+,+2号PWM值+,+3号PWM值+,+4号PWM值+,+5号PWM值+,+6号PWM值+,+7号PWM值+,+8号PWM值+,+9号PWM值+,+10号PWM值+,+11号PWM值+尾#
//*****************************************************************************


void communicationProtocol(void)
{
  receive_complete_flag = 0;//清零标志位
  USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);//关闭串口接收中断	
  //体感时的动作命令
  if(receive_temp[1]=='a')
  {
 	 Kinect_Analyze();
  }
  //电机的动作命令
  else if(receive_temp[1]=='z')
  {
	 Motor_Analyze();
  }
  //舵机的动作命令
  else if(receive_temp[1]=='s')
  {
     function_Analyze();
  }
  //特殊动作命令
  else if(receive_temp[1]=='x')
  {
  	 specialAction_Analyze();
  }
  //舵机控制命令
  else if(receive_temp[1]=='c')
  {
  	 steeringEngine_Analyze();
  }
  receive_count=0; 
  USART_ITConfig(USART1, USART_IT_RXNE,  ENABLE);//打开串口接收中断
}
