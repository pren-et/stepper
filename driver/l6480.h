/******************************************************************************
 ____  ____  _____ _   _       _____ _____ 
|  _ \|  _ \| ____| \ | |     | ____|_   _|
| |_) | |_) |  _| |  \| |_____|  _|   | |  
|  __/|  _ <| |___| |\  |_____| |___  | |  
|_|   |_| \_\_____|_| \_|     |_____| |_|  
                                           
Driver for Stepper driver L6480 from ST Microelectronics

******************************************************************************/

#ifndef L6480_H
#define L6480_H

#include <stdint.h>

/******************************************************************************
Registers
******************************************************************************/
/*! \typedef
 * \brief Possible access levels for registers.
 */
typedef enum {
    L6480_REG_RW_R,  /** readable only */
    L6480_REG_RW_WH, /** writable when outputs in high impedance */
    L6480_REG_RW_WS, /** writable when motor is stopped */
    L6480_REG_RW_WR /** always writable */
} l6480_reg_rw_t;

/*! \typedef
 * \brief Register ABS_POS
 */
typedef union {
    struct {
        uint32_t data   : 22;
        uint32_t unused :  2;
    } raw;
} l6480_reg_abs_pos_t;
#define L6480_REG_ABS_POS_ADDR  0x01
#define L6480_REG_ABS_POS_LEN   sizeof(l6480_reg_abs_pos_t)
#define L6480_REG_ABS_POS_RW    L6480_REG_RW_WS

/*! \typedef
 * \brief Register EL_POS
 */
typedef union {
    struct {
        uint16_t data   : 9;
        uint16_t unused : 7;
    } raw;
    struct {
        uint8_t microstep   : 7;
        uint8_t step        : 2;
        uint8_t unused      : 7;
    } reg;
} l6480_reg_el_pos_t;
#define L6480_REG_EL_POS_ADDR   0x02
#define L6480_REG_EL_POS_LEN    sizeof(l6480_reg_el_pos_t)
#define L6480_REG_EL_POS_RW     L6480_REG_RW_WS

/*! \typedef
 * \brief Register MARK
 */
typedef union {
    struct {
        uint32_t data   : 22;
        uint32_t unused :  2;
    } raw;
} l6480_reg_mark_t;
#define L6480_REG_MARK_ADDR 0x03
#define L6480_REG_MARK_LEN  sizeof(l6480_reg_mark_t)
#define L6480_REG_MARK_RW   L6480_REG_RW_WR

/*! \typedef
 * \brief Register SPEED
 */
typedef union {
    struct {
        uint32_t data   : 20;
        uint32_t unused :  4;
    } raw;
} l6480_reg_speed_t;
#define L6480_REG_SPEED_ADDR    0x04
#define L6480_REG_SPEED_LEN     sizeof(l6480_reg_speed_t)
#define L6480_REG_SPEED_RW      L6480_REG_RW_R

/*! \typedef
 * \brief Register ACC
 */
typedef union {
    struct {
        uint16_t data   : 12;
        uint16_t unused :  4;
    } raw;
} l6480_reg_acc_t;
#define L6480_REG_ACC_ADDR  0x05
#define L6480_REG_ACC_LEN   sizeof(l6480_reg_acc_t)
#define L6480_REG_ACC_RW    L6480_REG_RW_WS

/*! \typedef
 * \brief Register DEC
 */
typedef union {
    struct {
        uint16_t data   : 12;
        uint16_t unused :  4;
    } raw;
} l6480_reg_dec_t;
#define L6480_REG_DEC_ADDR  0x06
#define L6480_REG_DEC_LEN   sizeof(l6480_reg_dec_t)
#define L6480_REG_DEC_RW    L6480_REG_RW_WS

/*! \typedef
 * \brief Register MAX_SPEED
 */
typedef union {
    struct {
        uint16_t data   : 10;
        uint16_t unused :  6;
    } raw;
} l6480_reg_max_speed_t;
#define L6480_REG_MAX_SPEED_ADDR    0x07
#define L6480_REG_MAX_SPEED_LEN     sizeof(l6480_reg_max_speed_t)
#define L6480_REG_MAX_SPEED_RW      L6480_REG_RW_WR

/*! \typedef
 * \brief Register MIN_SPEED
 */
