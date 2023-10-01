// Muestra la imagen mario en la pantalla inferior
#include <nds.h>
#include "testImage.h"
#include "testImage2.h"
# define TIMER_SPEED ( BUS_CLOCK /1024)
uint ticks = 0;
void RunTimer(){
	ticks += timerElapsed (0) ;
}
int GetSeconds(){
	return ticks/TIMER_SPEED;
}
int main (void)
{
	timerStart (0 , ClockDivider_1024 , 0 , NULL ) ; 
	REG_POWERCNT = POWER_LCD | POWER_2D_A;

	VRAM_A_CR    = VRAM_ENABLE | VRAM_A_LCD;
	dmaCopy(testImageBitmap, VRAM_A, testImageBitmapLen);

	VRAM_B_CR    = VRAM_ENABLE | VRAM_B_LCD;
	dmaCopy(testImage2Bitmap, VRAM_B, testImage2BitmapLen);

	REG_DISPCNT  = MODE_FB0;
	while (1)
	{
		RunTimer();
		consoleClear();
		int lin , col;
		unsigned short *fb = VRAM_A ;
		for (lin =0; lin <192; lin ++){
			for (col =0; col <256; col ++){
				fb[lin * 256 + col ] = RGB15 (0 , 0, col *32/256) ;
			}
		}

		swiWaitForVBlank();
	}
	return 0;
}