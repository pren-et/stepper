/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file l6480.h
 * \brief Driver for Stepper driver L6480 from ST Microelectronics
 * \author pren-et
 * 
 */

#ifndef L6480_H
#define L6480_H

#include <stdint.h>

/******************************************************************************
Registers
******************************************************************************/
/*! \typedef
 *  \brief Possible access levels for registers.
 */
typedef enum {
    L6480_REG_RW_R,  /*!< readable only */
    L6480_REG_RW_WH, /*!< writable when outputs in high impedance */
    L6480_REG_RW_WS, /*!< writable when motor is stopped */
    L6480_REG_RW_WR  /*!< always writable */
} l6480_reg_rw_t;

/*! \typedef
 *  \brief Register ABS_POS
 */
typedef union {
    struct {
    uint32_t data   : 22;
    uint32_t unused :  2;
    } raw;
} l6480_reg_abs_pos_t;
/*! \name abs_pos
 * @{
 */
#define L6480_REG_ABS_POS_ADDR  0x01
#define L6480_REG_ABS_POS_LEN   sizeof(l6480_reg_abs_pos_t)
#define L6480_REG_ABS_POS_RW    L6480_REG_RW_WS
/*! @} */

/*! \typedef
 *  \brief Register EL_POS
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
/*! \name el_pos
 * @{
 */
#define L6480_REG_EL_POS_ADDR   0x02
#define L6480_REG_EL_POS_LEN    sizeof(l6480_reg_el_pos_t)
#define L6480_REG_EL_POS_RW     L6480_REG_RW_WS
/*! @} */

/*! \typedef
 *  \brief Register MARK
 */
typedef union {
    struct {
        uint32_t data   : 22;
        uint32_t unused :  2;
    } raw;
} l6480_reg_mark_t;
/*! \name mark
 * @{
 */
#define L6480_REG_MARK_ADDR 0x03
#define L6480_REG_MARK_LEN  sizeof(l6480_reg_mark_t)
#define L6480_REG_MARK_RW   L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register SPEED
 */
typedef union {
    struct {
        uint32_t data   : 20;
        uint32_t unused :  4;
    } raw;
} l6480_reg_speed_t;
/*! \name speed
 * @{
 */
#define L6480_REG_SPEED_ADDR    0x04
#define L6480_REG_SPEED_LEN     sizeof(l6480_reg_speed_t)
#define L6480_REG_SPEED_RW      L6480_REG_RW_R
/*! @} */

/*! \typedef
 *  \brief Register ACC
 */
typedef union {
    struct {
        uint16_t data   : 12;
        uint16_t unused :  4;
    } raw;
} l6480_reg_acc_t;
/*! \name acc
 * @{
 */
#define L6480_REG_ACC_ADDR  0x05
#define L6480_REG_ACC_LEN   sizeof(l6480_reg_acc_t)
#define L6480_REG_ACC_RW    L6480_REG_RW_WS
/*! @} */

/*! \typedef
 *  \brief Register DEC
 */
typedef union {
    struct {
        uint16_t data   : 12;
        uint16_t unused :  4;
    } raw;
} l6480_reg_dec_t;
/*! \name dec
 * @{
 */
#define L6480_REG_DEC_ADDR  0x06
#define L6480_REG_DEC_LEN   sizeof(l6480_reg_dec_t)
#define L6480_REG_DEC_RW    L6480_REG_RW_WS
/*! @} */

/*! \typedef
 *  \brief Register MAX_SPEED
 */
typedef union {
    struct {
        uint16_t data   : 10;
        uint16_t unused :  6;
    } raw;
} l6480_reg_max_speed_t;
/*! \name max_speed
 * @{
 */
#define L6480_REG_MAX_SPEED_ADDR    0x07
#define L6480_REG_MAX_SPEED_LEN     sizeof(l6480_reg_max_speed_t)
#define L6480_REG_MAX_SPEED_RW      L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register MIN_SPEED
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
/*! \name min_speed
 * @{
 */
#define L6480_REG_MIN_SPEED_ADDR    0x08
#define L6480_REG_MIN_SPEED_LEN     sizeof(l6480_reg_min_speed_t)
#define L6480_REG_MIN_SPEED_RW      L6480_REG_RW_WS
/*! @} */

/*! \typedef
 *  \brief Register FS_SPD
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
/*! \name fs_spd
 * @{
 */