typedef union {
    struct {
        uint16_t data   : 13;
        uint16_t unused :  3;
    } raw;
    struct {
        uint16_t min_speed  : 12;
        uint16_t lspd_opt   :  1;
        uint16_t unused     :  3;
    } reg;
} l6480_reg_min_speed_t;
#define L6480_REG_MIN_SPEED_ADDR    0x08
#define L6480_REG_MIN_SPEED_LEN     sizeof(l6480_reg_min_speed_t)
#define L6480_REG_MIN_SPEED_RW      L6480_REG_RW_WS

/*! \typedef
 * \brief Register FS_SPD
 */
typedef union {
    struct {
        uint16_t data   : 12;
        uint16_t unused :  4;
    } raw;
    struct {
        uint16_t min_speed  : 11;
        uint16_t lspd_opt   :  1;
        uint16_t unused     :  4;
    } reg;
} l6480_reg_fs_spd_t;
#define L6480_REG_FS_SPD_ADDR    0x15
#define L6480_REG_FS_SPD_LEN     sizeof(l6480_reg_fs_spd_t)
#define L6480_REG_FS_SPD_RW      L6480_REG_RW_WR

/*! \typedef
 * \brief Register KVAL_HOLD
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_hold_t;
#define L6480_REG_KVAL_HOLD_ADDR    0x09
#define L6480_REG_KVAL_HOLD_LEN     sizeof(l6480_reg_kval_hold_t)
#define L6480_REG_KVAL_HOLD_RW      L6480_REG_RW_WR

/*! \typedef
 * \brief Register KVAL_RUN
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_run_t;
#define L6480_REG_KVAL_RUN_ADDR     0x0A
#define L6480_REG_KVAL_RUN_LEN      sizeof(l6480_reg_kval_run_t)
#define L6480_REG_KVAL_RUN_RW       L6480_REG_RW_WR

/*! \typedef
 * \brief Register KVAL_ACC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_acc_t;
#define L6480_REG_KVAL_ACC_ADDR     0x0B
#define L6480_REG_KVAL_ACC_LEN      sizeof(l6480_reg_kval_acc_t)
#define L6480_REG_KVAL_ACC_RW       L6480_REG_RW_WR

/*! \typedef
 * \brief Register KVAL_DEC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_dec_t;
#define L6480_REG_KVAL_DEC_ADDR     0x0C
#define L6480_REG_KVAL_DEC_LEN      sizeof(l6480_reg_kval_dec_t)
#define L6480_REG_KVAL_DEC_RW       L6480_REG_RW_WR

/*! \typedef
 * \brief Register INT_SPEED
 */
typedef union {
    struct {
        uint16_t data   : 14;
        uint16_t unused :  2;
    } raw;
} l6480_reg_int_speed_t;
#define L6480_REG_INT_SPEED_ADDR    0x0D
#define L6480_REG_INT_SPEED_LEN     sizeof(l6480_reg_int_speed_t)
#define L6480_REG_INT_SPEED_RW      L6480_REG_RW_WH

/*! \typedef
 * \brief Register ST_SLP
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_st_slp_t;
#define L6480_REG_ST_SLP_ADDR   0x0E
#define L6480_REG_ST_SLP_LEN    sizeof(l6480_reg_st_slp_t)
#define L6480_REG_ST_SLP_RW     L6480_REG_RW_WH

/*! \typedef
 * \brief Register FN_SLP_ACC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_fn_slp_acc_t;
#define L6480_REG_FN_SLP_ACC_ADDR   0x0F
#define L6480_REG_FN_SLP_ACC_LEN    sizeof(l6480_reg_fn_slp_acc_t)
#define L6480_REG_FN_SLP_ACC_RW     L6480_REG_RW_WH

/*! \typedef
 * \brief Register FN_SLP_DEC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_fn_slp_dec_t;
#define L6480_REG_FN_SLP_DEC_ADDR   0x10
#define L6480_REG_FN_SLP_DEC_LEN    sizeof(l6480_reg_fn_slp_dec_t)
#define L6480_REG_FN_SLP_DEC_RW     L6480_REG_RW_WH

/*! \typedef
 * \brief Register K_THERM
 */
