////////////////////////////////////////////////
// i2c ( IIC) handling for Kinetis KL46Z256   //
// Clock setup  : 1 ( Bus clock 24MHz )       //
// I2C frequency: 100kHz                      //
// Authors: Adrian Barnas (ABarnasFLY)        //
//          Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////

#include "i2c.h"

i2c::i2c(I2C_Type* device):
m_device(device)
{
	
}

void i2c::init() //Frequency in argument :TODO
{
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	if(m_device == I2C0)
	{
		SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
		PORTE->PCR[18] |= PORT_PCR_MUX(4);
		PORTE->PCR[19] |= PORT_PCR_MUX(4);
	}
	else
	{
		SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
		PORTE->PCR[0] |= PORT_PCR_MUX(6);
		PORTE->PCR[1] |= PORT_PCR_MUX(6);
	}
	m_device->F = I2C_F_ICR(0x1F); //100kHz	
}

void i2c::enable()
{
	m_device->C1 |= I2C_C1_IICEN_MASK;
}

void i2c::disable()
{
	m_device->C1 &= ~I2C_C1_IICEN_MASK;
}

void i2c::start()
{
	m_device->C1 |= I2C_C1_MST_MASK;
}

void i2c::stop()
{
	m_device->FLT |= I2C_FLT_STOPF_MASK; //clear stop flag
	m_device->C1 &= ~I2C_C1_MST_MASK;

		//wait until stop sent
	while((m_device->FLT & I2C_FLT_STOPF_MASK) == 0)
	{
		m_device->C1 &= ~I2C_C1_MST_MASK;
	}
}

void i2c::selectTX()
{
	m_device->C1 |= I2C_C1_TX_MASK;
}

void i2c::selectRX()
{
	m_device->C1 &= ~I2C_C1_TX_MASK;
}

void i2c::clearIICIF()
{
	m_device->S |= I2C_S_IICIF_MASK;
}

void i2c::writeByte(uint8_t toSend)
{
	selectTX();
	clearIICIF();
	m_device->D = toSend;
	
	while((m_device->S & I2C_S_IICIF_MASK) == 0){};

}

void i2c::readByte(uint8_t* readBuffer)
{

	selectRX();
	clearIICIF();
	*readBuffer = m_device->D;
	while((m_device->S & I2C_S_IICIF_MASK) == 0){};
	selectTX();
	*readBuffer = m_device->D;
}

void i2c::sendACK() // default i2c send ACK when TXAK is cleared, this function only clear TXAK
{
	m_device->C1 &= ~I2C_C1_TXAK_MASK;
}
	
void i2c::sendNACK()
{
	m_device->C1 |= I2C_C1_TXAK_MASK;
}
void i2c::restart()
{
	m_device->C1 |= I2C_C1_RSTA_MASK;
}
bool i2c::isACK()
{
	return !(m_device->S & I2C_S_RXAK_MASK);
}
