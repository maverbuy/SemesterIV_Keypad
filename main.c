#include "stm32l476xx.h"
#include "lcd.h"

void System_Clock_Init(void);

int main(void){
	
	unsigned char key;
	char s[6];
	unsigned char len = 0;
	int i;
	
	LCD_Initialization();
	LCD_Clear();
	
	//continously scan the keypad
	while(1){
		
		key = keypad_scan();

		//case statement for special/default cases of keypad
		switch(key)
		{
			case'*':
				s[len] = '*'; //display a *
			break;
			case '#':
				for (i =0; i <6; i++)
				{
					s[i] = 0; //clear the entire display
				}
			default:
			if (len >= 6)
			{
				len = 0; //reset to beginning of screen
			}
			s[len] = key; //get the keypad button pressed
			len++; //increment to next spot on screen

		}
		
		LCD_DisplayString((uint8_t*)s); //send keypad pressed button to display on LCD
		
	}
}

void System_Clock_Init(void){
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );
		
}

