/*
 * File:   i2c_device.h
 * Author: vschilli
 *
 * Created on July 12, 2024, 12:34 PM
 */
#ifndef I2C_DEVICE_H
#define	I2C_DEVICE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#include <stdint.h>
    /**
     * <B><FONT COLOR=BLUE>void</FONT> initI2C(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function initializes the MSSP module in I2C Device mode.
     *  */
    void initI2C(void);

    /**
     * <B><FONT COLOR=BLUE>void</FONT> setupI2Cpins(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This functions configures the appropriate I/O pins for I2C operation.
     *  */
    void setupI2Cpins(void);

    /**
     * <B><FONT COLOR=BLUE>void</FONT> init_I2C_FSM(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function initializes the I2C state machines which enable proper
     * reception and transmission of I2C traffic.
     *  */
    void init_I2C_FSM(void);

    /**
     * <B><FONT COLOR=BLUE>void</FONT> handle_I2C_ISR(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function handles all I2C related interrupts from the MSSP module.
     * Invoked from the interrupt handler.
     *  */
    void handle_I2C_ISR(void);
        /**
     * <B><FONT COLOR=BLUE>void</FONT> clearI2Cinterrupt(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function clears the I2C interrupt flags.
     *  */
    void clearI2Cinterrupt(void);

    /**
     * <B><FONT COLOR=BLUE>void</FONT> enableI2Cinterrupt(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function enables the I2C interrupt.
     *  */
    void enableI2Cinterrupt(void);

    /**
     * <B><FONT COLOR=BLUE>void</FONT> disableI2Cinterrupt(<FONT COLOR=BLUE>void</FONT>)</B>
     *
     * This function disables the I2C interrupt.
     *  */
    void disableI2Cinterrupt(void);

#define I2C_IS_NOT_ACTIVE SSP1STATbits.P

#endif	/* I2C_DEVICE_H */
