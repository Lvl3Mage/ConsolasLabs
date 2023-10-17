#include <nds.h>
#include <stdio.h>

u8 green[64] =
{
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,
};

u8 red[64] =
{
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,2,2,
};
u8 blue[64] =
{
  3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,
  3,3,3,3,3,3,3,3,
};

u8 yellow[64] =
{
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
  4,4,4,4,4,4,4,4,
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
	REG_POWERCNT = POWER_ALL_2D;
	REG_DISPCNT  = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;
	REG_DISPCNT_SUB = MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE;
	VRAM_A_CR    	= VRAM_ENABLE | VRAM_A_MAIN_BG;
	VRAM_C_CR       = VRAM_ENABLE | VRAM_C_SUB_BG;
	BGCTRL[0]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY(3);  // Bottom
	BGCTRL[1]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(2) | BG_PRIORITY(2);  // Top
	BGCTRL[2]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(2) | BG_TILE_BASE(3) | BG_PRIORITY(1);  // Top
	BGCTRL[3]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(3) | BG_TILE_BASE(4) | BG_PRIORITY(0);  // Top

	BGCTRL_SUB[0]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY(3);  // Bottom
	BGCTRL_SUB[1]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(2) | BG_PRIORITY(2);  // Top
	BGCTRL_SUB[2]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(2) | BG_TILE_BASE(3) | BG_PRIORITY(1);  // Top
	BGCTRL_SUB[3]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(3) | BG_TILE_BASE(4) | BG_PRIORITY(0);  // Top

	static u8*  tileMemoryB0  = (u8*)  BG_TILE_RAM(1);
	static u16* mapMemoryB0   = (u16*) BG_MAP_RAM(0);

	static u8*  tileMemoryB1 = (u8*)  BG_TILE_RAM(2);
	static u16* mapMemoryB1  = (u16*) BG_MAP_RAM(1);

	static u8*  tileMemoryB2 = (u8*)  BG_TILE_RAM(3);
	static u16* mapMemoryB2  = (u16*) BG_MAP_RAM(2);

	static u8*  tileMemoryB3 = (u8*)  BG_TILE_RAM(4);
	static u16* mapMemoryB3  = (u16*) BG_MAP_RAM(3);

	static u8*  tileMemoryB0Sub  = (u8*)  BG_TILE_RAM_SUB(1);
	static u16* mapMemoryB0Sub   = (u16*) BG_MAP_RAM_SUB(0);

	static u8*  tileMemoryB1Sub = (u8*)  BG_TILE_RAM_SUB(2);
	static u16* mapMemoryB1Sub  = (u16*) BG_MAP_RAM_SUB(1);

	static u8*  tileMemoryB2Sub = (u8*)  BG_TILE_RAM_SUB(3);
	static u16* mapMemoryB2Sub  = (u16*) BG_MAP_RAM_SUB(2);

	static u8*  tileMemoryB3Sub = (u8*)  BG_TILE_RAM_SUB(4);
	static u16* mapMemoryB3Sub  = (u16*) BG_MAP_RAM_SUB(3);

	BG_PALETTE[1]     = RGB15(0,20,0);
	BG_PALETTE[2]     = RGB15(20,0,0);
	BG_PALETTE[3]     = RGB15(0,0,20);
	BG_PALETTE[4]     = RGB15(20,20,0);
	BG_PALETTE_SUB[1]     = RGB15(0,20,0);
	BG_PALETTE_SUB[2]     = RGB15(20,0,0);
	BG_PALETTE_SUB[3]     = RGB15(0,0,20);
	BG_PALETTE_SUB[4]     = RGB15(20,20,0);

	dmaCopy(green, tileMemoryB0 + 64,  sizeof(green));

	dmaCopy(red, tileMemoryB1 + 64,  sizeof(red));

	dmaCopy(blue, tileMemoryB2 + 64,  sizeof(blue));

	dmaCopy(yellow, tileMemoryB3 + 64,  sizeof(yellow));

	dmaCopy(green, tileMemoryB0Sub + 64,  sizeof(green));

	dmaCopy(red, tileMemoryB1Sub + 64,  sizeof(red));

	dmaCopy(blue, tileMemoryB2Sub + 64,  sizeof(blue));

	dmaCopy(yellow, tileMemoryB3Sub + 64,  sizeof(yellow));

	int fila, columna;

	for(fila=0;fila<24;fila++){
		for(columna=0;columna<32;columna++)
		{
			mapMemoryB0[fila*32+columna] = 1;       // Fondo 0, todo verde
			mapMemoryB0Sub[fila*32+columna] = 1;       // Fondo 0, todo verde
			if (columna>=16){
				mapMemoryB1[fila*32+columna] = 1;   // Fondo 1, mitad derecha rojo
				mapMemoryB1Sub[fila*32+columna] = 1;   // Fondo 1, mitad derecha rojo
			}
			if (columna<16 && fila >= 12){
				mapMemoryB2[fila*32+columna] = 1;   // Fondo 1, mitad derecha rojo
				mapMemoryB2Sub[fila*32+columna] = 1;   // Fondo 1, mitad derecha rojo
			}
			if (columna>=16 && fila < 12){
				mapMemoryB3[fila*32+columna] = 1;   // Fondo 1, mitad derecha rojo
				mapMemoryB3Sub[fila*32+columna] = 1;   // Fondo 1, mitad derecha rojo
			}

		}
	}

	while(1)
	{
		scanKeys();
		u32 keys = keysDown();
		if(keys & KEY_A){
			BGCTRL[0]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY(2);  // Bottom
			BGCTRL[1]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(2) | BG_PRIORITY(3);  // Top

		}
		if(keys & KEY_X){
			BGCTRL[0]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1) | BG_PRIORITY(3);  // Bottom
			BGCTRL[1]    = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(1) | BG_TILE_BASE(2) | BG_PRIORITY(2);  // Top
			
		}
		swiWaitForVBlank();
	}
}