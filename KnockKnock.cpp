#include "KnockKnock.h"

void KnockKnock::run()
{
	State state;
	while(1)
	{
		switch (state)
		{
			case POLLING_FIRST:
				state = on_pollingFirst();
				break;
			case FIRST_DETECTED:
				state = on_firstDetected();
				break;
			case POLLING_SECOND:
				state = on_pollingSecond();
				break;
			case ONE_DETECTED:
				state = on_oneDetected();
				break;
			case TWO_DETECTED:
				state = on_twoDetected();
		}
	}
	
}

State KnockKnock::on_pollingFirst()
{
	while(1)
	{
		if(sensor.readRawAccelZ() > ACCEL_THERESHOLD) return FIRST_DETECTED;
	}
}

State KnockKnock::on_firstDetected()
{
	Timer::wait(10);
	
	return POLLING_SECOND;
}

State KnockKnock::on_pollingSecond()
{
	Timer::setCompare(1000);
	Timer::start();
	while(!Timer::timeout())
	{
		if(sensor.readRawAccelZ() > ACCEL_THERESHOLD) return TWO_DETECTED;
	}
	return ONE_DETECTED;
}

State KnockKnock::on_oneDetected()
{
	display.Display(1,10);
	return POLLING_FIRST;
}

State KnockKnock::on_twoDetected()
{
	display.Display(2,10);
	return POLLING_FIRST;
}
