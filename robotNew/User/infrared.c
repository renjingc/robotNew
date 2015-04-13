#include "infrared.h"
#include "buzzer.h"

int infraredNum=0;
void Infrared_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=INFRARED1|INFRARED2|INFRARED3|INFRARED4;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;							//上拉输入
	GPIO_Init(INFRARED_PORT,&GPIO_InitStructure);
}

void Read_Infrared()
{
	 if(GPIO_ReadInputDataBit(INFRARED_PORT,INFRARED1)==0)
	 {
		//GPIO_ResetBits(BUZZER__PORT, BUZZER);	
		infraredNum=1;
	 }
	 else if(GPIO_ReadInputDataBit(INFRARED_PORT,INFRARED2)==0)
	 {
		//GPIO_ResetBits(BUZZER__PORT, BUZZER);	
		infraredNum=2;
	 }
	 else if(GPIO_ReadInputDataBit(INFRARED_PORT,INFRARED3)==0)
	 {
		//GPIO_ResetBits(BUZZER__PORT, BUZZER);	
		infraredNum=3;
	 }
	 else if(GPIO_ReadInputDataBit(INFRARED_PORT,INFRARED4)==0)
	 {
		//GPIO_ResetBits(BUZZER__PORT, BUZZER);	
		infraredNum=4;
	 }
	 else
	 {
	 	infraredNum=0;
	 }
}
