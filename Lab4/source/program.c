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

	u16 color_red = RGB15 (31 ,0 ,0) ;
	u16 color_yellow = RGB15 (31 ,31 ,0) ;
	u16 color_blue = RGB15 (0 ,0 ,31) ;
	u16 color_green = RGB15 (0 ,31 ,0) ;
	u16 color_white = RGB15 (31 ,31 ,31) ;


	VRAM_A_CR    = VRAM_ENABLE | VRAM_A_LCD;

	VRAM_B_CR    = VRAM_ENABLE | VRAM_B_LCD;

	VRAM_C_CR    = VRAM_ENABLE | VRAM_C_LCD;

	unsigned short *fbA = VRAM_A;
	for(int i = 0; i < 192; i++){
		for(int j = 0; j < 256; j++){
			int y = (i - 96);
			int x = (j - 128);

			if(sqrt(y*y+x*x) < 40){
				if(abs((x+32)*(x+32)/96 - 2*y - 32 ) < 10){
					fbA[i*256 + j] = color_white;
				}
				else{
					fbA[i*256 + j] = color_blue;
				}
			}
			else if((abs(y*2) + abs(x)) < 120){
				fbA[i*256 + j] = color_yellow;
			}
			else{
				fbA[i*256 + j] = color_green;

			}
		}
	}
	unsigned short *fbB = VRAM_B;
	for(int i = 0; i < 192; i++){
		for(int j = 0; j < 256; j++){
			int y = (i - 96);
			int x = (j - 128);
			if(x < -16 && y < -8){
				if((i % 8) - 4 < 0 && (j % 8) - 4 < 0){
					fbB[i*256 + j] = color_white;
				}
				else{
					fbB[i*256 + j] = color_blue;

				}

			}
			else{
				if((i % 16) - 8 < 0){
					fbB[i*256 + j] = color_red;
				}
				else{
					fbB[i*256 + j] = color_white;
				}
			}
		}
	}
	unsigned short *fbC = VRAM_C;
	for(int i = 0; i < 192; i++){
		for(int j = 0; j < 256; j++){
			int y = (i - 96);
			int x = (j - 128);
			if(abs(x) < 16 || abs(y) < 16){
				fbC[i*256 + j] = color_red;

			}
			else if(abs(x) < 28 || abs(y) < 28){
				fbC[i*256 + j] = color_white;

			}
			else if(abs((float)i-(float)j*(96.0/128.0)) < 8){
				fbC[i*256 + j] = color_red;

			}
			else if(abs((float)i -(float)(256-j)*(96.0/128.0)) < 8){
				fbC[i*256 + j] = color_red;

			}
			else if(abs((float)i-(float)j*(96.0/128.0)) < 20){
				fbC[i*256 + j] = color_white;

			}
			else if(abs((float)i -(float)(256-j)*(96.0/128.0)) < 20){
				fbC[i*256 + j] = color_white;

			}
			else{
				fbC[i*256 + j] = color_blue;

			}
		}
	}

	REG_DISPCNT  = MODE_FB2;
	while (1)
	{
		RunTimer();
		consoleClear();
		scanKeys();
		int held=keysHeld();

		if (held & KEY_A)
		{
			REG_DISPCNT  = MODE_FB0;
		}
		if (held & KEY_X)
		{
			REG_DISPCNT  = MODE_FB1;
		}
		if (held & KEY_B)
		{
			REG_DISPCNT  = MODE_FB2;
		}
		
		swiWaitForVBlank();
	}
	return 0;
}