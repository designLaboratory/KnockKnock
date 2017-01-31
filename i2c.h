////////////////////////////////////////////////
// i2c ( IIC) handling for Kinetis KL46Z256   //
// Clock setup  : 1 ( Bus clock 24MHz )       //
// I2C frequency: 100kHz                      //
// Authors: Adrian Barnas (ABarnasFLY)        //
//          Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////

#include "MKL46Z4.h"

class i2c
{
	I2C_Type* m_device;
	public:
	i2c(I2C_Type* device);
	
	void enable();  
	void disable(); 
	void start(); 
	void restart();
	void stop(); 
	void selectTX();
	void selectRX();
	void clearIICIF();
	void sendACK();
	void sendNACK();
	
	void init();
	void writeByte(uint8_t toSend);
	void readByte(uint8_t* readBuffer);
	bool isACK();
};
