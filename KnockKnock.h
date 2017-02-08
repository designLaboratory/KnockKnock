////////////////////////////////////////////////////////////////////
// KnockKnock class                                               //
// Contains main logic of program                                 //
// declares and defines state machine                             //
// Diagram with polish description availble in docs               //
// for description in english ask directly to program developers  //
//                                                                //
// authors: Agnieszka Lupierz (LupierzA)                          //
//          Adrian Barnas (ABarnasFLY)                            //
////////////////////////////////////////////////////////////////////

#include "MKL46Z4.h"
#include "MPU6050.h"
#include "slcd.h"
#include "timer.h"
#include "LED.h"
#include "PIT_timer.h"

#define ACCEL_THERESHOLD 16360

enum State
{
	WAIT_FOR_FIRST = 0,
	FIRST_DETECTED,
	WAIT_FOR_SECOND,
	ONE_DETECTED,
	TWO_DETECTED
};

class KnockKnock
{
	LED diodes;
	slcd display;
	MPU6050 sensor;
	State on_waitForFirst();
	State on_waitForSecond();
	State on_firstDetected();
	State on_oneDetected();
	State on_twoDetected();
	public:
		void run();
};
