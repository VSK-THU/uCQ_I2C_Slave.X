/*
 * File:   uCQ_i2c_slave_main.c
 * Author: vschilli
 *
 * Created on July 12, 2024, 12:31 PM
 */


#include "i2c_device.h"
#include "i2c_intr.h"
#include "global_def.h"
#include "LCD/GLCDnokia.h"
#include "uCQuick/uCQ_2018.h"

extern const char hsulmLogo47x5[];

void main(void) {
       //Run at 4MHz for 100kHz I2C
    OSCCONbits.IRCF = IRCF_4MHZ;

    GLCD_Init();
    GLCDputrbm_XY(5,47, &hsulmLogo47x5[0], 0, 18);
    GLCD_TextOut(5,0, "Hochschule Ulm");
    
    __delay_ms(2000); GLCD_Clear();
   
    GLCD_Text2Out(0,3,"I2C");
    GLCD_Text2Out(1,2,"SLAVE");
    
    
    //Init I2C for Communication
    initI2C();

    //Init FSM
    init_I2C_FSM();

    //Enable Interrupts
    enableInterrupts();

    /*When the 1st I2C activity occurs, it will enter while(1). When the STOP
     event occurs in I2C, the STOP bit will be set, which will enable power
     saving sleep all the time. */

//VSK    SLEEP();
    __asm("NOP");

    while (1)
    {
        //I2C Idle
        if (I2C_IS_NOT_ACTIVE)
        {
//VSK            SLEEP();
            __asm("NOP");
        }
    }
    return;
}
