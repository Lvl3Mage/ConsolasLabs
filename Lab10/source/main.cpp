#include <nds.h>
#include <stdio.h>
#include <algorithm>
#include "tiles.h"
using namespace std;
static u8*  tileMemory;
static u16* mapMemory;

bool moveSmClouds = false;
bool moveLgClouds = false;
bool duckAnim = false;
bool lockAnim = false;
int screenWidthL = 64;
int screenWidthS = 32;
int startCol = 0;
void smCloudTimer()
{
	moveSmClouds = true;
	// seconds += 1;
}
void lgCloudTimer()
{
	moveLgClouds = true;
	// seconds += 1;
}
void duckAnimTimer()
{
	if(lockAnim){
		lockAnim = false;
		return;
	}
	duckAnim = !duckAnim;
	// seconds += 1;
}
int PosToIndex(int x, int y){
	return y*screenWidthL+x;
}
int PosToIndexSM(int x, int y){
	return y*screenWidthS+x;
}
void ConfigureTimers()
{
	irqEnable(IRQ_TIMER0);
	irqSet(IRQ_TIMER0, smCloudTimer);
	TIMER_DATA(0) = 32764;
	TIMER_CR (0) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ;


	irqEnable(IRQ_TIMER1);
	irqSet(IRQ_TIMER1, lgCloudTimer);
	TIMER_DATA(1) = 0;
	TIMER_CR (1) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ;

	irqEnable(IRQ_TIMER2);
	irqSet(IRQ_TIMER2, duckAnimTimer);
	TIMER_DATA(2) = 32764;
	TIMER_CR (2) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ;
}

void ConfigureScreen()
{
	consoleDemoInit();
	REG_POWERCNT = (vu16) POWER_ALL_2D;
	REG_DISPCNT  = MODE_0_2D | DISPLAY_BG0_ACTIVE ;
	VRAM_A_CR    = VRAM_ENABLE | VRAM_A_MAIN_BG ;
	BGCTRL [0]   = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
	tileMemory   = (u8*)  BG_TILE_RAM(1);
	mapMemory    = (u16*) BG_MAP_RAM(0);

	BG_PALETTE[0]=RGB15(0,31,31);//cyan
	BG_PALETTE[1]=RGB15(31,31,31);//white
	BG_PALETTE[2]=RGB15(12,6,0);//brown1
	BG_PALETTE[3]=RGB15(15,8,0);//brown2
	BG_PALETTE[4]=RGB15(6,24,6);//green
	BG_PALETTE[5]=RGB15(31,15,0);//orange
	BG_PALETTE[6]=RGB15(2,12,2);//dark green
	BG_PALETTE[7]=RGB15(25,25,25);//gray
	BG_PALETTE[8]=RGB15(0,0,0);//black
	BG_PALETTE[9]=RGB15(18,18,18);//dark gray

	dmaCopy(sky,         tileMemory       ,  sizeof(sky));
	dmaCopy(smCloudL,    tileMemory + 64*1,  sizeof(smCloudL));
	dmaCopy(smCloudR,    tileMemory + 64*2,  sizeof(smCloudR));
	dmaCopy(lgCloudTL,   tileMemory + 64*3,  sizeof(smCloudL));
	dmaCopy(lgCloudTR,   tileMemory + 64*4,  sizeof(smCloudR));
	dmaCopy(lgCloudBL,   tileMemory + 64*5,  sizeof(smCloudL));
	dmaCopy(lgCloudBR,   tileMemory + 64*6,  sizeof(smCloudR));
	dmaCopy(terrain,   tileMemory + 64*7,  sizeof(terrain));
	dmaCopy(grass,   tileMemory + 64*8,  sizeof(grass));

	dmaCopy(chrt1,   tileMemory + 64*9,  sizeof(chrt1));
	dmaCopy(chrt2,   tileMemory + 64*10,  sizeof(chrt2));
	dmaCopy(chrt3,   tileMemory + 64*11,  sizeof(chrt3));
	dmaCopy(chrt4,   tileMemory + 64*12,  sizeof(chrt4));

	dmaCopy(chrt1_inv,   tileMemory + 64*13,  sizeof(chrt1_inv));
	dmaCopy(chrt2_inv,   tileMemory + 64*14,  sizeof(chrt2_inv));
	dmaCopy(chrt3_inv,   tileMemory + 64*15,  sizeof(chrt3_inv));
	dmaCopy(chrt4_inv,   tileMemory + 64*16,  sizeof(chrt4_inv));


	dmaCopy(chrt1_anim,   tileMemory + 64*17,  sizeof(chrt1_anim));
	dmaCopy(chrt2_anim,   tileMemory + 64*18,  sizeof(chrt2_anim));
	dmaCopy(chrt3_anim,   tileMemory + 64*19,  sizeof(chrt3_anim));
	dmaCopy(chrt4_anim,   tileMemory + 64*20,  sizeof(chrt4_anim));

	dmaCopy(chrt1_anim_inv,   tileMemory + 64*21,  sizeof(chrt1_anim_inv));
	dmaCopy(chrt2_anim_inv,   tileMemory + 64*22,  sizeof(chrt2_anim_inv));
	dmaCopy(chrt3_anim_inv,   tileMemory + 64*23,  sizeof(chrt3_anim_inv));
	dmaCopy(chrt4_anim_inv,   tileMemory + 64*24,  sizeof(chrt4_anim_inv));

	dmaCopy(grass2,   tileMemory + 64*25,  sizeof(grass2));
}

