////////////////////////////////////////////////
// Time utilities for KL46Z256                //
// using Period Interrupt Timer               //
// Author:  Agnieszka Lupierz (ALupierz)      //
////////////////////////////////////////////////


#include "PIT_timer.h"
bool PIT_timer::FlagTimeout = false;

void PIT_timer::init_PIT()
{
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;

	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_CHN_MASK;
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;

	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);

	
}

bool PIT_timer::timeout()
{
	return FlagTimeout;
}
extern "C" 
{
void PIT_IRQHandler()
{
	NVIC_ClearPendingIRQ(PIT_IRQn);
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK)
	{
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
		PIT_timer::FlagTimeout_set();
		PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
	}
}
}

void PIT_timer::wait(unsigned int value)
{
	FlagTimeout_clear();
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(value*24000);
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
}

void PIT_timer::wait_and_stop(unsigned int value)
{
	wait(value);
	while(FlagTimeout==false);	
}

void PIT_timer::FlagTimeout_set()
{
	FlagTimeout = true;
}

void PIT_timer::FlagTimeout_clear()
{
	FlagTimeout = false;
}