#define L6480_REG_FS_SPD_ADDR    0x15
#define L6480_REG_FS_SPD_LEN     sizeof(l6480_reg_fs_spd_t)
#define L6480_REG_FS_SPD_RW      L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register KVAL_HOLD
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_hold_t;
/*! \name kval_hold
 * @{
 */
#define L6480_REG_KVAL_HOLD_ADDR    0x09
#define L6480_REG_KVAL_HOLD_LEN     sizeof(l6480_reg_kval_hold_t)
#define L6480_REG_KVAL_HOLD_RW      L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register KVAL_RUN
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_run_t;
/*! \name kval_run
 * @{
 */
#define L6480_REG_KVAL_RUN_ADDR     0x0A
#define L6480_REG_KVAL_RUN_LEN      sizeof(l6480_reg_kval_run_t)
#define L6480_REG_KVAL_RUN_RW       L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register KVAL_ACC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_acc_t;
/*! \name kval_acc
 * @{
 */
#define L6480_REG_KVAL_ACC_ADDR     0x0B
#define L6480_REG_KVAL_ACC_LEN      sizeof(l6480_reg_kval_acc_t)
#define L6480_REG_KVAL_ACC_RW       L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register KVAL_DEC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_kval_dec_t;
/*! \name kval_dec
 * @{
 */
#define L6480_REG_KVAL_DEC_ADDR     0x0C
#define L6480_REG_KVAL_DEC_LEN      sizeof(l6480_reg_kval_dec_t)
#define L6480_REG_KVAL_DEC_RW       L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register INT_SPEED
 */
typedef union {
    struct {
        uint16_t data   : 14;
        uint16_t unused :  2;
    } raw;
} l6480_reg_int_speed_t;
/*! \name int_speed
 * @{
 */
#define L6480_REG_INT_SPEED_ADDR    0x0D
#define L6480_REG_INT_SPEED_LEN     sizeof(l6480_reg_int_speed_t)
#define L6480_REG_INT_SPEED_RW      L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register ST_SLP
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_st_slp_t;
/*! \name st_slp
 * @{
 */
#define L6480_REG_ST_SLP_ADDR   0x0E
#define L6480_REG_ST_SLP_LEN    sizeof(l6480_reg_st_slp_t)
#define L6480_REG_ST_SLP_RW     L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register FN_SLP_ACC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_fn_slp_acc_t;
/*! \name fn_slp_acc
 * @{
 */
#define L6480_REG_FN_SLP_ACC_ADDR   0x0F
#define L6480_REG_FN_SLP_ACC_LEN    sizeof(l6480_reg_fn_slp_acc_t)
#define L6480_REG_FN_SLP_ACC_RW     L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register FN_SLP_DEC
 */
typedef union {
    struct {
        uint8_t data;
    } raw;
} l6480_reg_fn_slp_dec_t;
/*! \name fn_slp_dec
 * @{
 */
#define L6480_REG_FN_SLP_DEC_ADDR   0x10
#define L6480_REG_FN_SLP_DEC_LEN    sizeof(l6480_reg_fn_slp_dec_t)
#define L6480_REG_FN_SLP_DEC_RW     L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register K_THERM
 */
typedef union {
    struct {
        uint8_t data   :  4;
        uint8_t unused :  4;
    } raw;
} l6480_reg_k_therm_t;
/*! \name k_therm
 * @{
 */
#define L6480_REG_K_THERM_ADDR  0x11
#define L6480_REG_K_THERM_LEN   sizeof(l6480_reg_k_therm_t)
#define L6480_REG_K_THERM_RW    L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register ADC_OUT
 */
typedef union {
    struct {
        uint8_t data   :  5;
        uint8_t unused :  3;
    } raw;
} l6480_reg_adc_out_t;
/*! \name adc_out
 * @{
 */
#define L6480_REG_ADC_OUT_ADDR  0x12
#define L6480_REG_ADC_OUT_LEN   sizeof(l6480_reg_adc_out_t)
#define L6480_REG_ADC_OUT_RW    L6480_REG_RW_R
/*! @} */

/*! \typedef
 *  \brief Register OCD_TH
 */
typedef union {
    struct {
        uint8_t data   :  5;
        uint8_t unused :  3;
    } raw;
} l6480_reg_ocd_th_t;
/*! \name ocd_th
 * @{
 */
#define L6480_REG_OCD_TH_ADDR   0x13
#define L6480_REG_OCD_TH_LEN    sizeof(l6480_reg_ocd_th_t)
#define L6480_REG_OCD_TH_RW     L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register STALL_TH
 */
