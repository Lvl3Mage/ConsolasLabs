#include <nds.h>
#include <stdio.h>
int counter = 0;

void int_timer() 
{
	counter ++;
}

int main(void) 
{
	consoleDemoInit();
	irqEnable(IRQ_TIMER0);
	irqSet(IRQ_TIMER0,int_timer); 

	TIMER_DATA(0)=49152; 
	TIMER_CR(0) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ ;
	while(1) 
	{
		iprintf("\x1b[12;2H%2i", counter);
		swiWaitForVBlank();
	}
}