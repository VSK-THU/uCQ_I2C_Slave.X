/*
 * File:   i2c_intr.c
 * Author: vschilli
 *
 * Created on July 12, 2024, 12:32 PM
 */


#include "i2c_intr.h"
#include "i2c_device.h"

void enableInterrupts(void)
{
    INTCON = 0x00;
    
    INTCONbits.GIE = 1;     //Enable Interrupts
    INTCONbits.PEIE = 1;    //Enable Peripheral Interrupts
}

void disableInterrupts(void)
{
    INTCONbits.GIE = 0;     //Disable Interrupts
    INTCONbits.PEIE = 0;    //Disable Peripheral Interrupts
}

void __interrupt() ISR(void)
{
    if (PIR1bits.SSP1IF)   //I2C
    {
        clearI2Cinterrupt();
        handle_I2C_ISR();
        return;
    }
    while(1);
}

