#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "image.h"
#include "GUI_BMPfile.h"

void  Handler(int signo)
{
    //System Exit
	printf("\r\nHandler:exit\r\n");
	DEV_ModuleExit();

    exit(0);
}

int main(void)
{
    // Exception handling:ctrl + c
    //signal(SIGINT, Handler);
    int looper =0;
	
	
		DEV_ModuleInit();
		//DEV_ModuleInit();
		//RED
	
		LCD_Init();
		LCD_Clear(WHITE);
		
	
		printf("Looper = %d\r\n",looper);
		DEV_Delay_ms(3000);	
		UBYTE *BlackImage;
		UDOUBLE Imagesize = LCD_WIDTH * LCD_HEIGHT *2;
		printf("Imagesize = %d\r\n",Imagesize);
		if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			exit(0);
		}
		
		Paint_NewImage(BlackImage,LCD_WIDTH,LCD_HEIGHT, 0, WHITE);
		Paint_Clear(GRAYBLUE);
		LCD_Display(BlackImage);
		Paint_SetRotate(90);
		//Paint_SetMirroring(MIRROR_VERTICAL);
		printf("About to draw string 123\r\n");
		char outstr[10];
		while (looper++<200)
		{
		
			Paint_Clear(GRAY);
			sprintf(outstr,"Loop %d",looper);
			Paint_DrawString_EN(30, 60, outstr, &Font24, YELLOW, RED);
			//LCD_Display(BlackImage);
			LCD_DisplayWindow(BlackImage, 30,60,180,90); // last two not used?
		}
		Paint_Clear(BLACK);
		Paint_DrawString_EN(20, 0, "Filename for first channel", &Font24, BLACK, WHITE);
		Paint_DrawString_EN(20, 26, "Filename for second channel", &Font24, BLACK, WHITE);
		Paint_DrawString_EN(20, 52, "Filename for third channel", &Font24, BLACK, WHITE);
		Paint_DrawString_EN(20, 78, "Filename for fourth channel", &Font24, BLACK, WHITE);
		Paint_DrawString_EN(20, 104, "Filename for fifth channel", &Font24, BLACK, WHITE);
		Paint_DrawString_EN(20, 130, "Filename for sixth channel", &Font24, BLACK, WHITE);
		Paint_DrawString_EN(20, 156, "Filename for seventh channel", &Font24, BLACK, WHITE);
		Paint_DrawString_EN(20, 182, "Filename for eighth channel", &Font24, BLACK, WHITE);
		//Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);
		//Paint_DrawString_CN(50,180, "΢ѩ����",  &Font24CN, WHITE, RED);
		//Paint_DrawRectangle(125, 10, 225, 58, RED,DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
		//printf("About to draw line 123\r\n");
		//Paint_DrawLine(125, 10, 225, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
		//Paint_DrawLine(225, 10, 125, 58, MAGENTA, LINE_STYLE_SOLID, DOT_PIXEL_2X2);
		
		Paint_DrawCircle(10,12, 4, BLUE,  DRAW_FILL_FULL, DOT_PIXEL_1X1);
		Paint_DrawCircle(10,38, 4, RED,  DRAW_FILL_FULL, DOT_PIXEL_1X1);
		Paint_DrawCircle(10,64, 4, YELLOW,  DRAW_FILL_FULL, DOT_PIXEL_1X1);
		//Paint_DrawCircle(180,100, 25, BLACK,    DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
		//Paint_DrawCircle(210,100, 25, RED, DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
		//Paint_DrawCircle(165,125, 25, YELLOW,   DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
		//Paint_DrawCircle(195,125, 25, GREEN,   DRAW_FILL_EMPTY, DOT_PIXEL_2X2);
		
		//Paint_DrawImage(gImage_100X100, 10, 75,100, 100); 

		
		LCD_Display(BlackImage);
		DEV_Delay_ms(2000);
	
	
		
		
		GUI_ReadBmp_RGB("/root/Beal/uploads/samplergui4.bmp",0,0);
		
		LCD_Display(BlackImage);
		//LCD_DisplayWindow(BlackImage, 00,00,319,239);
		DEV_Delay_ms(2000);

		//System Exit
		DEV_ModuleExit();

	
	return 0;
	
}

