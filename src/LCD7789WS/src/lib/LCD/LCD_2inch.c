/*****************************************************************************
* | File      	:	LCD_Driver.c
* | Author      :   Waveshare team
* | Function    :   LCD driver
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2018-12-18
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "LCD_2inch.h"
#include <string.h>
#include "GUI_Paint.h"
/*******************************************************************************
function:
	Hardware reset
*******************************************************************************/
static void LCD_Reset(void)
{
	DEV_Digital_Write(DEV_CS_PIN, 1);
	DEV_Delay_ms(200);
	DEV_Digital_Write(DEV_RST_PIN, 0);
	DEV_Delay_ms(200);
	DEV_Digital_Write(DEV_RST_PIN, 1);
	DEV_Delay_ms(200);
	//DEV_Digital_Write(DEV_CS_PIN, 0);
	//DEV_Delay_ms(1000);
}

/*******************************************************************************
function:
		Write data and commands
*******************************************************************************/
static void LCD_Write_Command(UBYTE data)	 
{	
	DEV_Digital_Write(DEV_CS_PIN, 0);
	DEV_Digital_Write(DEV_DC_PIN, 0);
	DEV_SPI_WriteByte(data);
}

static void LCD_WriteData_Byte(UBYTE data) 
{	
	DEV_Digital_Write(DEV_CS_PIN, 0);
	DEV_Digital_Write(DEV_DC_PIN, 1);
	DEV_SPI_WriteByte(data);  
	DEV_Digital_Write(DEV_CS_PIN,1);
}  

void LCD_WriteData_Word(UWORD data)
{
	DEV_Digital_Write(DEV_CS_PIN, 0);
	DEV_Digital_Write(DEV_DC_PIN, 1);
	DEV_SPI_WriteByte((data>>8) & 0xff);
	DEV_SPI_WriteByte(data);
	DEV_Digital_Write(DEV_CS_PIN, 1);
}	  


/******************************************************************************
function:	
		Common register initialization
******************************************************************************/
/*
void LCD_Init(void)
{
	LCD_Reset();

	LCD_Write_Command(0x36);
	LCD_WriteData_Byte(0x00); 

	LCD_Write_Command(0x3A); 
	LCD_WriteData_Byte(0x05);

	LCD_Write_Command(0x21); 

	LCD_Write_Command(0x2A);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x01);
	LCD_WriteData_Byte(0x3F);

	LCD_Write_Command(0x2B);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0xEF);

	LCD_Write_Command(0xB2);
	LCD_WriteData_Byte(0x0C);
	LCD_WriteData_Byte(0x0C);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x33);
	LCD_WriteData_Byte(0x33);

	LCD_Write_Command(0xB7);
	LCD_WriteData_Byte(0x35); 

	LCD_Write_Command(0xBB);
	LCD_WriteData_Byte(0x1F);

	LCD_Write_Command(0xC0);
	LCD_WriteData_Byte(0x2C);

	LCD_Write_Command(0xC2);
	LCD_WriteData_Byte(0x01);

	LCD_Write_Command(0xC3);
	LCD_WriteData_Byte(0x12);   

	LCD_Write_Command(0xC4);
	LCD_WriteData_Byte(0x20);

	LCD_Write_Command(0xC6);
	LCD_WriteData_Byte(0x0F); 

	LCD_Write_Command(0xD0);
	LCD_WriteData_Byte(0xA4);
	LCD_WriteData_Byte(0xA1);

	LCD_Write_Command(0xE0);
	LCD_WriteData_Byte(0xD0);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x11);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x0C);
	LCD_WriteData_Byte(0x15);
	LCD_WriteData_Byte(0x39);
	LCD_WriteData_Byte(0x33);
	LCD_WriteData_Byte(0x50);
	LCD_WriteData_Byte(0x36);
	LCD_WriteData_Byte(0x13);
	LCD_WriteData_Byte(0x14);
	LCD_WriteData_Byte(0x29);
	LCD_WriteData_Byte(0x2D);

	LCD_Write_Command(0xE1);
	LCD_WriteData_Byte(0xD0);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x10);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x06);
	LCD_WriteData_Byte(0x06);
	LCD_WriteData_Byte(0x39);
	LCD_WriteData_Byte(0x44);
	LCD_WriteData_Byte(0x51);
	LCD_WriteData_Byte(0x0B);
	LCD_WriteData_Byte(0x16);
	LCD_WriteData_Byte(0x14);
	LCD_WriteData_Byte(0x2F);
	LCD_WriteData_Byte(0x31);
	LCD_Write_Command(0x21);

	LCD_Write_Command(0x11);

	LCD_Write_Command(0x29);
}

*/

// below is copied from orient display data sheet


