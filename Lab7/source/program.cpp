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
int contador = 0;

void int_boton() 
{
  if (REG_KEYINPUT == 0x03FE)
  {
    iprintf("\x1b[1;0H Boton A Pulsado");
    contador = 0;
  }
}

int main(void)
{
  irqSet(IRQ_KEYS,int_boton);
  irqEnable(IRQ_KEYS); 
  REG_KEYCNT = 0x4001; 
  
  consoleDemoInit();
  while (1)
  { 
    contador ++;
    iprintf("\x1b[1;0HPulsa A                ");
    iprintf("\x1b[14;0HContador = %04i", contador);

    swiWaitForVBlank();
  }
}