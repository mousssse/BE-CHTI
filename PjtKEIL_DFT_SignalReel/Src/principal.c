#include "DriverJeuLaser.h"

extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern short int LeSignal;
int tab[64];
short int dma_buf[64];

void systick_callback(void) {
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	for (int i = 0; i < 64; i++) {
		tab[i] = DFT_ModuleAuCarre(dma_buf, i);
	}
}

int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// mise en place du callback
CLOCK_Configure();
Systick_Period_ff(360000); // 0.005 * 72 000 000 (fréquence du CPU 72MHz)
Systick_Prio_IT(2, systick_callback); 
SysTick_On;
SysTick_Enable_IT;
	
Init_TimingADC_ActiveADC_ff(ADC1, 72);
Single_Channel_ADC(ADC1, 2);
Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
Init_ADC1_DMA1(0, dma_buf);
	

//============================================================================	
	
	
while	(1)
	{
	}
}

