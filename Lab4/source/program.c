// Muestra la imagen mario en la pantalla inferior
#include <nds.h>
#include "testImage.h"
#include "testImage2.h"

int main (void)
{
	REG_POWERCNT = POWER_LCD | POWER_2D_A;

	VRAM_A_CR    = VRAM_ENABLE | VRAM_A_LCD;
	dmaCopy(testImageBitmap, VRAM_A, testImageBitmapLen);

	VRAM_B_CR    = VRAM_ENABLE | VRAM_B_LCD;
	dmaCopy(testImage2Bitmap, VRAM_B, testImage2BitmapLen);

	REG_DISPCNT  = MODE_FB0;
	while (1)
	{
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
		swiWaitForVBlank();
	}
	return 0;
}