/*
 * File:   config_bits.c
 * Author: vschilli
 *
 * Created on July 12, 2024, 12:54 PM
 */

#ifndef __18F24K22
 #ifndef __18F25K22
  #ifndef __18F26K22
    ERROR No Configuration bits are defined! Double click this message for more details."
  #endif
 #endif
#endif

// PIC18F2xK22 Configuration Bit Settings
// CONFIG1H
#pragma config FOSC = INTIO67   // Oscillator (LP,XT,HSHP,HSMP,RC,RCIO6,ECHP,
                                //  ECHPIO6,INTIO67,INTIO7,ECMPIO6,ECLP,ECLPIO6)
#pragma config PLLCFG = OFF     // 4X PLL Enable
#pragma config PRICLKEN = ON    // Primary clock enable
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable
#pragma config IESO = OFF       // Internal/External Oscillator Switchover

// CONFIG2L
#ifdef __DEBUG
    #pragma config PWRTEN = OFF // Power-up Timer Enable
#else
    #pragma config PWRTEN = ON
#endif
#pragma config BOREN = OFF      // Brown-out Reset Enable  (OFF,ON,NOSLP,SBORDIS)
#pragma config BORV = 190       // Brown Out Reset Volt.(285,250,220,190)[V/100]

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable (OFF,NOSLP,SWON,ON)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTB3  // ECCP2 B output mux (PORTB3, PORTC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable
#pragma config CCP3MX = PORTB5  // CCP3 MUX (PORTB5, PORTC6)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up
#pragma config T3CMX = PORTC0   // Timer3 Clock input mux (PORTB5,PORTC0)
#pragma config P2BMX = PORTB5   // ECCP2 B output mux (PORTB5,PORTC0)
//#ifdef __DEBUG
//    #pragma config MCLRE = EXTMCLR  // MCLR Pin Enable (MCLR / RE3)
//#else
//    #pragma config MCLRE = INTMCLR
//#endif

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable
#pragma config LVP = ON         // Single-Supply ICSP Enable
#pragma config XINST = OFF      // Extended Instruction Set Enable

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0
#pragma config CP1 = OFF
#ifndef __18F24K22
    #pragma config CP2 = OFF
    #pragma config CP3 = OFF
#endif
// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection
#pragma config CPD = OFF        // Data EEPROM Code Protection

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0
#pragma config WRT1 = OFF
#ifndef __18F24K22
    #pragma config WRT2 = OFF
    #pragma config WRT3 = OFF
#endif

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection
#pragma config WRTB = OFF       // Boot Block Write Protection
#pragma config WRTD = OFF       // Data EEPROM Write Protection

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0
#pragma config EBTR1 = OFF
#ifndef __18F24K22
    #pragma config EBTR2 = OFF
    #pragma config EBTR3 = OFF
#endif
// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection
            