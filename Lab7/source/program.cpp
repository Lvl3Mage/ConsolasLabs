#include <nds.h>
#include <stdio.h>
#include <bitset>
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
// int btn_pressed(){

// }
// int main(void)
// {
// 	int counter = 0;
// 	// logState = new LogState();
// 	consoleDemoInit();
// 	u16 lastVal;
// 	while(1) 
// 	{
// 		u16 val = ~REG_KEYINPUT & 0b0000000011000011;
// 		if (val && val != lastVal){
// 			counter++;	
// 		}
// 		lastVal = val;
// 		// std::bitset<16> byte1 = std::bitset<16>(~REG_KEYINPUT & 0b0000000011000011); // byte1.to_string().c_str()
// 		iprintf("\x1b[6;0H %d", counter);
// 		swiWaitForVBlank();
// 	}
// }
int counterA = 0;
int counterB = 0;
int counterUp = 0;
int counterDown = 0;

void btn_pressed() 
{
	u16 keyA = ~REG_KEYINPUT & 0b0000000000000001;
	u16 keyB = ~REG_KEYINPUT & 0b0000000000000010;
	u16 keyDown = ~REG_KEYINPUT & 0b0000000010000000;
	u16 keyUp = ~REG_KEYINPUT & 0b0000000001000000;
	if (keyA) counterA++;
	if (keyB) counterB++;
	if (keyDown) counterDown++;
	if (keyUp) counterUp++;
}

int main(void)
{
	irqSet(IRQ_KEYS,btn_pressed);
	irqEnable(IRQ_KEYS); 
	REG_KEYCNT = 0x40C3; 

	consoleDemoInit();
	while (1)
	{ 
		iprintf("\x1b[1;0HCounterA %d", counterA);
		iprintf("\x1b[3;0HCounterB %d", counterB);
		iprintf("\x1b[5;0HCounterUp %d", counterUp);
		iprintf("\x1b[7;0HCounterDown %d", counterDown);

		swiWaitForVBlank();
	}
}