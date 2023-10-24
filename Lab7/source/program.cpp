#include <nds.h>
#include <stdio.h>
int counter = 0;

void int_timer() 
{
	counter ++;
}
void btn_pressed() 
{
	u16 keyA = ~REG_KEYINPUT & 0b0000000000000001;
	u16 keyB = ~REG_KEYINPUT & 0b0000000000000010;
	u16 keyDown = ~REG_KEYINPUT & 0b0000000010000000;
	u16 keyUp = ~REG_KEYINPUT & 0b0000000001000000;
	if (keyA) TIMER_DATA(0)=32768; 
	if (keyB) TIMER_DATA(0)=49152; 
	if (keyDown) counter = 0;
	if (keyUp) TIMER_DATA(0)=0; 
	TIMER_CR(0) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ ;
}
int main(void) 
{
	irqSet(IRQ_KEYS,btn_pressed);
	irqEnable(IRQ_KEYS); 
	REG_KEYCNT = 0x40C3; 

	consoleDemoInit();
	irqEnable(IRQ_TIMER0);
	irqSet(IRQ_TIMER0,int_timer); 

	TIMER_DATA(0)=32768; 
	TIMER_CR(0) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ ;
	while(1) 
	{

		iprintf("\x1b[12;2H%2i", counter);
		swiWaitForVBlank(); 
	}
}