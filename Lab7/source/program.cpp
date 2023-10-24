#include <nds.h>
#include <stdio.h>
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
	// logState = new LogState();
	consoleDemoInit();
	while(1) 
	{
		while (REG_KEYINPUT != 0x03FD)
			iprintf("\x1b[6;0H Esperando Boton B       ");
		iprintf("\x1b[6;0HBoton B pulsado             ");
		swiWaitForVBlank();
	}
}