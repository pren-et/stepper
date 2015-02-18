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
/*! \fn spi_write(uint8_t *data)
 *  \todo Define in SPI Module
 */
void spi_write(uint8_t *data) { return; }
/*! \fn spi_read(uint8_t *data)
 *  \todo Define in SPI Module
 */
void spi_read(uint8_t *data) { return; }

void l6480_init(void) {
    /* test orientation of bitfields */
    test_bitfield_t test_bitfield;      /* testvariable */
    test_bitfield.bitfield.low = 0x01;  /* write testvalue to lower nibble */
    if (test_bitfield.byte != 0x01) {   /* test if lower nibble has been written */
        while (1) {                     /* loop to stop executing if wrong order */
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

void l6480_send_cmd(uint8_t cmd, uint8_t len, uint8_t read, uint8_t *data) {
    /* local variables */
    uint8_t i;          /* variable to count number of sent bits */
    spi_write(&cmd);    /* send command */
    if (read) {         /* check if reading data is needed */
        for (i = 0; i < (len - 1); i++) {
            spi_read(data++);   /* read data */
        }
    } else {
        for (i = 0; i < (len - 1); i++) {
            spi_write(data++);  /* write data */
        }
    }
}

int32_t l6480_get_abs_pos(void) {
    /* local variables */
    l6480_reg_abs_pos_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(ABS_POS), 
        L6480_CMD_GETPARAM_LEN(ABS_POS), 
        L6480_CMD_GETPARAM_READ(ABS_POS), 
        reg.array);

    /* return data */
    return reg.raw.data;
}

void l6480_set_abs_pos(int32_t pos) {
    /* local variables */
    l6480_reg_abs_pos_t reg;

    /* input value limitation */
    if (pos >= L6480_REG_ABS_POS_MAX) {
        pos  = L6480_REG_ABS_POS_MAX;
    }
    if (pos <= L6480_REG_ABS_POS_MIN) {
        pos  = L6480_REG_ABS_POS_MIN;
    }

    /* prepare data local */
    reg.raw.data = pos;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(ABS_POS), 
        L6480_CMD_SETPARAM_LEN(ABS_POS), 
        L6480_CMD_SETPARAM_READ(ABS_POS), 
        reg.array);

    return;
}

int16_t l6480_get_el_pos(void) {
    /* local variables */
    l6480_reg_el_pos_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(EL_POS), 
        L6480_CMD_GETPARAM_LEN(EL_POS), 
        L6480_CMD_GETPARAM_READ(EL_POS), 
        reg.array);

    /* return data */
    return reg.raw.data;
}

void l6480_set_el_pos(uint8_t fullstep, uint8_t microstep) {
    /* local variables */
    l6480_reg_el_pos_t reg;

    /* input value limitation */
    if (fullstep >= 3) {
        fullstep  = 3;
    }
    if (microstep >= 127) {
        microstep  = 127;
    }

    /* prepare data local */
    reg.reg.step = fullstep;
    reg.reg.microstep = microstep;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(EL_POS), 
        L6480_CMD_SETPARAM_LEN(EL_POS), 
        L6480_CMD_SETPARAM_READ(EL_POS), 
        reg.array);
    return;
}

int32_t l6480_get_mark(void) {
    /* local variables */
    l6480_reg_mark_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(MARK), 
        L6480_CMD_GETPARAM_LEN(MARK), 
        L6480_CMD_GETPARAM_READ(MARK), 
        reg.array);

    /* return data */
    return reg.raw.data;
}

void l6480_set_mark(int32_t mark) {
    /* local variables */
    l6480_reg_mark_t reg;

    /* input value limitation */
    if (mark >= L6480_REG_MARK_MAX) {
        mark  = L6480_REG_MARK_MAX;
    }
    if (mark <= L6480_REG_MARK_MIN) {
        mark  = L6480_REG_MARK_MIN;
    }

    /* prepare data local */
    reg.raw.data = mark;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(MARK), 
        L6480_CMD_SETPARAM_LEN(MARK), 
        L6480_CMD_SETPARAM_READ(MARK), 
        reg.array);

    return;
}

