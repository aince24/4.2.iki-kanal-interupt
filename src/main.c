
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef LED;
EXTI_InitTypeDef Ext_i;
NVIC_InitTypeDef Nvic;

void config(){

	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE);//led
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);//buton

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE); //interupt

    //led
    LED.GPIO_Mode=GPIO_Mode_OUT;
    LED.GPIO_OType= GPIO_OType_PP;
    LED.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15|GPIO_Pin_0|GPIO_Pin_1 ;
    LED.GPIO_PuPd=GPIO_PuPd_NOPULL ;
    LED.GPIO_Speed=0x03;

   GPIO_Init(GPIOD, &LED);

   //buton1
     LED.GPIO_Mode=GPIO_Mode_IN;
     LED.GPIO_OType= GPIO_OType_PP;
     LED.GPIO_Pin=GPIO_Pin_1;//PA1
     LED.GPIO_PuPd=GPIO_PuPd_DOWN ;
     LED.GPIO_Speed=0x03;

    GPIO_Init(GPIOA, &LED);


    //buton2
      LED.GPIO_Mode=GPIO_Mode_IN;
      LED.GPIO_OType= GPIO_OType_PP;
      LED.GPIO_Pin=GPIO_Pin_2;//PA2
      LED.GPIO_PuPd=GPIO_PuPd_DOWN ;
      LED.GPIO_Speed=0x03;

     GPIO_Init(GPIOA, &LED);

    //interupt yapacaðýmýz portu ve pinini tanýmladýk
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);

    //buton1
    Ext_i.EXTI_Line=EXTI_Line1;
    Ext_i.EXTI_LineCmd=ENABLE;
    Ext_i.EXTI_Mode=EXTI_Mode_Interrupt;
    Ext_i.EXTI_Trigger= EXTI_Trigger_Rising;

    EXTI_Init(&Ext_i);

    //buton2
    Ext_i.EXTI_Line=EXTI_Line2;
    Ext_i.EXTI_LineCmd=ENABLE;
    Ext_i.EXTI_Mode=EXTI_Mode_Interrupt;
    Ext_i.EXTI_Trigger= EXTI_Trigger_Rising;

    EXTI_Init(&Ext_i);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    //buton1 öncelikli
    Nvic.NVIC_IRQChannel=EXTI1_IRQn;
    Nvic.NVIC_IRQChannelCmd=ENABLE;
    Nvic.NVIC_IRQChannelPreemptionPriority=0;
    Nvic.NVIC_IRQChannelSubPriority=0;

    NVIC_Init(&Nvic);

    //buton2
    Nvic.NVIC_IRQChannel=EXTI2_IRQn;
    Nvic.NVIC_IRQChannelCmd=ENABLE;
    Nvic.NVIC_IRQChannelPreemptionPriority=1;
    Nvic.NVIC_IRQChannelSubPriority=0;

    NVIC_Init(&Nvic);
}

void delay(uint32_t time){
	while(time--){}
}
//buton1 bayrak fonksiyonu
void ExtI1_IRQHandler(void){

int i=0;
	if (EXTI_GetITStatus(EXTI_Line1) != RESET ){


	for(i=0;i<6;i++){
		GPIO_ToggleBits(GPIOD,GPIO_Pin_1);
	 delay(168000000);
	 }

		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}


//buton2 bayrak fonksiyonu
void ExtI2_IRQHandler(void){
int i=0;
	if (EXTI_GetITStatus(EXTI_Line2) != RESET ){

     for(i=0;i<6;i++){
    	 GPIO_ToggleBits(GPIOD,GPIO_Pin_2);
		delay(168000000);
     }
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}

int main(void)
{
 config();

 GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

  while (1)
  {
	  GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
  }
}


void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