typedef union {
    struct {
        uint16_t data   :  5;
        uint16_t unused :  3;
    } raw;
} l6480_reg_stall_th_t;
/*! \name stall_th
 * @{
 */
#define L6480_REG_STALL_TH_ADDR 0x14
#define L6480_REG_STALL_TH_LEN  sizeof(l6480_reg_stall_th_t)
#define L6480_REG_STALL_TH_RW   L6480_REG_RW_WR
/*! @} */

/*! \typedef
 *  \brief Register STEP_MODE
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
/*! \typedef
 * \brief enum for Step mode selection
 */
typedef enum {
    L6480_STEP_SEL_FULL         = 0x00, /*!< Step mode Full-step */
    L6480_STEP_SEL_HALF         = 0x01, /*!< Step mode Half-step */
    L6480_STEP_SEL_MICRO_4      = 0x02, /*!< Step mode 1/4   Microstep */
    L6480_STEP_SEL_MICRO_8      = 0x03, /*!< Step mode 1/8   Microstep */
    L6480_STEP_SEL_MICRO_16     = 0x04, /*!< Step mode 1/16  Microstep */
    L6480_STEP_SEL_MICRO_32     = 0x05, /*!< Step mode 1/32  Microstep */
    L6480_STEP_SEL_MICRO_64     = 0x06, /*!< Step mode 1/64  Microstep */
    L6480_STEP_SEL_MICRO_128    = 0x07, /*!< Step mode 1/128 Microstep */
} l6480_step_sel_t;
/*! \typedef
 * \brief enum for SYNC signal source
 */
typedef enum {
    L6480_SYNC_SEL_EL_POS_7     = 0X00, /*!< Electrical position [7] */
    L6480_SYNC_SEL_EL_POS_6     = 0X01, /*!< Electrical position [6] */
    L6480_SYNC_SEL_EL_POS_5     = 0X02, /*!< Electrical position [5] */
    L6480_SYNC_SEL_EL_POS_4     = 0X03, /*!< Electrical position [4] */
    L6480_SYNC_SEL_EL_POS_3     = 0X04, /*!< Electrical position [3] */
    L6480_SYNC_SEL_EL_POS_2     = 0X05, /*!< Electrical position [2] */
    L6480_SYNC_SEL_EL_POS_1     = 0X06, /*!< Electrical position [1] */
    L6480_SYNC_SEL_EL_POS_0     = 0X07, /*!< Electrical position [0] */
} l6480_sync_sig_src_t;
/*! \name step_mode
 * @{
 */
#define L6480_REG_STEP_MODE_ADDR    0x16
#define L6480_REG_STEP_MODE_LEN     sizeof(l6480_reg_step_mode_t)
#define L6480_REG_STEP_MODE_RW      L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register ALARM_EN
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
/*! \typedef
 *  \brief enum for ALARM_EN bits
 */
typedef enum {
    L6480_ALARM_EN_OVERCURRENT      = 0x00, /*!< Overcurrent alarm enabled */
    L6480_ALARM_EN_THERM_SHOTDOWN   = 0x01, /*!< Thermal shutdown alarm enabled */
    L6480_ALARM_EN_THERM_WARNING    = 0x02, /*!< Thermal warning alarm enabled */
    L6480_ALARM_EN_UVLO             = 0x03, /*!< UVLO alarm enabled */
    L6480_ALARM_EN_ADC_UVLO         = 0x04, /*!< ADC UVLO alarm enabled */
    L6480_ALARM_EN_STALL_DET        = 0x05, /*!< Stall detection alarm enabled */
    L6480_ALARM_EN_SWITCH_ON        = 0x06, /*!< Switch turn-on event alarm enabled */
    L6480_ALARM_EN_CMD_ERROR        = 0x07, /*!< Command error alarm enabled */
} l6480_alarm_en_t;
#define L6480_ALARM_EN_OVERCURRENT_MASK      = (1 << L6480_ALARM_EN_OVERCURRENT   )
#define L6480_ALARM_EN_THERM_SHOTDOWN_MASK   = (1 << L6480_ALARM_EN_THERM_SHOTDOWN)
#define L6480_ALARM_EN_THERM_WARNING_MASK    = (1 << L6480_ALARM_EN_THERM_WARNING )
#define L6480_ALARM_EN_UVLO_MASK             = (1 << L6480_ALARM_EN_UVLO          )
#define L6480_ALARM_EN_ADC_UVLO_MASK         = (1 << L6480_ALARM_EN_ADC_UVLO      )
#define L6480_ALARM_EN_STALL_DET_MASK        = (1 << L6480_ALARM_EN_STALL_DET     )
#define L6480_ALARM_EN_SWITCH_ON_MASK        = (1 << L6480_ALARM_EN_SWITCH_ON     )
#define L6480_ALARM_EN_CMD_ERROR_MASK        = (1 << L6480_ALARM_EN_CMD_ERROR     )
/*! \name alarm_en
 * @{
 */
