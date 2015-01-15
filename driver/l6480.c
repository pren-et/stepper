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
}
