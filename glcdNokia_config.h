/* 
 * File:   GLCDnokia_config.h
 * Author: vschilli
 *
* Created on 01. March 2018, 13:37
 */

#ifndef GLCDNOKIA_CFG_H
#define GLCDNOKIA_CFG_H

#include <xc.h>

#define GLCD_DC     LATAbits.LATA5
#define GLCD_nRES   LATCbits.LATC0
#define GLCD_nCS    LATCbits.LATC1
#define GLCD_CLK    LATCbits.LATC3
#define GLCD_DATA   LATCbits.LATC5

#define GLCD_DC_TRI     TRISAbits.TRISA5
#define GLCD_nRES_TRI   TRISCbits.TRISC0
#define GLCD_CS_TRI     TRISCbits.TRISC1
#define GLCD_CLK_TRI    TRISCbits.TRISC3
#define GLCE_DATA_TRI   TRISCbits.TRISC5

#define GLCD_DLY()
//Nop();

#endif	/* GLCDNOKIA_CFG_H */
