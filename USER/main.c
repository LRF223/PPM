#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 
extern u8   TIM2CH3_CAPTURE_STA;	//���벶��״̬		    				
extern u16	TIM2CH3_CAPTURE_VAL;	//���벶��ֵ

int main(void)
{		
  u32 temp=0; 
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200

  TIM2_Cap_Init(0XFFFF,72-1);	//��1Mhz��Ƶ�ʼ��� 
    while(1)
	{
 		delay_ms(10);   
        if(TIM2CH3_CAPTURE_STA&0X80)		//�ɹ�������һ��������
		{
      temp=TIM2CH3_CAPTURE_STA&0X3F;
			temp*=65536;		//���ʱ���ܺ�
			temp+=TIM2CH3_CAPTURE_VAL;		//�õ��ܵĸߵ�ƽʱ��
      printf("\n\n*%d*\n\n",temp); 
			delay_ms(10);
      TIM2CH3_CAPTURE_STA = 0;        
        }
	}	    
 }

