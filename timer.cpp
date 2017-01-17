#include "timer.h"

extern "C" {
  void SysTick_Handler(void)
  {
		if(Timer::isStarted())
			Timer::tick(); 
  }
}

void Timer::initSysTick()
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
	m_sysTickInitialized = 1;
}
bool Timer::isStarted()
{
	return m_started;
}

bool Timer::m_started = 0;
unsigned int Timer::m_value = 0;
unsigned int Timer::m_compare = 0;
bool Timer::m_timeout = 0;
bool Timer::m_sysTickInitialized = 0;
void Timer::tick()
{
	m_value++;
	if(m_value > m_compare) m_timeout = true;
}
void Timer::wait(unsigned int milisecondes)
{
	setCompare(milisecondes);
	start();
	while(!timeout()) {};
}

void Timer::start()
{
	if(m_sysTickInitialized)
	{
	m_timeout = false;
	m_value = 0;
	m_started = 1;
	}
	else m_timeout = 1;
}

void Timer::setCompare(unsigned int milisecondes)
{
	m_compare = milisecondes;
}

bool Timer::timeout()
{
	return m_timeout;
}