#define L6480_REG_ALARM_EN_ADDR    0x17
#define L6480_REG_ALARM_EN_LEN     sizeof(l6480_reg_alarm_en_t)
#define L6480_REG_ALARM_EN_RW      L6480_REG_RW_WS
/*! @} */

/*! \typedef
 *  \brief Register GATECFG1
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
/*! \typedef
 *  \brief enum for IGATE
 */
typedef enum {
    L6480_GATECFG1_IGATE_4_A    = 0x00, /*!< Gate current  4 mA */
    L6480_GATECFG1_IGATE_4_B    = 0x01, /*!< Gate current  4 mA */
    L6480_GATECFG1_IGATE_8      = 0x02, /*!< Gate current  8 mA */
    L6480_GATECFG1_IGATE_16     = 0x03, /*!< Gate current 16 mA */
    L6480_GATECFG1_IGATE_24     = 0x04, /*!< Gate current 24 mA */
    L6480_GATECFG1_IGATE_32     = 0x05, /*!< Gate current 32 mA */
    L6480_GATECFG1_IGATE_64     = 0x06, /*!< Gate current 64 mA */
    L6480_GATECFG1_IGATE_96     = 0x07, /*!< Gate current 96 mA */
} l6480_gatecfg1_igate_t;
/*! \typedef
 *  \brief enum for TBOOST
 */
typedef enum {
    L6480_GATECFG1_TBOOST_0     = 0x00, /*!< Turn-off boost time    0 ns */
    L6480_GATECFG1_TBOOST_62    = 0x00, /*!< Turn-off boost time   62 ns */
    L6480_GATECFG1_TBOOST_125   = 0x00, /*!< Turn-off boost time  125 ns */
    L6480_GATECFG1_TBOOST_250   = 0x00, /*!< Turn-off boost time  250 ns */
    L6480_GATECFG1_TBOOST_375   = 0x00, /*!< Turn-off boost time  375 ns */
    L6480_GATECFG1_TBOOST_500   = 0x00, /*!< Turn-off boost time  500 ns */
    L6480_GATECFG1_TBOOST_750   = 0x00, /*!< Turn-off boost time  750 ns */
    L6480_GATECFG1_TBOOST_1000  = 0x00, /*!< Turn-off boost time 1000 ns */
} l6480_gatecfg1_tboost_t;
/*! \name gatecfg1
 * @{
 */
#define L6480_REG_GATECFG1_ADDR    0x18
#define L6480_REG_GATECFG1_LEN     sizeof(l6480_reg_gatecfg1_t)
#define L6480_REG_GATECFG1_RW      L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register GATECFG2
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
/*! \name gatecfg2
 * @{
 */
#define L6480_REG_GATECFG2_ADDR    0x19
#define L6480_REG_GATECFG2_LEN     sizeof(l6480_reg_gatecfg2_t)
#define L6480_REG_GATECFG2_RW      L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register CONFIG
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
/*! \typedef
 *  \brief enum for system clock source selection
 */