void SetUp()
{
	ConfigureScreen();
	ConfigureTimers();
}
void DrawMapData(){
    iprintf("\x1b[2;2HUntitled DuckS Game");
    int row,col;
	for(row=0;row<24;row++){
		for(col=startCol;col<startCol+screenWidthS;col++)
		{
			int pos_mapData            = PosToIndex(col,row);
			int pos_mapMemory            = PosToIndexSM(col-startCol,row);
			mapMemory[pos_mapMemory] = mapData[pos_mapData];
		}
	}
}

void DrawTiles(int x, int y, int* tiles, int width, int height){
	int row,col;
	for(row=0;row<width;row++){
		for(col=0;col<height;col++)
		{
			int tileIndex = row*width + col;
			int tile = tiles[tileIndex];
			int mapPos = PosToIndex(x+col, y+row);
			mapData[mapPos] = tile;
		}
	}
}
void MoveClouds(int* cloudsIndecies, int indexAmount){

	u16 mapBuffer[768] = {0};
	for(int row=0;row<11;row++){
		for(int col=screenWidthL-1;col>=0;col--)
		{
			int mapIndex = PosToIndex(col,row);
			bool isCloud = false;
			for(int i = 0; i < indexAmount; i++){
				if(mapData[mapIndex] == cloudsIndecies[i]){
					isCloud = true;
					break;
				}
			}
			if(!isCloud){
				continue;
			}
			int nextCol = col+1;
			if(nextCol > screenWidthL-1){
				nextCol = 0;
			}
			int nextMapIndex = PosToIndex(nextCol,row);
			mapBuffer[nextMapIndex] = mapData[mapIndex];
			mapData[mapIndex] = 0;
		}
	}

	for(int row=0;row<11;row++){
		for(int col=screenWidthL-1;col>=0;col--)
		{
			int mapIndex = PosToIndex(col,row);
			bool isCloud = false;
			for(int i = 0; i < indexAmount; i++){
				if(mapBuffer[mapIndex] == cloudsIndecies[i]){
					isCloud = true;
					break;
				}
			}
			if(!isCloud){
				continue;
			}
			mapData[mapIndex] = mapBuffer[mapIndex];
		}
	}
}
int duckPos = 15;
bool duckDirRight = true;
void MoveDuck(){
	u32 key;
    scanKeys();
    key = keysDown();
    if (key & KEY_RIGHT) {
    	duckPos++;
    	duckDirRight = true;
    	lockAnim = true;
    }
    if (key & KEY_LEFT){
    	duckPos--;	
		duckDirRight = false;
		lockAnim = true;
    }
    duckPos = clamp(duckPos,0,screenWidthL-2);
    if(duckPos - startCol < 6){
    	startCol--;
    }
    if(duckPos - startCol > 18){
    	startCol++;
    }
    startCol = clamp(startCol,0,screenWidthL-screenWidthS);
}
int main()
{
	int* smCloudIndecies = new int[]{1,2};
	int* lgCloudIndecies = new int[]{3,4,5,6};
	int* duckR_anim0 = new int[]{9,10,11,12};
	int* duckL_anim0 = new int[]{14,13,16,15};
	int* duckR_anim1 = new int[]{17,18,19,20};
	int* duckL_anim1 = new int[]{22,21,24,23};
	int* empty = new int[]{0,0,0,0};
	SetUp();
	while(1)
	{
		if(moveSmClouds){
			MoveClouds(smCloudIndecies, 2);
			moveSmClouds = false;
		}
		if(moveLgClouds){
			MoveClouds(lgCloudIndecies, 4);
			moveLgClouds = false;
		}
		DrawTiles(duckPos,10,empty,2,2);
		MoveDuck();
		int* duckR = duckR_anim0;
		if(duckAnim){
			duckR = duckR_anim1;
		}
		int* duckL = duckL_anim0;
		if(duckAnim){
			duckL = duckL_anim1;
		}
		if(duckDirRight){
			DrawTiles(duckPos,10,duckR,2,2);
		}
		else{
			DrawTiles(duckPos,10,duckL,2,2);

		}
		DrawMapData();
		swiWaitForVBlank();
	}
}