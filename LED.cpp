#include "LED.h"

const uint32_t MaskLED[] = {1UL << 5, 1UL << 29};

LED::LED()
{
			SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
			PORTD->PCR[5] |= PORT_PCR_MUX(1u);
			PTD->PDDR |= MaskLED[0];		
			SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
			PORTE->PCR[29] |= PORT_PCR_MUX(1u);
			PTE->PDDR |= MaskLED[1];	
}


void LED::off(int diode)
{
		switch(diode)
	{
		case 1:	
			FPTD->PSOR |= MaskLED[0];
		break;
		
		case 2:
			FPTE->PSOR |= MaskLED[1];
		break;
	}
}

void LED::on(int diode)
{
		switch(diode)
	{
		case 1:
			FPTD->PCOR |= MaskLED[0];
		break;
		
		case 2:
			FPTE->PCOR |= MaskLED[1];
		break;
	}	
}