typedef enum {
    L6480_CONFIG_OSC_SEL_INT_16_NO_OUT_A    = 0x00, /*!< Internal oscillator 16 MHz, no output */
    L6480_CONFIG_OSC_SEL_INT_16_NO_OUT_B    = 0x01, /*!< Internal oscillator 16 MHz, no output */
    L6480_CONFIG_OSC_SEL_INT_16_NO_OUT_C    = 0x02, /*!< Internal oscillator 16 MHz, no output */
    L6480_CONFIG_OSC_SEL_INT_16_NO_OUT_D    = 0x03, /*!< Internal oscillator 16 MHz, no output */
    L6480_CONFIG_OSC_SEL_INT_16_OUT_2M      = 0x08, /*!< Internal oscillator 16 MHz, output frequency  2 MHz */
    L6480_CONFIG_OSC_SEL_INT_16_OUT_4M      = 0x09, /*!< Internal oscillator 16 MHz, output frequency  4 MHz */
    L6480_CONFIG_OSC_SEL_INT_16_OUT_8M      = 0x0A, /*!< Internal oscillator 16 MHz, output frequency  8 MHz */
    L6480_CONFIG_OSC_SEL_INT_16_OUT_16M     = 0x0B, /*!< Internal oscillator 16 MHz, output frequency 16 MHz */
    L6480_CONFIG_OSC_SEL_EXT_XTAL_8         = 0x04, /*!< External crystal or resonator  8 MHz */
    L6480_CONFIG_OSC_SEL_EXT_XTAL_16        = 0x05, /*!< External crystal or resonator 16 MHz */
    L6480_CONFIG_OSC_SEL_EXT_XTAL_24        = 0x06, /*!< External crystal or resonator 24 MHz */
    L6480_CONFIG_OSC_SEL_EXT_XTAL_32        = 0x07, /*!< External crystal or resonator 32 MHz */
    L6480_CONFIG_OSC_SEL_EXT_CLK_8          = 0x0C, /*!< External clock source  8 MHz */
    L6480_CONFIG_OSC_SEL_EXT_CLK_16         = 0x0D, /*!< External clock source 16 MHz */
    L6480_CONFIG_OSC_SEL_EXT_CLK_24         = 0x0E, /*!< External clock source 24 MHz */
    L6480_CONFIG_OSC_SEL_EXT_CLK_32         = 0x0F, /*!< External clock source 32 MHz */
} l6480_osc_sel_t;
/*! \typedef
 *  \brief enum for external switch interrupt mode
 */
typedef enum {
    L6480_CONFIG_SW_MODE_HARD  = 0x00, /*!< Hard stop interrupt */ 
    L6480_CONFIG_SW_MODE_SOFT  = 0x01, /*!< User disposal */
} l6480_sw_mode_t;
/*! \typedef
 *  \brief enum for overcurrent event
 */
typedef enum {
    L6480_CONFIG_OC_SD_SHUTDOWN     = 0x01, /*!< Bridges shut down */
    L6480_CONFIG_OC_SD_NO_SHUTDOWN  = 0x00, /*!< Bridges do not shut down */
} l6480_oc_sd_t;
/*! \typedef
 *  \brief enum for Programmable Vcc regulator output voltage
 */
typedef enum {
    L6480_CONFIG_VCCVAL_75  = 0x00, /*!< Vcc voltage 7.5 V */
    L6480_CONFIG_VCCVAL_15  = 0x01, /*!< Vcc voltage 15 V */
} l6480_vccval_t;
/*! \typedef
 *  \brief enum for UVLO protection thresholds
 */
typedef enum {
    L6480_CONFIG_UVLOVAL_LOW    = 0x00, /*!< Vcc_th_on =  6.9 V Vcc_th_off = 6.3 V Vboot_th_on =   6 V Vboot_th_off = 5.5 V */
    L6480_CONFIG_UVLOVAL_HIGH   = 0x01, /*!< Vcc_th_on = 10.4 V Vcc_th_off =  10 V Vboot_th_on = 9.2 V Vboot_th_off = 8.8 V */
} l6480_uvloval_t;
/*! \typedef
 *  \brief enum Motor supply voltage compensation
 */ 
typedef enum {
    L6480_CONFIG_EN_VSCOMP_DIS  = 0x00, /*!< Motor supply voltage compensation disabled */
    L6480_CONFIG_EN_VSCOMP_EN   = 0x01, /*!< Motor supply voltage compensation enabled */
} l6480_en_vscomp_t;
/*! \typedef
 *  \brief enum for pwm frequency division factor
 */
typedef enum {
    L6480_CONFIG_F_PWM_INT_1    = 0x00, /*!< Integer division factor 1 */
    L6480_CONFIG_F_PWM_INT_2    = 0x01, /*!< Integer division factor 2 */
    L6480_CONFIG_F_PWM_INT_3    = 0x02, /*!< Integer division factor 3 */
    L6480_CONFIG_F_PWM_INT_4    = 0x03, /*!< Integer division factor 4 */
    L6480_CONFIG_F_PWM_INT_5    = 0x04, /*!< Integer division factor 5 */
    L6480_CONFIG_F_PWM_INT_6    = 0x05, /*!< Integer division factor 6 */
    L6480_CONFIG_F_PWM_INT_7_A  = 0x06, /*!< Integer division factor 7 */
    L6480_CONFIG_F_PWM_INT_7_B  = 0x07, /*!< Integer division factor 7 */
} l6480_f_pwm_int_t;
/*! \typedef
 *  \brief enum for pwm frequency multiplication factor
 */
