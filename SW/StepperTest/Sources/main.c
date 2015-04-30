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
#include "Stepperspi.h"
#include "SMasterLdd1.h"
#include "LEDG.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "WAIT1.h"
#include "Vent.h"
#include "BitsIoLdd1.h"
//#include "STCK.h"
//#include "BitsIoLdd1.h"
//#include "WAIT1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "../../../../stepper/driver/drv/l6480.h"

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  l6480_init();							// Compilertest
  LEDG_On();
  l6480_cmd_getstatus();

  /*******************************************************
   * Einstellungen f�r den Motor und die Treiberstufen   *
   ******************************************************/
  l6480_set_ocd_th_millivolt(1000); 			// Overcurrentdetection Treshold
  l6480_set_stall_th_millivolt(1000); 			// Stalldetection Tresold
  l6480_set_gatecfg1_igate_milliampere(96);		// Gatstrom
  l6480_set_gatecfg1_tcc_nanosecond(250);		// Bestromungszeiten
  l6480_set_gatecfg1_tboost_nanosecond(125);
  l6480_set_gatecfg2_tdt_nanosecond(250);
  l6480_set_gatecfg2_tblank_nanosecond(250);	// Pausenzeit Messung
  l6480_set_kval_hold(10);						// KVAL Motor Stillstand
  l6480_set_kval_run(128);						// kVAL Motor Run
  l6480_set_kval_acc(10);
  l6480_set_kval_dec(10);

  /*******************************************************
   * Beginn Ansteuerung									 *
   ******************************************************/
  l6480_cmd_hardstop();							// Aus HiZ
  uint16_t speed = 0;
  for(;;){
    l6480_cmd_softstop();
    WAIT1_Waitms(1000);
    l6480_cmd_run(0,speed); 					// Motor reverse
    WAIT1_Waitms(2000);
    l6480_cmd_softstop();						//
    WAIT1_Waitms(1000);
    if (speed < 0xfffff) {					// increase speed
     speed += 1000;
    }
    else {
      speed = 0;							// reset speed
    }
  }
  l6480_cmd_hardstop();							// Aus HiZ
  //uint16_t speed = 0;
  for(;;){


	  speed = 5000;
	  //l6480_cmd_run(1,speed); 					// Motor forward
	  Vent_PutVal(TRUE);
	  WAIT1_Waitms(3000);
	  Vent_PutVal(FALSE);
	  WAIT1_Waitms(1000);

	  //l6480_cmd_softstop();
	  //Vent_PutVal(TRUE);
	  //WAIT1_Waitms(1000);
	  //l6480_cmd_run(0,speed); 					// Motor reverse
	  //WAIT1_Waitms(2000);
	  //l6480_cmd_softstop();						//
	  //WAIT1_Waitms(1000);
	  /*if (speed < 0xfffff) {					// increase speed
		  speed += 1000;
	  }
	  else {
		  speed = 0;							// reset speed
	  }*/
  }

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
