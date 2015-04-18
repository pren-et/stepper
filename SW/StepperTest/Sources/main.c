/* ###################################################################
**     Filename    : main.c
**     Project     : StepperTest
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2015-04-07, 21:52, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "LEDG.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
//#include "STCK.h"
//#include "BitsIoLdd1.h"
//#include "WAIT1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "l6480.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  l6480_init();
  LEDG_On();
  l6480_cmd_getstatus();
  /*
  l6480_reg_config_t config;
  config.raw.data      = 0x0000;
  config.reg.ext_clk   = 0;
  config.reg.osc_sel   = 1;
  config.reg.sw_mode   = 0;
  config.reg.oc_sd     = 0;
  config.reg.vccval    = 0;
  config.reg.uvloval   = 0;
  config.reg.en_vscomp = 0;
  config.reg.f_pwm_int = 1;
  config.reg.f_pwm_dec = 5;
 // l6480_get_config();
  l6480_set_ocd_th_millivolt(1000);
  l6480_set_kval_hold(64);
  l6480_set_kval_run(64);
  l6480_set_kval_acc(64);
  l6480_set_kval_dec(64);
  l6480_set_config(config.raw.data);
  l6480_cmd_getstatus();
  l6480_cmd_run(1,500); 	// Motor vorwärts
  */
  //l6480_cmd_stepclock(1);	// Motor vorwärts
  l6480_set_ocd_th_millivolt(1000); // Overcurrentdetection
  l6480_set_stall_th_millivolt(1000); // Stalldetection
  l6480_set_gatecfg1_igate_milliampere(96);
  l6480_set_gatecfg1_tcc_nanosecond(250);
  l6480_set_gatecfg1_tboost_nanosecond(125);
  l6480_set_gatecfg2_tdt_nanosecond(250);
  l6480_set_gatecfg2_tblank_nanosecond(250);
  l6480_set_kval_hold(10);				//
  l6480_set_kval_run(10);
  //l6480_set_config_oc_sd(0);			// Brücken nicht ausschalten bei OCD
  l6480_cmd_hardstop();					// Aus HiZ
  for(;;){
  l6480_cmd_run(1,1048575); 			// Motor vorwärts
  WAIT1_Waitms(1000);
  l6480_cmd_softstop();					// Aus HiZ
  WAIT1_Waitms(1000);
  }
  l6480_cmd_getstatus();
  /*
  int i = 0;
  for(i=0;i<20000;i++) {
	  STCK_PutVal(TRUE);
	  WAIT1_Waitus(100);
	  STCK_PutVal(FALSE);
	  WAIT1_Waitus(100);
  }*/
  l6480_cmd_getstatus();
  for(;;){};

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
