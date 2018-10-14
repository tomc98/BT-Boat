#include "registers.h"

extern void DelayMs(unsigned int);

void m1F(){
	GPIO_PORTC_DATA &= ~0x30;
	GPIO_PORTC_DATA |= 0x10;
}

void m1B(){
	GPIO_PORTC_DATA &= ~0x30;
	GPIO_PORTC_DATA |= 0x20;
}

void m1S(){
	GPIO_PORTC_DATA &= ~0x30;
}

void m2F(){
	GPIO_PORTC_DATA &= ~0xC0;
	GPIO_PORTC_DATA |= 0x40;
}

void m2B(){
	GPIO_PORTC_DATA &= ~0xC0;
	GPIO_PORTC_DATA |= 0x80;
}

void m2S(){
	GPIO_PORTC_DATA &= ~0xC0;
}

void soundDelay(int time){
	for(int j = 0; j < time; j++){
		for(int i = 0; i <= 200; i++);
	}
}


void hornF(){
	GPIO_PORTD_DATA &= ~0x1;
	soundDelay(50);
	GPIO_PORTD_DATA |= 0x1;
	soundDelay(50);
}



int main(void)
{	  
	int horn = 0;
	char message ; // 8 bit value

	// activate clock for UART
	SYSCTL_RCGCUART = SYSCTL_RCGCUART | 0x03 ;

	// delay to settle
	while ((SYSCTL_PRUART & 0x03) != 0x03);

	// activate clock for GPIO
	SYSCTL_RCGCGPIO = SYSCTL_RCGCGPIO | 0x03 ;

	// delay to settle
	while ((SYSCTL_PRGPIO & 0x03) != 0x03);

	//clocks done
	//------UART 0 setup for debug------\\
	//disable UART
	UART0_CTL = UART0_CTL & ~0x1;
	
	//Baud Rate set
	UART0_IBRD = 0xD0;
	UART0_FBRD = 0x15;
	//Line control
	UART0_LCRH |= 0x60;
	//enable Uart
	UART0_CTL = UART0_CTL | 0x321;
	
	//digital mode
	GPIO_PORTA_DEN = GPIO_PORTA_DEN | 0x3;
	//alt function stuff
	GPIO_PORTA_AFSEL = GPIO_PORTA_AFSEL | 0x3;
	GPIO_PORTA_PCTL &= ~0xFF;
	GPIO_PORTA_PCTL |= 0x11;
	
	//------UART setup for bluetooth-----\\
	//disable UART
	UART1_CTL = UART1_CTL & ~0x1;
	
	//Baud Rate set
	UART1_IBRD = 0xD0;
	UART1_FBRD = 0x15;
	//Line control
	UART1_LCRH |= 0x60;
	//enable Uart
	UART1_CTL |= 0x321;
	
	//digital mode
	GPIO_PORTB_DEN = GPIO_PORTB_DEN | 0x3;
	GPIO_PORTB_PUR |= 0x1;
	//alt function stuff
	GPIO_PORTB_AFSEL = GPIO_PORTB_AFSEL | 0x3;
	GPIO_PORTB_PCTL &= ~0xFF;
	GPIO_PORTB_PCTL |= 0x11;
	
	//-----motor stuff-----\\
	// activate clock for GPIO
	SYSCTL_RCGCGPIO = SYSCTL_RCGCGPIO | 0x04 ;

	// delay to settle
	while ((SYSCTL_PRGPIO & 0x04) != 0x04);
	
	//gpio stuff
	GPIO_PORTC_DIR |= 0xF0;
	GPIO_PORTC_AFSEL &= ~0xF0;
	GPIO_PORTC_DR2R |= 0xF0;
	GPIO_PORTC_DEN |= 0xF0;
	GPIO_PORTC_PCTL &= ~0xF0;
	
	//-----ultrasonic stuff-----\\
	// activate clock for GPIO
	SYSCTL_RCGCGPIO = SYSCTL_RCGCGPIO | 0x08 ;

	// delay to settle
	while ((SYSCTL_PRGPIO & 0x08) != 0x08);
	
	//gpio stuff
	GPIO_PORTD_DIR &= ~0xCF;
	GPIO_PORTD_DIR |= 0x45;
	GPIO_PORTD_AFSEL &= ~0xCF;
	GPIO_PORTD_DR8R |= 0x45;
	GPIO_PORTD_PDR |= 0x8A;
	GPIO_PORTD_DEN |= 0xCF;
	GPIO_PORTD_PCTL &= 0x0;
	

	while(1){
		if(((UART1_FR >> 4) & 1) != 1){
			message = UART1_DR & 0xFF;
			if(message == 0x30){
				m1S();
				m2S();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x77;
			}else if(message == 0x31){
				m1S();
				m2F();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x32){
				m1S();
				m2B();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x33){
				m1F();
				m2S();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x34){
				m1F();
				m2F();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x35){
				m1F();
				m2B();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x36){
				m1B();
				m2S();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x37){
				m1B();
				m2F();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x38){
				m1B();
				m2B();
				while(((UART1_FR >> 5) & 1) == 1);
				UART1_DR = 0x73;
			}else if(message == 0x39){
				if(horn == 1)horn = 0;
				else horn = 1;
			}
			if(horn == 1){
				hornF();
			}
			while(((UART1_FR >> 5) & 1) == 1);
			UART1_DR = 72;
		}
	}
}
