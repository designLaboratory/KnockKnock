#include "MKL46Z4.h"
#include "MPU6050.h"
#include "slcd.h"
#include "timer.h"

#define ACCEL_THERESHOLD 1

enum State
{
	POLLING_FIRST = 0,
	FIRST_DETECTED,
	POLLING_SECOND,
	ONE_DETECTED,
	TWO_DETECTED
};

class KnockKnock
{
	slcd display;
	MPU6050 sensor;
	State on_pollingFirst();
	State on_pollingSecond();
	State on_firstDetected();
	State on_oneDetected();
	State on_twoDetected();
	public:
		void run();
};
