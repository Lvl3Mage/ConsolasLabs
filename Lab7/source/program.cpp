#include <nds.h>
#include <stdio.h>
int counter1 = 0;
int counter2 = 0;

void int_timer1() 
{
	counter1 ++;
}
void int_timer2(){
	counter2 ++;
}

int main(void) 
{
	consoleDemoInit();
	irqEnable(IRQ_TIMER0);
	irqEnable(IRQ_TIMER1);
	irqSet(IRQ_TIMER0,int_timer1); 
	irqSet(IRQ_TIMER1,int_timer2); 

	TIMER_DATA(0)=32768; 
	TIMER_CR(0) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ ;

	TIMER_DATA(1)=0; 
	TIMER_CR(1) = TIMER_DIV_1024 | TIMER_ENABLE | TIMER_IRQ_REQ ;
	while(1) 
	{
		iprintf("\x1b[12;2H%2i", counter1);
		iprintf("\x1b[14;2H%2i", counter2);
		swiWaitForVBlank();
	}
}