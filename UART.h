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