int32_t l6480_get_speed(void) {
    /* local variables */
    l6480_reg_speed_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(SPEED), 
        L6480_CMD_GETPARAM_LEN(SPEED), 
        L6480_CMD_GETPARAM_READ(SPEED), 
        reg.array);

    /* return data */
    return reg.raw.data;
}

int32_t l6480_get_speed_millisteps_s(void) {
    /* local variables */
    int32_t speed;

    /* read current speed from device */
    speed = l6480_get_speed();

    /*! calculate speed in millisteps per second
        \f[
            \text{speed}~[\si{step\per\second}] 
            = \frac{\text{SPEED} \cdot 2^{-28}}{250~[\si{\second}]}
        \f]
        \f[
            \text{speed}~[\si{\milli step\per\second}] 
            = \frac{\text{SPEED} \cdot 1000 \cdot 2^{-28}}{250~[\si{\second}]} 
            = \text{SPEED} \cdot 2^{-26} \cdot 10^{9} 
            \approx \text{MIN\_SPEED} \cdot 14.90
        \f]
    */
    speed = speed * 149 / 10;

    /* return speed */
    return speed;
}

uint16_t l6480_get_acc(void) {
    /* local variables */
    l6480_reg_acc_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(ACC), 
        L6480_CMD_GETPARAM_LEN(ACC), 
        L6480_CMD_GETPARAM_READ(ACC), 
        reg.array);

    /* return data */
    return reg.raw.data;
}

uint16_t l6480_get_acc_steps_ss(void) {
    /* local variables */
    uint32_t acc;

    /* read current acc from device */
    acc = l6480_get_acc();

    /*! calculate acc in steps per second^2
        \f[
            \text{acc}~[\si{step\per\second^2}]
            = \frac{\text{ACC} \cdot 2^{-40}}{\left(250~[\si{\second}] \cdot 10^{-9}\right)^2}
            = \text{ACC} \cdot 2^{-36} \cdot 10^{12}
            \approx \text{MIN\_SPEED} \cdot 14.55
        \f]
    */
    acc = acc * 1455 / 100;

    /* return acc */
    return (uint16_t) acc;
}

void l6480_set_acc(uint16_t acc) {
    /* local variables */
    l6480_reg_acc_t reg;

    /* input value limitation */
    if (acc >= L6480_REG_ACC_MAX) {
        acc  = L6480_REG_ACC_MAX;
    }

    /* prepare data local */
    reg.raw.data = acc;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(ACC), 
        L6480_CMD_SETPARAM_LEN(ACC), 
        L6480_CMD_SETPARAM_READ(ACC), 
        reg.array);

    return;
}

void l6480_set_acc_steps_ss(uint16_t acc) {
    /* local variables */

    /*! Calculate acc register value
        \f[
            \text{acc}~[\si{step\per\second^2}]
            = \frac{\text{ACC} \cdot 2^{-40}}{\left(250~[\si{\second}] \cdot 10^{-9}\right)^2}
            = \text{ACC} \cdot 2^{-36} \cdot 10^{12}
            \approx \text{MIN\_SPEED} \cdot 14.55
        \f]
    */
    acc = (uint16_t) ((uint32_t) acc * 100 / 1455);

    /* send data to device */
    l6480_set_acc(acc);

    return;
}

uint16_t l6480_get_dec(void) {
    /* local variables */
    l6480_reg_dec_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(DEC), 
        L6480_CMD_GETPARAM_LEN(DEC), 
        L6480_CMD_GETPARAM_READ(DEC), 
        reg.array);

    /* return data */
    return reg.raw.data;
}

uint16_t l6480_get_dec_steps_ss(void) {
    /* local variables */
    uint32_t dec;

    /* read current dec from device */
    dec = l6480_get_dec();

    /*! calculate dec in steps per second^2
        \f[
            \text{dec}~[\si{step\per\second^2}]
            = \frac{\text{DEC} \cdot 2^{-40}}{\left(250~[\si{\second}] \cdot 10^{-9}\right)^2}
            = \text{DEC} \cdot 2^{-36} \cdot 10^{12}
            \approx \text{MIN\_SPEED} \cdot 14.55
        \f]
    */
    dec = dec * 1455 / 100;

    /* return dec */
    return (uint16_t) dec;
}

