/* uProcessors project
	 authors: Agnieszka Lupierz
				   	Adrian Barnas
*/
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


