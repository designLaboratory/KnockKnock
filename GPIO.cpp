////////////////////////////////////////////////
// using GPIO               									//
// Author:  Agnieszka Lupierz (ALupierz)      //
////////////////////////////////////////////////


#include "GPIO.h"

void GPIO::init_GPIO()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[13] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[13] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK;
	PORTA->PCR[13] &= ~PORT_PCR_PS_MASK;
	PTA->PDDR &= ~(1<<13);	
	
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTA_IRQn);
}

void GPIO::PORTA_IRQHandler()
{
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	if (PORTA->ISFR & (1UL<<13))
	{
		FlagDetect_set();
	}
	PORTA->ISFR = 0xffffffff;
}

void GPIO::FlagDetect_set()
{
	FlagDetect = true;
}

void GPIO::FlagDetect_clear()
{
	FlagDetect = false;
}

bool GPIO::detected()
{
	return FlagDetect;
}