void l6480_set_dec(uint16_t dec) {
    /* local variables */
    l6480_reg_dec_t reg;

    /* input value limitation */
    if (dec >= L6480_REG_DEC_MAX) {
        dec  = L6480_REG_DEC_MAX;
    }

    /* prepare data local */
    reg.raw.data = dec;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(DEC), 
        L6480_CMD_SETPARAM_LEN(DEC), 
        L6480_CMD_SETPARAM_READ(DEC), 
        reg.array);

    return;
}

void l6480_set_dec_steps_ss(uint16_t dec) {
    /* local variables */

    /*! Calculate dec register value
        \f[
            \text{dec}~[\si{step\per\second^2}]
            = \frac{\text{DEC} \cdot 2^{-40}}{\left(250~[\si{\second}] \cdot 10^{-9}\right)^2}
            = \text{DEC} \cdot 2^{-36} \cdot 10^{12}
            \approx \text{MIN\_SPEED} \cdot 14.55
        \f]
    */
    dec = (uint16_t) ((uint32_t) dec * 100 / 1455);

    /* send data to device */
    l6480_set_dec(dec);

    return;
}

uint16_t l6480_get_max_speed(void) {
    /* local variables */
    l6480_reg_max_speed_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(MAX_SPEED), 
        L6480_CMD_GETPARAM_LEN(MAX_SPEED), 
        L6480_CMD_GETPARAM_READ(MAX_SPEED), 
        reg.array);

    /* return data */
    return reg.raw.data;
}

uint16_t l6480_get_max_speed_steps_s(void) {
    /* local variables */
    uint32_t max_speed;

    /* read max_speed from device */
    max_speed = l6480_get_max_speed();

    /*! calculate max_speed in steps per second
        \f[
            \text{max\_speed}~[\si{step\per\second}]
            = \frac{\text{MAX\_SPEED} \cdot 2^{-18}}{250~[\si{\second}] \cdot 10^{-9}}
            = \text{MAX\_SPEED} \cdot 2^{-16} \cdot 10^{6}
            \approx \text{MIN\_SPEED} \cdot 15.259
        \f]
    */
    max_speed = max_speed * 15259 / 1000;

    /* return max_speed */
    return (uint16_t) max_speed;
}

void l6480_set_max_speed(uint16_t max_speed) {
    /* local variables */
    l6480_reg_max_speed_t reg;

    /* input value limitation */
    if (max_speed >= L6480_REG_MAX_SPEED_MAX) {
        max_speed  = L6480_REG_MAX_SPEED_MAX;
    }

    /* prepare data local */
    reg.raw.data = max_speed;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(MAX_SPEED), 
        L6480_CMD_SETPARAM_LEN(MAX_SPEED), 
        L6480_CMD_SETPARAM_READ(MAX_SPEED), 
        reg.array);

    return;
}

void l6480_set_max_speed_steps_s(uint16_t max_speed) {
    /* local variables */

    /*! Calculate max_speed register value
        \f[
            \text{max\_speed}~[\si{step\per\second}]
            = \frac{\text{MAX\_SPEED} \cdot 2^{-18}}{250~[\si{\second}] \cdot 10^{-9}}
            = \text{MAX\_SPEED} \cdot 2^{-16} \cdot 10^{6}
            \approx \text{MIN\_SPEED} \cdot 15.259
        \f]
    */
    max_speed = (uint16_t) ((uint32_t) max_speed * 1000 / 15259);

    /* send data to device */
    l6480_set_max_speed(max_speed);

    return;
}

uint16_t l6480_get_min_speed(void) {
    /* local variables */
    l6480_reg_min_speed_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(MIN_SPEED), 
        L6480_CMD_GETPARAM_LEN(MIN_SPEED), 
        L6480_CMD_GETPARAM_READ(MIN_SPEED), 
        reg.array);

    /* Analyze data */
    if (reg.reg.lspd_opt == 1) {
        reg.reg.min_speed = 0; /* minimum speed zero when low speed optimization on */
    }

    /* return data */
    return reg.reg.min_speed;
}

