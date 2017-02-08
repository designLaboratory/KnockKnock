////////////////////////////////////////////////
// using GPIO                                 //
// Author:  Agnieszka Lupierz (ALupierz)      //
////////////////////////////////////////////////

#include "MKL46Z4.h"

class GPIO
{
  static bool FlagDetect;
	public:
	static void init_GPIO();
	static void FlagDetect_set();
	static void FlagDetect_clear();
	static bool detected();
};

