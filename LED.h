////////////////////////////////////////////////
// slcd handling for Kinetis KL46Z256         //
// used code from microprocessors classes     //
// Authors: Adrian Barnas (ABarnasFLY)        //
//          Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////

#include "MKL46Z4.h" 

class LED
{
	public:
		LED(void);
		void on(int diode);
		void off(int diode);
};
