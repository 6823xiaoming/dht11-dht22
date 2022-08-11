#include "dht.h"
#include "intrins.h"
/*
   DHT11/DHT22 通用驱动
   在头文件更改具体型号
   注意：在移植其他平台的话，要注意ms延时和us延时函数
   @小明
*/

void DHT11_delay_us(uchar n)
{
    uint i;
	 for(i=n-3;i>0;i--);
}

void DHT11_delay_ms(uint z)
{
	
   uint i,j;

   for(i=z;i>0;i--)
      for(j=950;j>0;j--);
}

void DHT11_start(void)
{

#if (MODE == DHT11)
   Data=0;
   DHT11_delay_ms(25);    
   Data=1;
   DHT11_delay_us(27);  //精确时间 30us
#elif (MODE == DHT22)
   Data=0;
   DHT11_delay_ms(5);    
   Data=1;
   DHT11_delay_us(27);  //精确时间 30us
#endif
	
}

//接收一个字节
uchar DHT11_rec_byte(void)     
{
	
   uchar i,dat=0;
	EA = 0;
  for(i=0;i<8;i++)  
   {          
      while(!Data);   
      DHT11_delay_us(28);     
      dat<<=1;           
      if(Data==1)    
         dat+=1;
      while(Data);  
    }  
   EA = 1;
    return dat;
}

//获取温湿度数据
void DHT11_receive(float* temp, float* humid)      
{
    uchar R_H,R_L,T_H,T_L,RH,RL,TH,TL,revise; 
    DHT11_start();
    if(Data==0)
    {
      while(Data==0);     
#if (MODE == DHT11)
      DHT11_delay_us(17);
		DHT11_delay_us(17);
#elif (MODE == DHT22)
		DHT11_delay_us(16);
		DHT11_delay_us(16);
		DHT11_delay_us(16);
		DHT11_delay_us(16);
#endif			
        R_H=DHT11_rec_byte();     
        R_L=DHT11_rec_byte();    
        T_H=DHT11_rec_byte();     
        T_L=DHT11_rec_byte();    
        revise=DHT11_rec_byte();  

        DHT11_delay_us(25);   
        if((R_H+R_L+T_H+T_L)==revise)       
        {
            RH=R_H;
            RL=R_L;
            TH=T_H;
            TL=T_L;
        } 
		
#if (MODE == DHT11)
		*humid = RH;
		*temp = TH;
#elif (MODE == DHT22)
		*temp = (T_H << 8 | T_L) / 10.0;
		*humid = (R_H << 8 | R_L) / 10.0;

		// *temp = (T_H *256 + T_L) / 10.0;
		// *humid = (R_H *256 + R_L) / 10.0;
      
		if(T_H & 0x80)
			*temp *= -1;
#endif	
    }
	
	Data = 1;
	

}