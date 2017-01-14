#include "timer.h"

unsigned int Timer::m_value = 0;
unsigned int Timer::m_compare = 0;
bool Timer::m_timeout = 0;
void Timer::wait(unsigned int milisecondes)
{
	setCompare(milisecondes);
	start();
	while(!timeout()) {};
}

void Timer::start()
{
	m_timeout = false;
	m_value = 0;
	SysTick_Config(SystemCoreClock / 1000);
	NVIC_ClearPendingIRQ(SysTick_IRQn);
	NVIC_EnableIRQ(SysTick_IRQn);	
}

void Timer::setCompare(unsigned int milisecondes)
{
	m_compare = milisecondes;
}

bool Timer::timeout()
{
	return m_timeout;
}

void SysTick_Handler()
{
	Timer::m_value++;
	if (Timer::m_value > Timer::m_compare)
	{
		Timer::m_timeout = true;
		NVIC_DisableIRQ(SysTick_IRQn);
	}
}
