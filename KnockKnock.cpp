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

#include "KnockKnock.h"
	
void KnockKnock::run()
{
	diodes.off(1);
	diodes.off(2);
	
	display.Initialize();
	display.Display(1000,10);
	sensor.Init();
	display.Display(1001,10);

	State state = WAIT_FOR_FIRST;
	while(1)
	{
		switch (state)
		{
			case WAIT_FOR_FIRST:
				state = on_waitForFirst();
				break;
			case FIRST_DETECTED:
				state = on_firstDetected();
				break;
			case WAIT_FOR_SECOND:
				state = on_waitForSecond();
				break;
			case ONE_DETECTED:
				state = on_oneDetected();
				break;
			case TWO_DETECTED:
				state = on_twoDetected();
				break;
		}
	}
	
}

State KnockKnock::on_waitForFirst()
{
	while(1)
	{
		display.Display(0xAAAA,16);
		if(sensor.readRawAccelZ() > ACCEL_THERESHOLD) return FIRST_DETECTED;
	}
}

State KnockKnock::on_firstDetected()
{
	diodes.on(1);
	Timer::wait(200);

	
	return WAIT_FOR_SECOND;
}

State KnockKnock::on_waitForSecond()
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
	Timer::wait(2000);
	diodes.off(1);
	diodes.off(2);
	return WAIT_FOR_FIRST;
}

State KnockKnock::on_twoDetected()
{
	display.Display(2,10);
	diodes.on(2);
	Timer::wait(2000);
	diodes.off(1);
	diodes.off(2);
	return WAIT_FOR_FIRST;
	
}
