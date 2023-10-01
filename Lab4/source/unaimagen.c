// Muestra la imagen mario en la pantalla inferior
#include <nds.h>
#include "testImage.h"

int main (void)
{
	REG_POWERCNT = POWER_LCD | POWER_2D_A;
	REG_DISPCNT  = MODE_FB0;
	VRAM_A_CR    = VRAM_ENABLE | VRAM_A_LCD;
	dmaCopy(testImageBitmap, VRAM_A, testImageBitmapLen);
	while (1)
	{
		swiWaitForVBlank();
	}
	return 0;
}