typedef enum {
    L6480_CONFIG_F_PWM_INT_0_625    = 0x00, /*!< Multiplication factor 0.625 */
    L6480_CONFIG_F_PWM_INT_0_75     = 0x01, /*!< Multiplication factor 0.75  */
    L6480_CONFIG_F_PWM_INT_0_875    = 0x02, /*!< Multiplication factor 0.875 */
    L6480_CONFIG_F_PWM_INT_1        = 0x03, /*!< Multiplication factor 1     */
    L6480_CONFIG_F_PWM_INT_1_25     = 0x04, /*!< Multiplication factor 1.25  */
    L6480_CONFIG_F_PWM_INT_1_5      = 0x05, /*!< Multiplication factor 1.5   */
    L6480_CONFIG_F_PWM_INT_1_75     = 0x06, /*!< Multiplication factor 1.75  */
    L6480_CONFIG_F_PWM_INT_2        = 0x07, /*!< Multiplication factor 2     */
} l6480_f_pwm_dec_t;
/*! \name config
 * @{
 */
#define L6480_REG_CONFIG_ADDR    0x1A
#define L6480_REG_CONFIG_LEN     sizeof(l6480_reg_config_t)
#define L6480_REG_CONFIG_RW      L6480_REG_RW_WH
/*! @} */

/*! \typedef
 *  \brief Register STATUS
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
/*! \typedef
 *  \brief enum for device thermal status interpretation
 */
typedef enum {
    L6480_STATUS_TH_STATUS_NORMAL       = 0x00, /*!< Normal */
    L6480_STATUS_TH_STATUS_WARNING      = 0x01, /*!< Warning */
    L6480_STATUS_TH_STATUS_BRI_SHTDWN   = 0x02, /*!< Bridge shutdown */
    L6480_STATUS_TH_STATUS_DEV_SHTDWN   = 0x03, /*!< Device shutdown */
} l6480_th_status_t;
/*! \typedef
 *  \brief enum for direction status
 */
typedef enum {
    L6480_STATUS_DIR_FWD    = 0x00, /*!< Forward */
    L6480_STATUS_DIR_REV    = 0x01, /*!< Reverse */
} l6480_dir_status_t;
/*! \typedef
 *  \brief enum for motor status interpretation
 */
typedef enum {
    L6480_STATUS_MOT_STATUS_STOP    = 0x00, /*!< Stopped */
    L6480_STATUS_MOT_STATUS_ACC     = 0x01, /*!< Acceleration */
    L6480_STATUS_MOT_STATUS_DEC     = 0x02, /*!< Deceleration */
    L6480_STATUS_MOT_STATUS_CONST   = 0x03, /*!< Constant speed */
} l6480_mot_status_t;
#define L6480_REG_STATUS_ADDR    0x1B
#define L6480_REG_STATUS_LEN     sizeof(l6480_reg_status_t)
#define L6480_REG_STATUS_RW      L6480_REG_RW_R
/*! @} */

/*! \typedef
 *  \brief L6480 Registers
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

/*! \typedef
 *  \brief Address for L6480 Registers
 */
