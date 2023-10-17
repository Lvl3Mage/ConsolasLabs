#include <nds.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include "way11.h"
#include "way31.h"
#include "way32.h"
# define TIMER_SPEED ( BUS_CLOCK /1024)
uint ticks = 0;
void RunTimer(){
	ticks += timerElapsed (0) ;
}
int GetSeconds(){
	return ticks/TIMER_SPEED;
}

class LogState
{
	int accumulatedLines = 0;
public:
	void Log(char* value, int lines){
		iprintf("\x1b[%d;0H%s", accumulatedLines, value);
		accumulatedLines += lines*2;
	}
	void Reset(){
		accumulatedLines = 0;
	}
};

LogState* logState;
class Room{
	
	char* description;
	int descLines;
public:
	class Door{
		int startRectCoord[2];
		int endRectCoord[2];
		public:
			Room* target;
			Door(int startCoordX, int startCoordY, int endCoordX, int endCoordY, Room* _target){
				startRectCoord[0] = startCoordX;
				startRectCoord[1] = startCoordY;
				endRectCoord[0] = endCoordX;
				endRectCoord[1] = endCoordY;
				target = _target;
			}
			bool isClicked(touchPosition coords){
				return startRectCoord[0] < coords.px && startRectCoord[1] < coords.py && endRectCoord[0] > coords.px && endRectCoord[1] > coords.py;
			}
	};
	std::vector<Door*> doors;
	int* bitmap;
	Room(char* _description, int _lines, int _bitmap[]){
		description = _description;
		descLines = _lines;
		bitmap = _bitmap;
	}
	void AddDoor(Door* _door){
		doors.push_back(_door);
	}
	void Draw(){
		dmaCopy(bitmap, VRAM_A, 98304);
	}
	void Log(){
		logState->Log(description, descLines);
	}
	Door* GetDoor(touchPosition clickCoords){
		for(int i = 0; i < doors.size(); i++){
			if(doors[i]->isClicked(clickCoords)){
				return doors[i];
			}
		}
		return NULL;
	}
};
Room* currentRoom;
Room* currentMonsterRoom;

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
	Room* startingRoom = new Room("room1", 1, way31Bitmap);
	Room* midRoom = new Room("room2", 1, way11Bitmap);
	Room* midRoom2 = new Room("room3", 1, way32Bitmap);
	startingRoom->AddDoor(new Room::Door(0,0,128,192,midRoom));
	startingRoom->AddDoor(new Room::Door(128,0,256,192,midRoom2));
	// Room* endRoom = new Room("room3", 1);
	currentRoom = startingRoom;
	logState = new LogState();
	REG_POWERCNT = POWER_LCD | POWER_2D_A;


	VRAM_A_CR    = VRAM_ENABLE | VRAM_A_LCD;


	REG_DISPCNT  = MODE_FB0;
	consoleDemoInit();
	//initialize it with a color
	// unsigned short *fbA = VRAM_A;
	// for(int i = 0; i < 192; i++){
	// 	for(int j = 0; j < 256; j++){
	// 		fbA[i*256 + j] = RGB15(31,0,0);
	// 	}
	// }

	while(1) 
	{
		touchPosition coords;
		touchRead(&coords);
		scanKeys();
		u32 keys = keysDown();
		if(keys & KEY_TOUCH){
			Room::Door* door;
			door = currentRoom->GetDoor(coords);
			if(door != NULL){
				currentRoom = door->target;
			}
		}
		logState->Reset();
		currentRoom->Log();
		currentRoom->Draw();
		swiWaitForVBlank();
	}
}
