// Muestra la imagen mario en la pantalla inferior
#include <nds.h>
#include "testImage.h"
#include "testImage2.h"
#include "amongus.h"
#include "berlin.h"
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

	VRAM_C_CR    = VRAM_ENABLE | VRAM_C_LCD;
	dmaCopy(amongusBitmap, VRAM_B,amongusBitmapLen);
	VRAM_D_CR    = VRAM_ENABLE | VRAM_D_LCD;
	dmaCopy(berlinBitmap, VRAM_D, berlinBitmapLen);

	REG_DISPCNT  = MODE_FB0;
	while (1)
	{
		RunTimer();
		consoleClear();
		scanKeys();
		int held=keysHeld();

		if (GetSeconds() % 4 == 0)
		{
			REG_DISPCNT  = MODE_FB0;
		}
		if (GetSeconds() % 4 == 1)
		{
			REG_DISPCNT  = MODE_FB1;
		}
		if (GetSeconds() % 4 == 2)
		{
			REG_DISPCNT  = MODE_FB2;
		}
		if (GetSeconds() % 4 == 3)
		{
			REG_DISPCNT  = MODE_FB3;
		}
		swiWaitForVBlank();
	}
	return 0;
}