////////////////////////////////////////////////
// MPU6050 handling using i2c interface       //
// Authors: Adrian Barnas (ABarnasFLY)        //
//          Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////

#include "MKL46Z4.h"
#include "i2c.h"
#include "GPIO.h"

class MPU6050
{
		i2c conectionDevice;
	public:
		MPU6050();
		int readHL(uint8_t);
		void setRegister(uint8_t, uint8_t);
		void enableOnMotionInterupt(uint16_t thereshold, uint16_t duration);
		void Init();
		bool detected();
	  void clearDetected();
		uint16_t readRawAccelZ();
};
