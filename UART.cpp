////////////////////////////////////////////////
// UART2 handling for Kinetis KL46Z256        //
// Clock setup   : 1 ( Bus clock 24MHz )      //
// UART baudrate : 9600                       //
// No parity                                  //
// One stop bit                               //
// Authors: Adrian Barnas (ABarnasFLY)        //
//          Agnieszka Lupierz (LupierzA)      //
////////////////////////////////////////////////


#include "UART.h"
#include <string>


void UART::init() {
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	PORTE->PCR[16] |= PORT_PCR_MUX(3); //UART0_TX
	PORTE->PCR[17] |= PORT_PCR_MUX(3); //UART0_RX
		
	UART2->C2 &= ~(UART_C2_RE_MASK | UART_C2_TE_MASK);
	
	UART2->BDH |= UART_BDH_SBR(0);
	UART2->BDL |= UART_BDL_SBR(156);
	UART2->BDH &= ~UART_BDH_SBNS_MASK;
	UART2->C1 &= ~(UART_C1_M_MASK | UART_C1_PE_MASK);
	
}

void UART::sendInt16(uint16_t data)
{
	uint16_t format = 10;
	uint8_t val = 0;
	val = (data / (format*format*format*format) ) % 10;
	sendByte(val + 48);
	val = (data / (format*format*format) ) % 10;
	sendByte(val + 48);
	val = (data / (format*format) ) % 10;
	sendByte(val + 48);
	val = (data / format ) % 10;
	sendByte(val + 48);
	val = data % 10;
	sendByte(val + 48);
}
void UART::sendByte(char data)
{
	 while( !(UART2->S1 & UART_S1_TDRE_MASK) );
   // Zapis 8-miu bitów
	 UART2->D = data;
}


void UART::transmitEnable()
{
	UART2->C2 |= UART_C2_TE_MASK;
}

void UART::receiveEnable()
{
	UART2->C2 |= UART_C2_RE_MASK;
}


void UART::receiveInteruptEnable()
{
	NVIC_ClearPendingIRQ(UART2_IRQn);
	NVIC_SetPriority(UART2_IRQn, 1);
	NVIC_EnableIRQ(UART2_IRQn);
	UART2->C2 |= UART_C2_RIE_MASK;
}
extern "C" void UART2_IRQHandler() {
/*Handle the receive interupt*/
	int a = UART2->S1;
}