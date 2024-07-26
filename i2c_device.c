/*
 * File:   i2c_device.c
 * Author: vschilli
 *
 * Created on July 12, 2024, 12:34 PM
 */

#include "i2c_device.h"
#include "global_def.h"

void initI2C(void)
{
    //Disable I2C Interrupts
    disableI2Cinterrupt();

    //Clear Configuration and Turn off I2C
    SSP1CON1 = 0x00;

    //Setup IO
    setupI2Cpins();

    SSP1STAT = 0x00;
    SSP1STATbits.SMP = 1;       //Disable Slew Rate Control (100kHz)
    SSP1STATbits.CKE = 0;       //Disable SMBUS inputs

    SSP1CON1bits.SSPM = 0b1110; //I2C 7-bit Address Mode ***
    SSP1CON1bits.CKP = 1;

    SSP1CON2 = 0x00;
    SSP1CON2bits.GCEN = 0;      //Disable General Call
    SSP1CON2bits.ACKDT = 0;     //Polarity of ACK
    SSP1CON2bits.ACKEN = 1;     //Enable ACK
    SSP1CON2bits.RCEN = 1;      //Enable Rx
    SSP1CON2bits.SEN = 0;       //Disable Clock Stretching

    SSP1CON3 = 0x00;
    SSP1CON3bits.PCIE = 1;      //Enable STOP Interrupt
    SSP1CON3bits.SCIE = 1;      //Enable START Interrupts
//    SSP1CON3bits.SDAHT = 0;     //100ns hold time
    SSP1CON3bits.AHEN = 0;      //Disable Address Hold
    SSP1CON3bits.DHEN = 0;      //DIsable Data Hold

    SSP1ADD = I2C_BASE_ADDRESS << 1;    //Sets the I2C Address
    SSP1MSK = 0xFE;             //Check 7-bit of the address

    //Clear any old ISRs + Enable I2C Interrupt
    clearI2Cinterrupt();
    enableI2Cinterrupt();

    //Turn on the Module
    SSP1CON1bits.SSPEN = 1;
}

void setupI2Cpins(void)
{
    //Pins are Inputs
    TRISCbits.TRISC3 = 1;   //SCL
    TRISCbits.TRISC4 = 1;   //SDA

    //Digital Inputs
    ANSELCbits.ANSC3 = 0;
    ANSELCbits.ANSC4 = 0;
}

#define I2C_BUFFER_SIZE 16
static volatile uint8_t i2cBuffer[I2C_BUFFER_SIZE];
static volatile uint8_t i2cBufferIdx;
static volatile uint8_t i2cRegAddr;

typedef enum{
    S_STOPPED,
    S_STARTED,
    S_REG_ADDRESS,   // wait for it
    S_WRITE,
    S_READ
}I2C_Status_t;
static volatile I2C_Status_t state = S_STOPPED;

void init_I2C_FSM(void)
{
    state = S_STOPPED;
    i2cBufferIdx = 0;
    for(uint8_t i=0;i<I2C_BUFFER_SIZE;i++) i2cBuffer[i]=0;
    i2cRegAddr = 0;
}

void handle_I2C_ISR(void)
{
    uint8_t rx;

    if (SSP1STATbits.P)
    {
        state = S_STOPPED;
        i2cBufferIdx = 0;
        
//        if(SSP1STATbits.BF)             // ?
//            rx = SSP1BUF;
//        SSP1CON1bits.SSPOV = 0;         // ?
        return;
    }
    if((SSP1STATbits.S) && (!SSP1STATbits.BF)){
        //(Re)Start detected, no buffered data, no ACK/NACK yet, and no STOP
        state = S_STARTED; i2cBufferIdx = 0;
        return;
    };

    switch(state){
          case S_STOPPED:
            if((SSP1STATbits.S) && (!SSP1STATbits.BF)){
                //Start detected, no buffered data, no ACK/NACK yet, and no STOP
                state = S_STARTED;
            } break;

        case S_STARTED:
            if (SSP1STATbits.BF) {//!SSP1STATbits.D_nA
                rx = SSP1BUF;
                if (!SSP1STATbits.R_nW) {           // write (address))
                    state = S_REG_ADDRESS;
                    LATAbits.LATA2 ^= 1;
                }
                else { //SSP1STATbits.R_nW          // read
                    state = S_READ;
                    SSP1BUF = i2cBuffer[i2cRegAddr + i2cBufferIdx];
                    if((i2cRegAddr + i2cBufferIdx) < (I2C_BUFFER_SIZE -1))
                        i2cBufferIdx++;
                    SSP1CON1bits.CKP = 1;
                }
            } break;
            
        case S_REG_ADDRESS:       // error ?
            rx = SSP1BUF;
            i2cRegAddr= rx;
            if(i2cRegAddr > (I2C_BUFFER_SIZE -1)) i2cRegAddr = 0;
            state = S_WRITE;
            break;
            
        case S_WRITE:
            if((SSP1STATbits.S) && (!SSP1STATbits.BF)){ //Restart detected
                state = S_STARTED;
                i2cBufferIdx = 0;
            }
            else{
                i2cBuffer[i2cRegAddr + i2cBufferIdx] = SSP1BUF;
                if((i2cRegAddr + i2cBufferIdx) < (I2C_BUFFER_SIZE -1))
                    i2cBufferIdx++;
            }
            break;

        case S_READ:
            SSP1BUF = i2cBuffer[i2cRegAddr + i2cBufferIdx];
            if((i2cRegAddr + i2cBufferIdx) < (I2C_BUFFER_SIZE -1))
                i2cBufferIdx++;
            SSP1CON1bits.CKP = 1;
            break;
    }
}

void clearI2Cinterrupt(void){ PIR1bits.SSP1IF = 0; }
void enableI2Cinterrupt(void){ PIE1bits.SSP1IE = 1; }
void disableI2Cinterrupt(void){ PIE1bits.SSP1IE = 0; }
