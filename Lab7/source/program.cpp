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

int main(void)
{
	int counterA = 0;
	int counterB = 0;
	int counterDown = 0;
	int counterUp = 0;
	// logState = new LogState();
	consoleDemoInit();
	while(1) 
	{
		while (!(~REG_KEYINPUT & 0b0000000011000011)){
			iprintf("\x1b[6;0H Waiting for key");
		}
		if((~REG_KEYINPUT & 0b0000000000000001)) counterA++;
		if((~REG_KEYINPUT & 0b0000000000000010)) counterB++;
		if((~REG_KEYINPUT & 0b0000000001000000)) counterUp++;
		if((~REG_KEYINPUT & 0b0000000010000000)) counterDown++;

		// std::bitset<16> byte1 = std::bitset<16>(~REG_KEYINPUT & 0b0000000011000011); // byte1.to_string().c_str()
		
		iprintf("\x1b[6;0H %d", counterA);
		iprintf("\x1b[6;0H %d", counterB);
		iprintf("\x1b[6;0H %d", counterUp);
		iprintf("\x1b[6;0H %d", counterDown);
		swiWaitForVBlank();
	}
}
