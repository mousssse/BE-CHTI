#include "DriverJeuLaser.h"
#include "Affichage_Valise.h"
#include "GestionSon.h"
#include <time.h>
#include <stdlib.h>

extern int PeriodeSonMicroSec;
extern int DFT_ModuleAuCarre( short int * Signal64ech, char k);
extern char LED;
int flag = 1 ;

// permet de compter qu'une seule fois un point et non 12 à 14 fois mais ne fonctionne qu'avec la malette
int stop = 0;

// que 4 joueurs car on n'a que 4 afficheurs de points
int nbJoueurs = 4;
int dft[4];
short int dma_buf[64];
int scores[4];
int frequences[6] = {17, 18, 19, 20};
int led[4] = {LED_Cible_4, LED_Cible_3, LED_Cible_2,  LED_Cible_1};
int ledIndex;
int active;

// choisit une cible au hasard
void chooseTarget() {
	// pour que la nouvelle cible soit différente de la précédente
	int random = rand() % 3;
	ledIndex = (1 + random + ledIndex) % 4;
	active = led[ledIndex];
	Choix_Capteur(active+1);
	Prepare_Set_LED(active);
	// à commenter qd on n'a pas la malette :
	Mise_A_Jour_Afficheurs_LED();
}

// remet le flag à 0 pour que callbackson puisse jouer le son
void startSon() {
	flag = 0;
}

void systick_callback(void) {
	if (stop) {
		stop = 0;
	}
	Start_DMA1(64);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	
	for (int numJoueur = 0; numJoueur < nbJoueurs; numJoueur++) {
		if (!stop) {
			dft[numJoueur] = DFT_ModuleAuCarre(dma_buf, frequences[numJoueur]); 
			if (dft[numJoueur] > 0x1000) {
				// sur la malette, mais on voulait mettre
				// plus de points pour les plus petites cibles
				/*if (active == LED_Cible_1) {
					scores[numJoueur] += 1;
				}
				else {
					scores[numJoueur] += 2;
				}*/
				scores[numJoueur]++;
				stop = 1;
				startSon();
				//affichage et changement de cible
				Prepare_Clear_LED(active);
				Prepare_Afficheur(numJoueur+1, scores[numJoueur]);
				chooseTarget();
			}
		}
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
Systick_Prio_IT(12, systick_callback); 
SysTick_On;
SysTick_Enable_IT;
	
Init_TimingADC_ActiveADC_ff(ADC1, 72);
Single_Channel_ADC(ADC1, 2);
Init_Conversion_On_Trig_Timer_ff(ADC1, TIM2_CC2, 225);
Init_ADC1_DMA1(0, dma_buf);

// init gestion son
PWM_Init_ff(TIM3, 3, 720);
	
GPIO_Configure(GPIOB, 0, OUTPUT, ALT_PPULL);	
	
Timer_1234_Init_ff(TIM4, 72*PeriodeSonMicroSec);
Active_IT_Debordement_Timer(TIM4, 2, callbackson);


	
for (int i = 0; i < nbJoueurs; i++) {
	scores[i] = 0;
}
Init_Affichage();
for (int i = 0; i < 4; i++) {
	Prepare_Afficheur(i, 0);
}
// première valeur d'index entre 0 et 3
ledIndex = rand() % 4;
chooseTarget();

//============================================================================	
	
	
while	(1)
	{
	}
}

