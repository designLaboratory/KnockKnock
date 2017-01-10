#include <MKL46Z4.h>
#include "MPU6050.h"
#include "slcd.h"
#define RED_MASK  1UL<<5				//Red led is Port D bit 5
#define GREEN_MASK 1UL<<29			//Green led is Port C bit 5/

uint8_t v[2];
void initLED();
void ledOnR();
void ledOnG();
int ack;
int main()
{
	int i = 0;
	slcd display;
	display.Initialize();
	MPU6050 sensor;
	sensor.Init();
	display.Display(sensor.readRawAccelZ(),16);
	while(1)
	{
		display.Display(sensor.readRawAccelZ(),16);
		i+=2;
	}
}
void initLED()
{
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[5] = PORT_PCR_MUX(1);                       
  PORTE->PCR[29] = PORT_PCR_MUX(1); 
	FPTD->PDDR |= RED_MASK	;          /* enable PTB18/19 as Output */
	FPTE->PDDR |= GREEN_MASK	; 
	FPTE->PSOR |= GREEN_MASK ; 
	FPTD->PSOR |= RED_MASK ;
}

void ledOnG()
{
	FPTE->PTOR |= GREEN_MASK;
}

void ledOnR()
{
	FPTD->PTOR |= RED_MASK;
}