uint32_t l6480_get_min_speed_millisteps_s(void) {
    /* local variables */
    uint32_t min_speed;

    /* read min_speed from device */
    min_speed = l6480_get_min_speed();

    /*! calculate min_speed in millisteps per second
        \f[
            \text{min\_speed}~[\si{step\per\second}]
            = \frac{\text{MIN\_SPEED} \cdot 2^{-24}}{250~[\si{\second}] \cdot 10^{-9}}
        \f]
        \f[
            \text{min\_speed}~[\si{\milli step\per\second}]
            = \frac{\text{MIN\_SPEED} \cdot 2^{-24} \cdot 10^{3}}{250~[\si{\second}] \cdot 10^{-9}}
            = \text{MIN\_SPEED} \cdot 2^{-22} \cdot 10^{9}
            \approx \text{MIN\_SPEED} \cdot 238.42
        \f]
    */
    min_speed = min_speed * 2384 / 10;

    /* return min_speed */
    return min_speed;
}

uint16_t l6480_get_lspd_opt_speed(void) {
    /* local variables */
    l6480_reg_min_speed_t reg;

    /* read data from device */
    l6480_send_cmd( L6480_CMD_GETPARAM(MIN_SPEED), 
        L6480_CMD_GETPARAM_LEN(MIN_SPEED), 
        L6480_CMD_GETPARAM_READ(MIN_SPEED), 
        reg.array);

    /* Analyze data */
    if (reg.reg.lspd_opt == 0) {
        reg.reg.min_speed = 0; /* low speed optimization threshold zero when low speed optimization off */
    }

    /* return data */
    return reg.reg.min_speed;
}

uint32_t l6480_get_lspd_opt_speed_millisteps_s(void) {
    /* local variables */
    uint32_t min_speed;

    /* read min_speed from device */
    min_speed = l6480_get_min_speed();

    /*! calculate min_speed in millisteps per second
        \f[
            \text{min\_speed}~[\si{step\per\second}]
            = \frac{\text{MIN\_SPEED} \cdot 2^{-24}}{250~[\si{\second}] \cdot 10^{-9}}
        \f]
        \f[
            \text{min\_speed}~[\si{\milli step\per\second}]
            = \frac{\text{MIN\_SPEED} \cdot 2^{-24} \cdot 10^{3}}{250~[\si{\second}] \cdot 10^{-9}}
            = \text{MIN\_SPEED} \cdot 2^{-22} \cdot 10^{9}
            \approx \text{MIN\_SPEED} \cdot 238.42
        \f]
    */
    min_speed = min_speed * 2384 / 10;

    /* return min_speed */
    return min_speed;
}

void l6480_set_min_speed(uint16_t speed) {
    /* local variables */
    l6480_reg_min_speed_t reg;

    /* input value limitation */
    if (speed >= L6480_REG_MIN_SPEED_MAX) {
        speed  = L6480_REG_MIN_SPEED_MAX;
    }

    /* prepare data local */
    reg.reg.min_speed = speed;
    reg.reg.lspd_opt  = 0;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(MIN_SPEED), 
        L6480_CMD_SETPARAM_LEN(MIN_SPEED), 
        L6480_CMD_SETPARAM_READ(MIN_SPEED), 
        reg.array);

    return;
}

void l6480_set_min_speed_millisteps_s(uint32_t speed) {
    /* local variables */

    /*! Calculate max_speed register value
        \f[
            \text{min\_speed}~[\si{\milli step\per\second}]
            = \frac{\text{MIN\_SPEED} \cdot 2^{-24} \cdot 10^{3}}{250~[\si{\second}] \cdot 10^{-9}}
            = \text{MIN\_SPEED} \cdot 2^{-22} \cdot 10^{9}
            \approx \text{MIN\_SPEED} \cdot 238.42
        \f]
    */
    speed = (uint16_t) (speed * 10 / 2384);

    /* send data to device */
    l6480_set_min_speed(speed);

    return;
}