typedef union {
    struct {
        uint8_t data   :  4;
        uint8_t unused :  4;
    } raw;
} l6480_reg_k_therm_t;
#define L6480_REG_K_THERM_ADDR  0x11
#define L6480_REG_K_THERM_LEN   sizeof(l6480_reg_k_therm_t)
#define L6480_REG_K_THERM_RW    L6480_REG_RW_WR

/*! \typedef
 * \brief Register ADC_OUT
 */
typedef union {
    struct {
        uint8_t data   :  5;
        uint8_t unused :  3;
    } raw;
} l6480_reg_adc_out_t;
#define L6480_REG_ADC_OUT_ADDR  0x12
#define L6480_REG_ADC_OUT_LEN   sizeof(l6480_reg_adc_out_t)
#define L6480_REG_ADC_OUT_RW    L6480_REG_RW_R

/*! \typedef
 * \brief Register OCD_TH
 */
typedef union {
    struct {
        uint8_t data   :  5;
        uint8_t unused :  3;
    } raw;
} l6480_reg_ocd_th_t;
#define L6480_REG_OCD_TH_ADDR   0x13
#define L6480_REG_OCD_TH_LEN    sizeof(l6480_reg_ocd_th_t)
#define L6480_REG_OCD_TH_RW     L6480_REG_RW_WR

/*! \typedef
 * \brief Register STALL_TH
 */
typedef union {
    struct {
        uint16_t data   :  5;
        uint16_t unused :  3;
    } raw;
} l6480_reg_stall_th_t;
#define L6480_REG_STALL_TH_ADDR 0x14
#define L6480_REG_STALL_TH_LEN  sizeof(l6480_reg_stall_th_t)
#define L6480_REG_STALL_TH_RW   L6480_REG_RW_WR

/*! \typedef
 * \brief Register STEP_MODE
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
    struct {
        uint8_t step_sel    :  3;
        uint8_t null        :  1;
        uint8_t sync_sel    :  3;
        uint8_t sync_en     :  1;
    } reg;
} l6480_reg_step_mode_t;
#define L6480_REG_STEP_MODE_ADDR    0x16
#define L6480_REG_STEP_MODE_LEN     sizeof(l6480_reg_step_mode_t)
#define L6480_REG_STEP_MODE_RW      L6480_REG_RW_WH

/*! \typedef
 * \brief Register ALARM_EN
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
    struct {
        uint8_t overcurrent     :  1;
        uint8_t therm_shutdown  :  1;
        uint8_t therm_warning   :  1;
        uint8_t uvlo            :  1;
        uint8_t adc_uvlo        :  1;
        uint8_t stall_det       :  1;
        uint8_t switch_on       :  1;
        uint8_t cmd_error       :  1;
    } reg;
} l6480_reg_alarm_en_t;
#define L6480_REG_ALARM_EN_ADDR    0x17
#define L6480_REG_ALARM_EN_LEN     sizeof(l6480_reg_alarm_en_t)
#define L6480_REG_ALARM_EN_RW      L6480_REG_RW_WS

/*! \typedef
 * \brief Register GATECFG1
 */
typedef union {
    struct {
        uint16_t data   : 12;
        uint16_t unused :  4;
    } raw;
    struct {
        uint16_t tcc    :  5;
        uint16_t igate  :  5;
        uint16_t tboost :  5;
        uint16_t wd_en  :  5;
        uint16_t unused :  4;
    } reg;
} l6480_reg_gatecfg1_t;
#define L6480_REG_GATECFG1_ADDR    0x18
#define L6480_REG_GATECFG1_LEN     sizeof(l6480_reg_gatecfg1_t)
#define L6480_REG_GATECFG1_RW      L6480_REG_RW_WH

/*! \typedef
 * \brief Register GATECFG2
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
    struct {
        uint8_t tdt     :  5;
        uint8_t tblank  :  3;
    } reg;
} l6480_reg_gatecfg2_t;
#define L6480_REG_GATECFG2_ADDR    0x19
#define L6480_REG_GATECFG2_LEN     sizeof(l6480_reg_gatecfg2_t)
#define L6480_REG_GATECFG2_RW      L6480_REG_RW_WH

/*! \typedef
 * \brief Register CONFIG
 */
