#include "OLED_drive.h"
#include "i2c.h"
#include "word_stock.h"

/*OLED初始化数据*/
uint8_t OLED_Init_Data[]={
0xAE, 0x00, 0x10, 0x40, 0xB0, 0x81, 0xFF, 0xA1, 0xA6, 0xA8, 0x3F,
					
0xC8, 0xD3, 0x00, 0xD5, 0x80, 0xD8, 0x05, 0xD9, 0xF1, 0xDA, 0x12,
					
0xD8, 0x30, 0x8D, 0x14, 0xAF};


/*初始化oled屏幕*/
void OLED_Init(void)
{
	HAL_Delay(200);
	
	for(uint8_t i=0; i<27; i++)
	{
		HAL_I2C_Mem_Write(&hi2c1 ,0x78, 0x00, I2C_MEMADD_SIZE_8BIT, OLED_Init_Data+i, 1, 0x100);
	}
}


/*向OLED写控制命令*/
void OLED_WR_CMD(uint8_t cmd)
{
	HAL_I2C_Mem_Write(&hi2c1 ,0x78, 0x00, I2C_MEMADD_SIZE_8BIT, &cmd, 1, 0x100);
}


/*向设备写数据*/
void OLED_WR_DATA(uint8_t data)
{
	HAL_I2C_Mem_Write(&hi2c1 ,0x78, 0x40, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x100);
}


/*清屏*/
void OLED_Clear(void)
{
	uint8_t i, n;   
	for(i=0;i<8;i++)  
	{  
		OLED_WR_CMD(0xb0+i);
		OLED_WR_CMD (0x00); 
		OLED_WR_CMD (0x10); 
		for(n=0;n<128;n++)
			OLED_WR_DATA(0);
	} 
}


/*开启OLED显示*/    
void OLED_Display_On(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X14);  //DCDC ON
	OLED_WR_CMD(0XAF);  //DISPLAY ON
}


/*关闭OLED显示*/  
void OLED_Display_Off(void)
{
	OLED_WR_CMD(0X8D);  //SET DCDC命令
	OLED_WR_CMD(0X10);  //DCDC OFF
	OLED_WR_CMD(0XAE);  //DISPLAY OFF
}


void OLED_On(void)  
{  
	uint8_t i, n;
	for(i=0; i<8; i++)  
	{  
		OLED_WR_CMD(0xb0+i);    //设置页地址（0~7）
		OLED_WR_CMD(0x00);      //设置显示位置—列低地址
		OLED_WR_CMD(0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			OLED_WR_DATA(1); 
	} //更新显示
}


void OLED_Set_Pos(uint8_t x, uint8_t y) 
{ 	
	OLED_WR_CMD(0xb0+y);
	OLED_WR_CMD(((x&0xf0)>>4)|0x10);
	OLED_WR_CMD(x&0x0f);
} 


/**
  * @brief  在指定位置显示一个字符,包括部分符号
  * @param  x    0~127
  * @param  y    0~63
  * @param  chr  字符
  * @param  size 选择字体 16/12 
  * @retval None
  */
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr, uint8_t Char_Size)
{      	
	unsigned char c=0,i=0;
	
	c=chr-' ';  //得到偏移后的值			
	
	if(x>128-1)
	{
		x=0;
		y=y+2;
	}
	
	if(Char_Size == 16)
	{
		OLED_Set_Pos(x,y);
		
		for(i=0; i<8; i++)
			OLED_WR_DATA(F8X16[c*16+i]);
		
		OLED_Set_Pos(x,y+1);
		
		for(i=0; i<8; i++)
			OLED_WR_DATA(F8X16[c*16+i+8]);
	}
//	else 
//	{	
//		OLED_Set_Pos(x,y);
//		
//		for(i=0;i<6;i++)
//			OLED_WR_DATA(F6x8[c][i]);
//	}
}


/**
  * @brief  在指定位置显示一个字符串
  * @param  x    0~127
  * @param  y    0~63
  * @param  chr  字符串
  * @param  size 字体大小 16
  * @retval None
  */
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *chr, uint8_t Char_Size)
{
	unsigned char j = 0;
	
	while (chr[j] != '\0')
	{
		OLED_ShowChar(x, y, chr[j], Char_Size);
		x += 8;
		
		if(x > 120)
		{
			x = 0;
			y += 2;
		}
		
		j++;
	}
}


//显示汉字
//hzk 用取模软件得出的数组
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no)
{      			    
	uint8_t t, adder = 0;
	
	OLED_Set_Pos(x, y);
	
	for(t=0; t<16; t++)
	{
		OLED_WR_DATA(simplified_Chinese[2*no][t]);
		adder += 1;
	}	
	
	OLED_Set_Pos(x, y+1);
	
	for(t=0; t<16; t++)
	{	
		OLED_WR_DATA(simplified_Chinese[2*no+1][t]);
		adder += 1;
	}					
}