void l6480_set_lspd_opt_speed(uint16_t speed) {
    /* local variables */
    l6480_reg_min_speed_t reg;

    /* input value limitation */
    if (speed >= L6480_REG_MIN_SPEED_MAX) {
        speed  = L6480_REG_MIN_SPEED_MAX;
    }

    /* prepare data local */
    reg.reg.min_speed = speed;
    reg.reg.lspd_opt  = 1;

    /* send data to device */
    l6480_send_cmd( L6480_CMD_SETPARAM(MIN_SPEED), 
        L6480_CMD_SETPARAM_LEN(MIN_SPEED), 
        L6480_CMD_SETPARAM_READ(MIN_SPEED), 
        reg.array);

    return;
}

void l6480_set_lspd_opt_speed_millisteps_s(uint32_t speed) {
    /* local variables */

    /*! Calculate max_speed register value
        \f[
            \text{min\_speed}~[\si{\milli step\per\second}]
            = \frac{\text{MIN\_SPEED} \cdot 2^{-24} \cdot 10^{3}}{250~[\si{\second}] \cdot 10^{-9}}
            = \text{MIN\_SPEED} \cdot 2^{-22} \cdot 10^{9}
            \approx \text{MIN\_SPEED} \cdot 238.42
        \f]
    */
    speed = (uint16_t) (speed * 10 / 2384);

    /* send data to device */
    l6480_set_lspd_opt_speed(speed);

    return;
}

uint8_t l6480_get_boost_mode(void) {
    /*! \todo Implement function */
}

void l6480_set_boost_mode_on(void) {
    /*! \todo Implement function */
}

void l6480_set_boost_mode_off(void) {
    /*! \todo Implement function */
}

uint16_t l6480_get_fs_spd(void) {
    /*! \todo Implement function */
}

uint16_t l6480_get_fs_spd_steps_s(void) {
    /*! \todo Implement function */
}

void l6480_set_fs_spd(uint16_t speed) {
    /*! \todo Implement function */
}

void l6480_set_fs_spd_steps_s(uint16_t speed) {
    /*! \todo Implement function */
}

uint8_t l6480_get_kval_hold(void) {
    /*! \todo Implement function */
}

void l6480_set_kval_hold(uint8_t value) {
    /*! \todo Implement function */
}

uint8_t l6480_get_kval_run(void) {
    /*! \todo Implement function */
}

void l6480_set_kval_run(uint8_t value) {
    /*! \todo Implement function */
}

uint8_t l6480_get_kval_acc(void) {
    /*! \todo Implement function */
}

void l6480_set_kval_acc(uint8_t value) {
    /*! \todo Implement function */
}

uint8_t l6480_get_kval_dec(void) {
    /*! \todo Implement function */
}

void l6480_set_kval_dec(uint8_t value) {
    /*! \todo Implement function */
}

uint16_t l6480_get_int_speed(void) {
    /*! \todo Implement function */
}

uint32_t l6480_get_int_speed_steps_s(void) {
    /*! \todo Implement function */
}

void l6480_set_int_speed(uint16_t speed) {
    /*! \todo Implement function */
}

void l6480_set_int_speed_steps_s(uint16_t speed) {
    /*! \todo Implement function */
}

uint8_t l6480_get_st_slp(void) {
    /*! \todo Implement function */
}

void l6480_set_st_slp(uint8_t slope) {
    /*! \todo Implement function */
}

uint8_t l6480_get_fn_slp_acc(void) {
    /*! \todo Implement function */
}

void l6480_set_fn_slp_acc(uint8_t slope) {
    /*! \todo Implement function */
}

uint8_t l6480_get_fn_slp_dec(void) {
    /*! \todo Implement function */
}

void l6480_set_fn_slp_dec(uint8_t slope) {
    /*! \todo Implement function */
}

uint8_t l6480_get_k_therm(void) {
    /*! \todo Implement function */
}

uint16_t l6480_get_k_therm_milli(void) {
    /*! \todo Implement function */
}

void l6480_set_k_therm(uint8_t value) {
    /*! \todo Implement function */
}

void l6480_set_k_therm_milli(uint16_t value) {
    /*! \todo Implement function */
}

uint8_t l6480_get_adc_out(void) {
    /*! \todo Implement function */
}

