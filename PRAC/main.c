/*
 * Copyright (C) 2017 Universitat Oberta de Catalunya - http://www.uoc.edu/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Universitat Oberta de Catalunya nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*----------------------------------------------------------------------------*/

/* Standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/* Free-RTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "portmacro.h"


/* MSP432 drivers includes */
#include "msp432_launchpad_board.h"

/* LCD realted drivers */
#include "st7735.h"
#include "st7735_msp432.h"
#include "grlib.h"


/*----------------------------------------------------------------------------*/

#define TASK_PRIORITY      ( tskIDLE_PRIORITY + 2 )
#define HEARTBEAT_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )

#define TASK_STACK_SIZE         ( 1024 )
#define HEARTBEAT_STACK_SIZE        ( 128 )

#define HEART_BEAT_ON_MS            ( 10 )
#define HEART_BEAT_OFF_MS           ( 990 )
#define TASK_DELAY_MS               ( 100 )

/*----------------------------------------------------------------------------*/



// Tasks
static void HeartBeatTask(void *pvParameters);
static void LCDTask(void *pvParameters);

// Global variables
static Graphics_Context g_sContext;

/*----------------------------------------------------------------------------*/

static void HeartBeatTask(void *pvParameters){
    for(;;){
        led_toggle(MSP432_LAUNCHPAD_LED_RED);
        vTaskDelay( pdMS_TO_TICKS(HEART_BEAT_ON_MS) );
        led_toggle(MSP432_LAUNCHPAD_LED_RED);
        vTaskDelay( pdMS_TO_TICKS(HEART_BEAT_OFF_MS) );
    }
}

static void LCDTask(void *pvParameters){

    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);

    Graphics_drawString(&g_sContext,
                        "Universitat Oberta",
                        AUTO_STRING_LENGTH,
                        10,
                        10,
                        OPAQUE_TEXT);

    Graphics_drawString(&g_sContext,
                        "de Catalunya",
                        AUTO_STRING_LENGTH,
                        25,
                        20,
                        OPAQUE_TEXT);

    Graphics_drawString(&g_sContext,
                        "(UOC)",
                        AUTO_STRING_LENGTH,
                        50,
                        30,
                        OPAQUE_TEXT);

    for(;;){
        vTaskDelay( pdMS_TO_TICKS(TASK_DELAY_MS) );
    }
}


/*----------------------------------------------------------------------------*/

int main(int argc, char** argv)
{
    int32_t retVal = -1;

    /* Initialize the board */
    board_init();


    if ( true ) {

        /* Create HeartBeat task */
        retVal = xTaskCreate(HeartBeatTask, "HeartBeatTask", HEARTBEAT_STACK_SIZE, NULL, HEARTBEAT_TASK_PRIORITY, NULL );
        if(retVal < 0) {
            led_on(MSP432_LAUNCHPAD_LED_RED);
            while(1);
        }

        /* Create ADCread task */
        retVal = xTaskCreate(LCDTask, "LCDTask", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL );
        if(retVal < 0) {
            led_on(MSP432_LAUNCHPAD_LED_RED);
            while(1);
        }

        /* Start the task scheduler */
        vTaskStartScheduler();
    }

    return 0;
}

/*----------------------------------------------------------------------------*/