typedef union {
    struct {
        uint16_t data;
    } raw;
    struct {
        uint16_t osc_sel    :  3;
        uint16_t ext_clk    :  1;
        uint16_t sw_mode    :  1;
        uint16_t en_vscomp  :  1;
        uint16_t reserved   :  1;
        uint16_t oc_sd      :  1;
        uint16_t uvloval    :  1;
        uint16_t vccval     :  1;
        uint16_t f_pwm_dec  :  3;
        uint16_t f_pwm_int  :  3;
    } reg;
} l6480_reg_config_t;
#define L6480_REG_CONFIG_ADDR    0x1A
#define L6480_REG_CONFIG_LEN     sizeof(l6480_reg_config_t)
#define L6480_REG_CONFIG_RW      L6480_REG_RW_WH

/*! \typedef
 * \brief Register STATUS
 */
typedef union {
    struct {
        uint16_t data;
    } raw;
    struct {
        uint16_t hiz            :  1;
        uint16_t busy           :  1;
        uint16_t sw_f           :  1;
        uint16_t sw_evn         :  1;
        uint16_t dir            :  1;
        uint16_t mot_status     :  2;
        uint16_t cmd_error      :  1;
        uint16_t stck_mod       :  1;
        uint16_t uvlo           :  1;
        uint16_t uvlo_adc       :  1;
        uint16_t th_status      :  2;
        uint16_t ocd            :  1;
        uint16_t step_loss_a    :  1;
        uint16_t step_loss_b    :  1;
    } reg;
} l6480_reg_status_t;
#define L6480_REG_STATUS_ADDR    0x1B
#define L6480_REG_STATUS_LEN     sizeof(l6480_reg_status_t)
#define L6480_REG_STATUS_RW      L6480_REG_RW_R

/*! \typedef
 * \brief L6480 Registers
 */
typedef struct {
    l6480_reg_abs_pos_t     abs_pos;
    l6480_reg_el_pos_t      el_pos;
    l6480_reg_mark_t        mark;
    l6480_reg_speed_t       speed;
    l6480_reg_acc_t         acc;
    l6480_reg_dec_t         dec;
    l6480_reg_max_speed_t   max_speed;
    l6480_reg_min_speed_t   min_speed;
    l6480_reg_fs_spd_t      fs_spd;
    l6480_reg_kval_hold_t   kval_hold;
    l6480_reg_kval_run_t    kval_run;
    l6480_reg_kval_acc_t    kval_acc;
    l6480_reg_kval_dec_t    kval_dec;
    l6480_reg_int_speed_t   int_speed;
    l6480_reg_st_slp_t      st_slp;
    l6480_reg_fn_slp_acc_t  fn_slp_acc;
    l6480_reg_fn_slp_dec_t  fn_slp_dec;
    l6480_reg_k_therm_t     k_therm;
    l6480_reg_adc_out_t     adc_out;
    l6480_reg_ocd_th_t      ocd_th;
    l6480_reg_stall_th_t    stall_th;
    l6480_reg_step_mode_t   step_mode;
    l6480_reg_alarm_en_t    alarm_en;
    l6480_reg_gatecfg1_t    gatecfg1;
    l6480_reg_gatecfg2_t    gatecfg2;
    l6480_reg_config_t      config;
    l6480_reg_status_t      status;
} l6480_reg_t;

/*******************************************************************************
Commands
*******************************************************************************/

/*! 
 * \brief Command NOP
 */
#define L6480_CMD_NOP                       0x00
#define L6480_CMD_NOP_LEN                   1
#define L6480_CMD_NOP_READ                  0

/*!
 * \brief Command SetParam(PARAM, VALUE)
 */
#define L6480_CMD_SETPARAM(reg)             (0x00 | L6480_REG_##reg##_ADDR)
#define L6480_CMD_SETPARAM_LEN(reg)         (1 + L6480_REG_##reg##_LEN)
#define L6480_CMD_SETPARAM_READ(reg)        0

/*!
 * \brief Command GetParam(PARAM, VALUE)
 */
#define L6480_CMD_GETPARAM(reg)             (0x20 | L6480_REG_##reg##_ADDR)
#define L6480_CMD_GETPARAM_LEN(reg)         (1 + L6480_REG_##reg##_LEN)
#define L6480_CMD_GETPARAM_READ(reg)        1

