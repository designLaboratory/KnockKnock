////////////////////////////////////////////////
// UART2 handling for Kinetis KL46Z256        //
// Clock setup   : 1 ( Bus clock 24MHz )      //
// UART baudrate : 9600                       //
// No parity                                  //
// One stop bit                               //
// Authors: Adrian Barnas (ABarnasFLY)        //
//          Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////

#include <MKL46Z4.h>

class UART
{
	public:
	void init();
	void receiveEnable();
	void receiveInteruptEnable();
	void transmitEnable();
	void sendByte(char data);
	void sendInt16(uint16_t data);
};