typedef enum {
    L6480_REG_ABS_POS_ADDR_ENUM     = L6480_REG_ABS_POS_ADDR,   /*!< Address for ABS_POS */
    L6480_REG_EL_POS_ADDR_ENUM      = L6480_REG_EL_POS_ADDR,    /*!< Address for EL_POS */
    L6480_REG_MARK_ADDR_ENUM        = L6480_REG_MARK_ADDR,      /*!< Address for MARK */
    L6480_REG_SPEED_ADDR_ENUM       = L6480_REG_SPEED_ADDR,     /*!< Address for SPEED */
    L6480_REG_ACC_ADDR_ENUM         = L6480_REG_ACC_ADDR,       /*!< Address for ACC */
    L6480_REG_DEC_ADDR_ENUM         = L6480_REG_DEC_ADDR,       /*!< Address for DEC */
    L6480_REG_MAX_SPEED_ADDR_ENUM   = L6480_REG_MAX_SPEED_ADDR, /*!< Address for MAX_SPEED */
    L6480_REG_MIN_SPEED_ADDR_ENUM   = L6480_REG_MIN_SPEED_ADDR, /*!< Address for MIN_SPEED */
    L6480_REG_FS_SPD_ADDR_ENUM      = L6480_REG_FS_SPD_ADDR,    /*!< Address for FS_SPD */
    L6480_REG_KVAL_HOLD_ADDR_ENUM   = L6480_REG_KVAL_HOLD_ADDR, /*!< Address for KVAL_HOLD */
    L6480_REG_KVAL_RUN_ADDR_ENUM    = L6480_REG_KVAL_RUN_ADDR,  /*!< Address for KVAL_RUN */
    L6480_REG_KVAL_ACC_ADDR_ENUM    = L6480_REG_KVAL_ACC_ADDR,  /*!< Address for KVAL_ACC */
    L6480_REG_KVAL_DEC_ADDR_ENUM    = L6480_REG_KVAL_DEC_ADDR,  /*!< Address for KVAL_DEC */
    L6480_REG_INT_SPEED_ADDR_ENUM   = L6480_REG_INT_SPEED_ADDR, /*!< Address for INT_SPEED */
    L6480_REG_ST_SLP_ADDR_ENUM      = L6480_REG_ST_SLP_ADDR,    /*!< Address for ST_SLP */
    L6480_REG_FN_SLP_ACC_ADDR_ENUM  = L6480_REG_FN_SLP_ACC_ADDR,/*!< Address for FN_SLP_ACC */
    L6480_REG_FN_SLP_DEC_ADDR_ENUM  = L6480_REG_FN_SLP_DEC_ADDR,/*!< Address for FN_SLP_DEC */
    L6480_REG_K_THERM_ADDR_ENUM     = L6480_REG_K_THERM_ADDR,   /*!< Address for K_THERM */
    L6480_REG_ADC_OUT_ADDR_ENUM     = L6480_REG_ADC_OUT_ADDR,   /*!< Address for ADC_OUT */
    L6480_REG_OCD_TH_ADDR_ENUM      = L6480_REG_OCD_TH_ADDR,    /*!< Address for OCD_TH */
    L6480_REG_STALL_TH_ADDR_ENUM    = L6480_REG_STALL_TH_ADDR,  /*!< Address for STALL_TH */
    L6480_REG_STEP_MODE_ADDR_ENUM   = L6480_REG_STEP_MODE_ADDR, /*!< Address for STEP_MODE */
    L6480_REG_ALARM_EN_ADDR_ENUM    = L6480_REG_ALARM_EN_ADDR,  /*!< Address for ALARM_EN */
    L6480_REG_GATECFG1_ADDR_ENUM    = L6480_REG_GATECFG1_ADDR,  /*!< Address for GATECFG1 */
    L6480_REG_GATECFG2_ADDR_ENUM    = L6480_REG_GATECFG2_ADDR,  /*!< Address for GATECFG2 */
    L6480_REG_CONFIG_ADDR_ENUM      = L6480_REG_CONFIG_ADDR,    /*!< Address for CONFIG */
    L6480_REG_STATUS_ADDR_ENUM      = L6480_REG_STATUS_ADDR,    /*!< Address for STATUS */
} l6480_reg_addr_t;

/*******************************************************************************
Commands
*******************************************************************************/

/*! \name Command NOP
 *  \brief Command NOP
 */
#define L6480_CMD_NOP                       0x00
#define L6480_CMD_NOP_LEN                   1
#define L6480_CMD_NOP_READ                  0
/*! @} */

/*! \name Command SetParam(PARAM, VALUE)
 *  \brief Command SetParam(PARAM, VALUE)
 */
#define L6480_CMD_SETPARAM(reg)             (0x00 | L6480_REG_##reg##_ADDR)
#define L6480_CMD_SETPARAM_LEN(reg)         (1 + L6480_REG_##reg##_LEN)
#define L6480_CMD_SETPARAM_READ(reg)        0
/*! @} */

/*! \name Command
 *  \brief Command GetParam(PARAM, VALUE)
 */
#define L6480_CMD_GETPARAM(reg)             (0x20 | L6480_REG_##reg##_ADDR)
#define L6480_CMD_GETPARAM_LEN(reg)         (1 + L6480_REG_##reg##_LEN)
#define L6480_CMD_GETPARAM_READ(reg)        1
/*! @} */

/*! \name Command
 *  \brief Command Run(DIR, SPD)
 */
#define L6480_CMD_RUN(dir)                  (0x50 | (dir?0x01:0x00))
#define L6480_CMD_RUN_LEN(dir)              4
#define L6480_CMD_RUN_READ(dir)             0
/*! @} */

/*! \name Command
 *  \brief Command StepClock(DIR)
 */