void LCD_Init(void)
{
	LCD_Reset();
	LCD_Write_Command(0x01); // software reset
	DEV_Delay_ms(150);
	//LCD_Write_Command(0x11); // sleep out
	DEV_Delay_ms(220);

	LCD_Write_Command(0x36); // memory data access control AF has 08 for BGR
	LCD_WriteData_Byte(0x80); 

	LCD_Write_Command(0x3A);  // interface pixel format  (color mode AF)
	LCD_WriteData_Byte(0x55); // 16bit/pixel AF has 0x55 (rich was x05) high bits set RGB interface mode

	LCD_Write_Command(0x21); // Display inversion on
	LCD_Write_Command(0x2A); // Column address set
	LCD_WriteData_Byte(0x00); // 
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0xEF);

	LCD_Write_Command(0x2B);  // Row address set
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0xEF);

	LCD_Write_Command(0xB2);  // porch control
	LCD_WriteData_Byte(0x0C);
	LCD_WriteData_Byte(0x0C);
	LCD_WriteData_Byte(0x00);
	LCD_WriteData_Byte(0x33);
	LCD_WriteData_Byte(0x33);

	LCD_Write_Command(0xB7); // gate control
	LCD_WriteData_Byte(0x35); 

	LCD_Write_Command(0xBB);  // vcoms setting
	LCD_WriteData_Byte(0x18);

	LCD_Write_Command(0xC0); // lcm control
	LCD_WriteData_Byte(0x2C);

	LCD_Write_Command(0xC2); //VDV andVRHCommandEnable
	LCD_WriteData_Byte(0x01);

	LCD_Write_Command(0xC3); //VRH set
	LCD_WriteData_Byte(0x20);   

	LCD_Write_Command(0xC4); //VDV setting
	LCD_WriteData_Byte(0x20);

	LCD_Write_Command(0xC6);// FR control 2
	LCD_WriteData_Byte(0x0F); 

	LCD_Write_Command(0xD0); //Power control 1
	LCD_WriteData_Byte(0xA4);
	LCD_WriteData_Byte(0xA1);

	LCD_Write_Command(0xE0);  // positive voltga egamma conterol
	LCD_WriteData_Byte(0xD0);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x11);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x0C);
	LCD_WriteData_Byte(0x15);
	LCD_WriteData_Byte(0x39);
	LCD_WriteData_Byte(0x33);
	LCD_WriteData_Byte(0x50);
	LCD_WriteData_Byte(0x36);
	LCD_WriteData_Byte(0x13);
	LCD_WriteData_Byte(0x14);
	LCD_WriteData_Byte(0x29);
	LCD_WriteData_Byte(0x2D);

	LCD_Write_Command(0xE1);  // negative voltage gamma control
	LCD_WriteData_Byte(0xD0);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x10);
	LCD_WriteData_Byte(0x08);
	LCD_WriteData_Byte(0x06);
	LCD_WriteData_Byte(0x06);
	LCD_WriteData_Byte(0x39);
	LCD_WriteData_Byte(0x44);
	LCD_WriteData_Byte(0x51);
	LCD_WriteData_Byte(0x0B);
	LCD_WriteData_Byte(0x16);
	LCD_WriteData_Byte(0x14);
	LCD_WriteData_Byte(0x2F);
	LCD_WriteData_Byte(0x31);
	//LCD_Write_Command(0x29); // edit out Rich

	LCD_Write_Command(0x11); // sleep out  -- again??

	//LCD_Write_Command(0x13); // normal display on (added Rich)
	DEV_Delay_ms(200);
	LCD_Write_Command(0x29); // display on!
	DEV_Delay_ms(200);
}

/******************************************************************************
function:	Set the cursor position
parameter	:
	  Xstart: 	Start UWORD x coordinate
	  Ystart:	Start UWORD y coordinate
	  Xend  :	End UWORD coordinates
	  Yend  :	End UWORD coordinatesen
******************************************************************************/
void LCD_SetWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD  Yend)
{ 
	LCD_Write_Command(0x2a);
	LCD_WriteData_Byte(Xstart >>8);
	LCD_WriteData_Byte(Xstart & 0xff);
	LCD_WriteData_Byte((Xend - 1) >> 8);
	LCD_WriteData_Byte((Xend - 1) & 0xff);

	LCD_Write_Command(0x2b);
	LCD_WriteData_Byte(Ystart >>8);
	LCD_WriteData_Byte(Ystart & 0xff);
	LCD_WriteData_Byte((Yend - 1) >> 8);
	LCD_WriteData_Byte((Yend - 1) & 0xff);

	LCD_Write_Command(0x2C);
}

/******************************************************************************
function:	Settings window
parameter	:
	  Xstart: 	Start UWORD x coordinate
	  Ystart:	Start UWORD y coordinate

******************************************************************************/
void LCD_SetCursor(UWORD X, UWORD Y)
{ 
	LCD_Write_Command(0x2a);
	LCD_WriteData_Byte(X >> 8);
	LCD_WriteData_Byte(X);
	LCD_WriteData_Byte(X >> 8);
	LCD_WriteData_Byte(X);

	LCD_Write_Command(0x2b);
	LCD_WriteData_Byte(Y >> 8);
	LCD_WriteData_Byte(Y);
	LCD_WriteData_Byte(Y >> 8);
	LCD_WriteData_Byte(Y);

	LCD_Write_Command(0x2C);
}

