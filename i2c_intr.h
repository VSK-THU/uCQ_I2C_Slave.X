/*
 * File:   i2c_intr.h
 * Author: vschilli
 *
 * Created on July 12, 2024, 12:32 PM
 */

#ifndef I2C_INTR_H
#define	I2C_INTR_H

//#include <stdint.h>
    /**
     * <B><FONT COLOR=BLUE>void __interrupt()</FONT> ISR(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function receives all interrupts and dispatches them to the appropriate
     * handlers.
     *  */
    void __interrupt() ISR(void);

    /**
     * <B><FONT COLOR=BLUE>void</FONT> enableInterrupts(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function enables all global interrupts.
     *  */
    void enableInterrupts(void);

    /**
     * <B><FONT COLOR=BLUE>void</FONT> disableInterrupts(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function disables all global interrupts.
     *  */
    void disableInterrupts(void);

#endif	/* I2C_INTR_H */