#define L6480_CMD_STEPCLOCK(dir)            (0x58 | (dir?0x01:0x00))
#define L6480_CMD_STEPCLOCK_LEN(dir)        1
#define L6480_CMD_STEPCLOCK_READ(dir)       0
/*! @} */

/*! \name Command
 *  \brief Command Move(DIR, N_STEP)
 */
#define L6480_CMD_MOVE(dir)                 (0x40 | (dir?0x01:0x00))
#define L6480_CMD_MOVE_LEN(dir)             4
#define L6480_CMD_MOVE_READ(dir)            0
/*! @} */

/*! \name Command
 *  \brief Command GoTo(ABS_POS)
 */
#define L6480_CMD_GOTO                      0x60
#define L6480_CMD_GOTO_LEN                  4
#define L6480_CMD_GOTO_READ                 0
/*! @} */

/*! \name Command
 *  \brief Command GoTo_DIR(DIR, ABS_POS)
 */
#define L6480_CMD_GOTO_DIR(dir)             (0x68 | (dir?0x01:0x00))
#define L6480_CMD_GOTO_DIR_LEN(dir)         4
#define L6480_CMD_GOTO_DIR_READ(dir)        0
/*! @} */

/*! \name Command
 *  \brief Command GoUntil(ACT, DIR, SPD)
 */
#define L6480_CMD_GOUNTIL(act, dir)         (0x82 | (act?0x08:0x00) | (dir?0x01:0x00))
#define L6480_CMD_GOUNTIL_LEN(act, dir)     4
#define L6480_CMD_GOUNTIL_READ(act, dir)    0
/*! @} */

/*! \name Command
 *  \brief Command ReleaseSW(act, dir)
 */
#define L6480_CMD_RELEASESW(act, dir)       (0x92 | (act?0x08:0x00) | (dir?0x01:0x00))
#define L6480_CMD_RELEASESW_LEN(act, dir)   1
#define L6480_CMD_RELEASESW_READ(act, dir)  0
/*! @} */

/*! \name Command GoHome
 *  \brief Command GoHome
 */
#define L6480_CMD_GOHOME                    0x70
#define L6480_CMD_GOHOME_LEN                1
#define L6480_CMD_GOHOME_READ               0
/*! @} */

/*! \name Command GoMark
 *  \brief Command GoMark
 */
#define L6480_CMD_GOMARK                    0x74
#define L6480_CMD_GOMARK_LEN                1
#define L6480_CMD_GOMARK_READ               0
/*! @} */

/*! \name Command ResetPos
 *  \brief Command ResetPos
 */
#define L6480_CMD_RESETPOS                  0xD8
#define L6480_CMD_RESETPOS_LEN              1
#define L6480_CMD_RESETPOS_READ             0
/*! @} */

/*! \name Command ResetDevice
 *  \brief Command ResetDevice
 */
#define L6480_CMD_RESETDEVICE               0xC0
#define L6480_CMD_RESETDEVICE_LEN           1
#define L6480_CMD_RESETDevice_READ          0
/*! @} */

/*! \name Command SoftStop
 *  \brief Command SoftStop
 */
#define L6480_CMD_SOFTSTOP                  0xB0
#define L6480_CMD_SOFTSTOP_LEN              1
#define L6480_CMD_SOTFSTOP_READ             0
/*! @} */

/*! \name Command HardStop
 *  \brief Command HardStop
 */
#define L6480_CMD_HARDSTOP                  0xB8
#define L6480_CMD_HARDSTOP_LEN              1
#define L6480_CMD_HARDSTOP_READ             0
/*! @} */

/*! \name Command SoftHiZ
 *  \brief Command SoftHiZ
 */
#define L6480_CMD_SOFTHIZ                   0xA0
#define L6480_CMD_SOFTHIZ_LEN               1
#define L6480_CMD_SOFTHIZ_READ              0
/*! @} */

/*! \name Command HardHiZ
 *  \brief Command HardHiZ
 */
#define L6480_CMD_HARDHIZ                   0xA8
#define L6480_CMD_HARDHIZ_LEN               1
#define L6480_CMD_HARDHIZ_READ              0
/*! @} */

/*! \name Command GetStatus
 *  \brief Command GetStatus
 */
#define L6480_CMD_GETSTATUS                 0xD0
#define L6480_CMD_GETSTATUS_LEN             3
#define L6480_CMD_GETSTATUS_READ            1
/*! @} */

#endif /* L6480_H */
