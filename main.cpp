////////////////////////////////////////////////
// Colecting data to detect proper referenc   //
// in clock detecting                         //
// Authors: Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////

#include "MKL46Z4.h"
#include "KnockKnock.h"
#include "UART.h"

int main()
{
	MPU6050 sensor;
	UART uart;
	sensor.Init();
	uart.init();
	uart.transmitEnable();
	
	while(1)
	{
		uart.sendInt16(sensor.readRawAccelZ());
	}
	
	
}


