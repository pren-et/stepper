/*!
 *  ____  ____  _____ _   _       _____ _____ 
 * |  _ \|  _ \| ____| \ | |     | ____|_   _|
 * | |_) | |_) |  _| |  \| |_____|  _|   | |  
 * |  __/|  _ <| |___| |\  |_____| |___  | |  
 * |_|   |_| \_\_____|_| \_|     |_____| |_|  
 *                                            
 * \file main.h
 * \brief Driver for Stepper driver L6480 from ST Microelectronics
 * \author pren-et
 * 
 */

#include "stdio.h"
//#include "platform.h"
#include "../SW/StepperTest/Sources/l6480.h"

int main(void) {
    printf("Hello World\n");
    l6480_init();
    printf("hardhiz\n");
    l6480_cmd_hardhiz();
    printf("run\n");
    l6480_cmd_run(1, 2);
    return 0;
}
