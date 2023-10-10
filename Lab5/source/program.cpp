// Muestra la imagen mario en la pantalla inferior
#include <nds.h>
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
	for(int i = coords[1]; i < coords[1]+size; i++){
		for(int j = coords[0]; j < coords[0]+size; j++){
			fbA[i*256 + j] = RGB15(31,31,31);
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
int Clamp(int val, int min, int max){
	if(val < min){
		val = min;
	}
	else if (val > max){
		val = max;
	}
	return val;
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
		coords[0] = Clamp(coords[0],0,256-size);
		coords[1] = Clamp(coords[1],0,192-size);
		swiWaitForVBlank();
	}
	return 0;
}