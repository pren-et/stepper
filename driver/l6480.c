/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file l6480.c
 * \brief Driver for Stepper driver L6480 from ST Microelectronics
 * \author pren-et
 * 
 */

#include "l6480.h"

/* Definition of necessary functions provided by a SPI module later */
void spi_write(uint8_t *data) { return; }
void spi_read(uint8_t *data) { return; }

void l6480_init(void) {
    /*! test orientation of bitfields */
    test_bitfield_t test_bitfield;      /*!< testvariable */
    test_bitfield.bitfield.low = 0x01;  /*!< write testvalue to lower nibble */
    if (test_bitfield.byte != 0x01) {   /*!< test if lower nibble has been written */
        while (1) {                     /*!< loop to stop executing if wrong order */
            /* Hey Programmer */
            /* It seems that your compiler uses a */
            /* different order for bitfields than mine. */
            /* If you still want to use this library, */
            /* change ,if possible, the order of bitfields in */
            /* your compiler or in this library! */
        }
    }
    
    return;
}

/* Funtion for sending a command */
void l6480_send_cmd(uint8_t cmd, uint8_t len, uint8_t read, uint8_t *data) {
    /*! local variables */
    uint8_t i;          /*!< variable to count number of sent bits */
    spi_write(&cmd);    /*!< send command */
    if (read) {         /*!< check if reading data is needed */
        for (i = 0; i < (len - 1); i++) {
            spi_read(data++);   /*!< read data */
        }
    } else {
        for (i = 0; i < (len - 1); i++) {
            spi_write(data++);  /*!< write data */
        }
    }
}

/* Functions for reading and writing registers */
int32_t l6480_get_abs_pos(void) {
    /*! local variables */
    l6480_reg_abs_pos_t reg;

    /*! read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(ABS_POS), 
        L6480_CMD_GETPARAM_LEN(ABS_POS), 
        L6480_CMD_GETPARAM_READ(ABS_POS), 
        reg.array);

    /*! return data */
    return reg.raw.data;
}

void l6480_set_abs_pos(int32_t pos) {
    /*! local variables */
    l6480_reg_abs_pos_t reg;

    /*! input value limitation */
    if (pos >= L6480_REG_ABS_POS_MAX) {
        pos  = L6480_REG_ABS_POS_MAX;
    }
    if (pos <= L6480_REG_ABS_POS_MIN) {
        pos  = L6480_REG_ABS_POS_MIN;
    }

    /*! prepare data local */
    reg.raw.data = pos;

    /*! send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(ABS_POS), 
        L6480_CMD_SETPARAM_LEN(ABS_POS), 
        L6480_CMD_SETPARAM_READ(ABS_POS), 
        reg.array);

    return;
}

int16_t l6480_get_el_pos(void) {
    /*! local variables */
    l6480_reg_el_pos_t reg;

    /*! read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(EL_POS), 
        L6480_CMD_GETPARAM_LEN(EL_POS), 
        L6480_CMD_GETPARAM_READ(EL_POS), 
        reg.array);

    /*! return data */
    return reg.raw.data;
}

void l6480_set_el_pos(uint8_t fullstep, uint8_t microstep) {
    /*! local variables */
    l6480_reg_el_pos_t reg;

    /*! input value limitation */
    if (fullstep >= 3) {
        fullstep  = 3;
    }
    if (microstep >= 127) {
        microstep  = 127;
    }

    /*! prepare data local */
    reg.reg.step = fullstep;
    reg.reg.microstep = microstep;

    /*! send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(EL_POS), 
        L6480_CMD_SETPARAM_LEN(EL_POS), 
        L6480_CMD_SETPARAM_READ(EL_POS), 
        reg.array);
    return;
}

int32_t l6480_get_mark(void) {
    /*! local variables */
    l6480_reg_mark_t reg;

    /*! read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(MARK), 
        L6480_CMD_GETPARAM_LEN(MARK), 
        L6480_CMD_GETPARAM_READ(MARK), 
        reg.array);

    /*! return data */
    return reg.raw.data;
}

void l6480_set_mark(int32_t mark) {
    /*! local variables */
    l6480_reg_abs_pos_t reg;

    /*! input value limitation */
    if (mark >= L6480_REG_MARK_MAX) {
        mark  = L6480_REG_MARK_MAX;
    }
    if (mark <= L6480_REG_MARK_MIN) {
        mark  = L6480_REG_MARK_MIN;
    }

    /*! prepare data local */
    reg.raw.data = mark;

    /*! send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(MARK), 
        L6480_CMD_SETPARAM_LEN(MARK), 
        L6480_CMD_SETPARAM_READ(MARK), 
        reg.array);

    return;
}

int32_t l6480_get_speed(void) {
    /*! local variables */
    l6480_reg_speed_t reg;

    /*! read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(SPEED), 
        L6480_CMD_GETPARAM_LEN(SPEED), 
        L6480_CMD_GETPARAM_READ(SPEED), 
        reg.array);

    /*! return data */
    return reg.raw.data;
}

int32_t l6480_get_speed_millisteps_s(void) {
    /*! local variables */
    int32_t speed;

    /*! read current speed from device */
    speed = l6480_get_speed();

    /*! calculate speed in millisteps per second
        \f[
            \text{speed}~[\si{step\per\second}] 
            = \frac{\text{SPEED} \cdot 2^{-28}}{250~[\si{\nano\second}]}
        \f]
        \f[
            \text{speed}~[\si{\milli step\per\second}] 
            = \frac{\text{SPEED} \cdot 1000 \cdot 2^{-28}}{250~[\si{\nano\second}]} 
            = \text{SPEED} \cdot 2^{-26} \cdot 10^{9} 
            \approx 14.90
        \f]
    */
    speed = speed * 149 / 10;

    /*! return speed */
    return speed;
}

