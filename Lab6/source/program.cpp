#include <nds.h>
#include <stdio.h>

u8 comecocos[64] =
{
    2,2,1,1,1,1,2,2,
    2,1,1,1,1,1,2,2,
    1,1,1,1,1,2,2,2,
    1,1,1,1,2,2,2,2,
    1,1,1,1,2,2,2,2,
    1,1,1,1,1,2,2,2,
    2,1,1,1,1,1,2,2,
    2,2,1,1,1,1,2,2,
};

u8 fondo[64] =
{
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2
};

u8 fantasma[64] =
{
	2,2,2,3,3,2,2,2,
	2,3,3,3,3,3,3,2,
	3,3,3,3,3,3,3,3,
	3,4,2,3,3,4,2,3,
	3,4,2,3,3,4,2,3,
	3,3,3,3,3,3,3,3,
	3,3,3,3,3,3,3,3,
	3,2,3,2,2,3,2,3
};

u16 mapData[768] =
{
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2
};
int Clamp(int val, int min, int max){
	if(val < min){
		val = min;
	}
	else if (val > max){
		val = max;
	}
	return val;
}
int main( void )
{
	int fila,columna,pos_mapMemory,pos_mapData;

	REG_POWERCNT    = POWER_ALL_2D;
	REG_DISPCNT     = MODE_0_2D | DISPLAY_BG0_ACTIVE;
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE;
	VRAM_A_CR       = VRAM_ENABLE | VRAM_A_MAIN_BG;
	VRAM_C_CR       = VRAM_ENABLE | VRAM_C_SUB_BG;
	BGCTRL[0]       = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
	BGCTRL_SUB[0]   = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);

	
	static u8*  tileMemory    = (u8*)  BG_TILE_RAM(1);
	static u16* mapMemory     = (u16*) BG_MAP_RAM(0);
	static u8*  tileMemorySub = (u8*)  BG_TILE_RAM_SUB(1);
	static u16* mapMemorySub  = (u16*) BG_MAP_RAM_SUB(0);

	BG_PALETTE[1]=RGB15(28,0,0);
	BG_PALETTE[2]=RGB15(0,20,0);
	BG_PALETTE_SUB[1] = RGB15(0,20,0);
	BG_PALETTE_SUB[2] = RGB15(20,0,0);

	dmaCopy(comecocos,tileMemory + 64,  sizeof(comecocos));
	dmaCopy(fondo,  tileMemory + 128, sizeof(fondo));
	dmaCopy(comecocos,tileMemorySub + 64,  sizeof(comecocos));
	dmaCopy(fondo,  tileMemorySub + 128, sizeof(fondo));
	// dmaCopy(fantasma,  tileMemory + 192, sizeof(fantasma));

	pos_mapData = 0;
	for(fila=0;fila<24;fila++){
		for(columna=0;columna<32;columna++)
		{
			pos_mapMemory            = fila*32+columna;
			mapMemory[pos_mapMemory] = mapData[pos_mapData];
			pos_mapData ++;
	    }
	}
	pos_mapData = 0;
	for(fila=0;fila<24;fila++){
		for(columna=0;columna<32;columna++)
		{
			pos_mapMemory            = fila*32+columna;
			mapMemorySub[pos_mapMemory] = mapData[pos_mapData];
			pos_mapData ++;
	    }
	}
	int posX = 0;
	int posY = 0;
	bool upperScreen = false;
	while(1)
	{
		scanKeys();
		u32 keys = keysDown();

		mapMemory[posY*32 + posX] = 2;
		mapMemorySub[posY*32 + posX] = 2;
		if(keys & KEY_DOWN){
			posY ++;
		}
		if(keys & KEY_UP){
			posY --;
		}
		if(keys & KEY_LEFT){
			posX --;
		}
		if(keys & KEY_RIGHT){
			posX ++;
		}
		if(keys & KEY_A){
			BG_PALETTE[1]=RGB15(10,0,0);
			BG_PALETTE[2]=RGB15(10,20,0);
			upperScreen = true;
		}
		if(keys & KEY_X){
			BG_PALETTE[1]=RGB15(28,0,0);
			BG_PALETTE[2]=RGB15(0,20,0);
			upperScreen = false;
		}
		posX = Clamp(posX, 0, 31);
		posY = Clamp(posY, 0, 23);
		if(upperScreen){
			mapMemorySub[posY*32 + posX] = 1;

		}
		else{
			mapMemory[posY*32 + posX] = 1;

		}

		swiWaitForVBlank();
	}
}