/******************************************************************************
function:	Clear screen function, refresh the screen to a certain color
parameter	:
	  Color :		The color you want to clear all the screen
******************************************************************************/
void LCD_Clear(UWORD Color)
{
	UWORD i,j;
	UWORD image[LCD_WIDTH];
	for(i=0;i<LCD_WIDTH;i++){
		image[i] = Color>>8 | (Color&0xff)<<8;
	}
	UBYTE *p = (UBYTE *)(image);
	LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
	DEV_Digital_Write(DEV_DC_PIN, 1);
	for(i = 0; i < LCD_HEIGHT; i++){
		DEV_SPI_Write_nByte(p,LCD_WIDTH*2);
	}
}

/******************************************************************************
function:	Refresh a certain area to the same color
parameter	:
	  Xstart: Start UWORD x coordinate
	  Ystart:	Start UWORD y coordinate
	  Xend  :	End UWORD coordinates
	  Yend  :	End UWORD coordinates
	  color :	Set the color
******************************************************************************/
void LCD_ClearWindow(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend,UWORD color)
{          
	UWORD i,j; 
	LCD_SetWindow(Xstart, Ystart, Xend-1,Yend-1);
	for(i = Ystart; i <= Yend-1; i++){
		for(j = Xstart; j <= Xend-1; j++){
			LCD_WriteData_Word(color);
		}
	}
}

/******************************************************************************
function: Show a picture
parameter	:
		image: Picture buffer
******************************************************************************/
void LCD_Display(UBYTE *image)
{
	UWORD i,j;
	LCD_SetWindow(0, 0, LCD_WIDTH, LCD_HEIGHT);
	DEV_Digital_Write(DEV_DC_PIN, 1);
	for(i = 0; i < LCD_HEIGHT; i++){
		DEV_SPI_Write_nByte((UBYTE *)image+LCD_WIDTH*2*i,LCD_WIDTH*2);
	}
}

/******************************************************************************
function: Draw a point
parameter	:
	    X	: 	Set the X coordinate
	    Y	:	Set the Y coordinate
	  Color :	Set the color
******************************************************************************/
void LCD_DrawPaint(UWORD x, UWORD y, UWORD Color)
{
	LCD_SetCursor(x, y);
	LCD_WriteData_Word(Color); 	    
}

void LCD_DisplayOff(void)
{
	LCD_Write_Command(0x28); 	    
}

//void LCD_DisplayWindow(UBYTE *image,UWORD XXstart, UWORD YYstart, UWORD XXend, UWORD YYend,int rotate,MIRROR_IMAGE mirror)
void LCD_DisplayWindow(UBYTE *image,UWORD XXstart, UWORD YYstart, UWORD XXend, UWORD YYend)
{
	UWORD i,j,Xstart,Ystart,Xend,Yend;
	switch(Paint.Rotate) {
    //switch(0) {
	case 0:
        Xstart = XXstart;
		Xend = XXend;
		Ystart = YYstart;
		Yend = YYend;
        
        break;
    case 90:
        Xstart = Paint.WidthMemory - YYstart - 1;
        Ystart = XXstart;
		Xend = Paint.WidthMemory - YYend - 1;
        Yend = XXend;
        break;
    case 180:
        Xstart = Paint.WidthMemory - XXstart - 1;
        Ystart = Paint.HeightMemory - YYstart - 1;
		Xend = Paint.WidthMemory - XXend - 1;
        Yend = Paint.HeightMemory - YYend - 1;
        break;
    case 270:
        Xstart = YYstart;
        Ystart = Paint.HeightMemory - XXstart - 1;
		Xend = YYend;
        Yend = Paint.HeightMemory - XXend - 1;
        break;

    default:
		Xstart = XXstart;
		Xend = XXend;
		Ystart = YYstart;
		Yend = YYend;
        return;
    }
    
    switch(Paint.Mirror) {
	//switch(MIRROR_NONE) {
    case MIRROR_NONE:
        break;
    case MIRROR_HORIZONTAL:
        Xstart = Paint.WidthMemory - Xstart - 1;
		Xend = Paint.WidthMemory - Xend - 1;
        break;
    case MIRROR_VERTICAL:
        Ystart = Paint.HeightMemory - Ystart - 1;
		Yend = Paint.HeightMemory - Yend - 1;
        break;
    case MIRROR_ORIGIN:
        Xstart = Paint.WidthMemory - Xstart - 1;
		Xend = Paint.WidthMemory - Xend - 1;
        Ystart = Paint.WidthMemory - Ystart - 1;
		Yend = Paint.WidthMemory - Yend - 1;
        break;
    default:
        return;
    }
	if (Xend<Xstart)
	{
		UWORD tmp = Xend;
		Xend=Xstart;
		Xstart=tmp;
	}
	if (Yend<Ystart)
	{
		UWORD tmp = Yend;
		Yend=Ystart;
		Ystart=tmp;
	}

	LCD_SetWindow(Xstart,Ystart,Xend,Yend);
	DEV_Digital_Write(DEV_DC_PIN, 1);
	for(i = Ystart; i < Yend; i++){
		DEV_SPI_Write_nByte((UBYTE *)image+(LCD_WIDTH*2*i)+(Xstart*2),((Xend-Xstart)*2));
	}
}

