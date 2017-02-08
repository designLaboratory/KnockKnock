////////////////////////////////////////////////
// Time utilities for KL46Z256                //
// using Period Interrupt Timer               //
// Author:  Agnieszka Lupierz (ALupierz)      //
////////////////////////////////////////////////

#include "MKL46Z4.h"

class PIT_timer
{
	public:
		static void init_PIT();
		static void PIT_IRQHandler();
	  static void wait(unsigned int);
		static void wait_and_stop(unsigned int);
	  static void FlagTimeout_set();
	  static void FlagTimeout_clear();
	private:
		static bool FlagTimeout;
};

