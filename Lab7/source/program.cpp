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
	int counter = 0;
	// logState = new LogState();
	consoleDemoInit();
	u16 lastVal;
	while(1) 
	{
		u16 val = ~REG_KEYINPUT & 0b0000000011000011;
		if (val && val != lastVal){
			counter++;	
		}
		lastVal = val;
		// std::bitset<16> byte1 = std::bitset<16>(~REG_KEYINPUT & 0b0000000011000011); // byte1.to_string().c_str()
		iprintf("\x1b[6;0H %d", counter);
		swiWaitForVBlank();
	}
}
