/* uProcessors project
	 authors: Agnieszka Lupierz
				   	Adrian Barnas
*/
#include "MKL46Z4.h"
#include "KnockKnock.h"

int main()
{
	Timer::initSysTick();
	Timer::wait(1000);
	KnockKnock program;
	program.run();
}


