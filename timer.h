#include "MKL46Z4.h"

class Timer
{
	public:
		static bool m_timeout;
		static unsigned int m_compare;
		static unsigned int m_value;
		static void wait(unsigned int miliseconds);
		static void start();
		static bool timeout();
		static void setCompare(unsigned int milliseconds);
};
