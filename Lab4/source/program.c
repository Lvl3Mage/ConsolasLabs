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

void DrawSquare(int coords[], int size){
	unsigned short *fbA = VRAM_A;
	for(int i = coords[0]; i < coords[0]+size; i++){
		for(int j = coords[1]; j < coords[1]+size; j++){
			fbA[j*256 + i] = RGB15(31,31,31);
		}
	}
}
void ClearDisplay(){
	unsigned short *fbA = VRAM_A;
	for(int i = 0; i < 192; i++){
		for(int j = 0; j < 256; j++){
			fbA[i*256 + j] = RGB15(0,0,0);
		}
	}
}
int main (void)
{
	timerStart (0 , ClockDivider_1024 , 0 , NULL ) ; 
	REG_POWERCNT = POWER_LCD | POWER_2D_A;


	VRAM_A_CR    = VRAM_ENABLE | VRAM_A_LCD;


	REG_DISPCNT  = MODE_FB0;

	int coords[2] = {32,32};
	int size = 50;
	while (1)
	{
		RunTimer();
		consoleClear();
		scanKeys();
		int held=keysHeld();
		ClearDisplay();
		DrawSquare(coords, size);
		if (held & KEY_UP){
			coords[1] -= 1;
		}
		if (held & KEY_RIGHT){
			coords[0] += 1;

		}
		if (held & KEY_DOWN){
			coords[1] += 1;

		}
		if (held & KEY_LEFT){
			coords[0] -= 1;

		}
		
		swiWaitForVBlank();
	}
	return 0;
}