/*!
 * \brief Command Run(DIR, SPD)
 */
#define L6480_CMD_RUN(dir)                  (0x50 | (dir?0x01:0x00))
#define L6480_CMD_RUN_LEN(dir)              4
#define L6480_CMD_RUN_READ(dir)             0

/*!
 * \brief Command StepClock(DIR)
 */
#define L6480_CMD_STEPCLOCK(dir)            (0x58 | (dir?0x01:0x00))
#define L6480_CMD_STEPCLOCK_LEN(dir)        1
#define L6480_CMD_STEPCLOCK_READ(dir)       0

/*!
 * \brief Command Move(DIR, N_STEP)
 */
#define L6480_CMD_MOVE(dir)                 (0x40 | (dir?0x01:0x00))
#define L6480_CMD_MOVE_LEN(dir)             4
#define L6480_CMD_MOVE_READ(dir)            0

/*!
 * \brief Command GoTo(ABS_POS)
 */
#define L6480_CMD_GOTO                      0x60
#define L6480_CMD_GOTO_LEN                  4
#define L6480_CMD_GOTO_READ                 0

/*!
 * \brief Command GoTo_DIR(DIR, ABS_POS)
 */
#define L6480_CMD_GOTO_DIR(dir)             (0x68 | (dir?0x01:0x00))
#define L6480_CMD_GOTO_DIR_LEN(dir)         4
#define L6480_CMD_GOTO_DIR_READ(dir)        0

/*!
 * \brief Command GoUntil(ACT, DIR, SPD)
 */
#define L6480_CMD_GOUNTIL(act, dir)         (0x82 | (act?0x08:0x00) | (dir?0x01:0x00))
#define L6480_CMD_GOUNTIL_LEN(act, dir)     4
#define L6480_CMD_GOUNTIL_READ(act, dir)    0

/*!
 * \brief Command ReleaseSW(act, dir)
 */
#define L6480_CMD_RELEASESW(act, dir)       (0x92 | (act?0x08:0x00) | (dir?0x01:0x00))
#define L6480_CMD_RELEASESW_LEN(act, dir)   1
#define L6480_CMD_RELEASESW_READ(act, dir)  0

/*!
 * \brief Command GoHome
 */
#define L6480_CMD_GOHOME                    0x70
#define L6480_CMD_GOHOME_LEN                1
#define L6480_CMD_GOHOME_READ               0

/*!
 * \brief Command GoMark
 */
#define L6480_CMD_GOMARK                    0x74
#define L6480_CMD_GOMARK_LEN                1
#define L6480_CMD_GOMARK_READ               0

/*!
 * \brief Command ResetPos
 */
#define L6480_CMD_RESETPOS                  0xD8
#define L6480_CMD_RESETPOS_LEN              1
#define L6480_CMD_RESETPOS_READ             0

/*!
 * \brief Command ResetDevice
 */
#define L6480_CMD_RESETDEVICE               0xC0
#define L6480_CMD_RESETDEVICE_LEN           1
#define L6480_CMD_RESETDevice_READ          0

/*!
 * \brief Command SoftStop
 */
#define L6480_CMD_SOFTSTOP                  0xB0
#define L6480_CMD_SOFTSTOP_LEN              1
#define L6480_CMD_SOTFSTOP_READ             0

/*!
 * \brief Command HardStop
 */
#define L6480_CMD_HARDSTOP                  0xB8
#define L6480_CMD_HARDSTOP_LEN              1
#define L6480_CMD_HARDSTOP_READ             0

/*!
 * \brief Command SoftHiZ
 */
#define L6480_CMD_SOFTHIZ                   0xA0
#define L6480_CMD_SOFTHIZ_LEN               1
#define L6480_CMD_SOFTHIZ_READ              0

/*!
 * \brief Command HardHiZ
 */
#define L6480_CMD_HARDHIZ                   0xA8
#define L6480_CMD_HARDHIZ_LEN               1
#define L6480_CMD_HARDHIZ_READ              0

/*!
 * \brief Command GetStatus
 */
#define L6480_CMD_GETSTATUS                 0xD0
#define L6480_CMD_GETSTATUS_LEN             3
#define L6480_CMD_GETSTATUS_READ            1

#endif /* L6480_H */
