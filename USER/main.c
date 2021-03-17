#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
 
extern u8   TIM2CH3_CAPTURE_STA;	//输入捕获状态		    				
extern u16	TIM2CH3_CAPTURE_VAL;	//输入捕获值

int main(void)
{		
  u32 temp=0; 
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200

  TIM2_Cap_Init(0XFFFF,72-1);	//以1Mhz的频率计数 
    while(1)
	{
 		delay_ms(10);   
        if(TIM2CH3_CAPTURE_STA&0X80)		//成功捕获到了一次上升沿
		{
      temp=TIM2CH3_CAPTURE_STA&0X3F;
			temp*=65536;		//溢出时间总和
			temp+=TIM2CH3_CAPTURE_VAL;		//得到总的高电平时间
      printf("\n\n*%d*\n\n",temp); 
			delay_ms(10);
      TIM2CH3_CAPTURE_STA = 0;        
        }
	}	    
 }

