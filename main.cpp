///////////////////////////////////////////
// Microprocessors System II Project     //
// Authors:                              //
// Agnieszka Lupierz                     //
// Adrian Barnaś                         //
///////////////////////////////////////////

#include "MKL46Z4.h"
#include "KnockKnock.h"

int main()
{
	Timer::initSysTick();
	Timer::wait(1000);
	KnockKnock program;
	program.run();
}


