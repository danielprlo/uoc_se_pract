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


/* Free-RTOS includes */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "portmacro.h"


/* MSP432 drivers includes */
#include "msp432_launchpad_board.h"
#include "uart_driver.h"
#include "edu_boosterpack_joystick.h"
#include "edu_boosterpack_buttons.h"

/* LCD realted drivers */
#include "st7735.h"
#include "st7735_msp432.h"
#include "grlib.h"




/*----------------------------------------------------------------------------*/

#define TASK_PRIORITY               ( tskIDLE_PRIORITY + 2 )
#define HEARTBEAT_TASK_PRIORITY     ( tskIDLE_PRIORITY + 1 )

#define TASK_STACK_SIZE             ( 1024 )
#define HEARTBEAT_STACK_SIZE        ( 128 )

#define HEART_BEAT_ON_MS            ( 10 )
#define HEART_BEAT_OFF_MS           ( 990 )
#define DELAY_MS                    ( 100 )
#define DELAY_DEBOUNCING            ( 400 )

#define QUEUE_SIZE                  ( 10 )
#define TX_UART_MESSAGE_LENGTH      ( 80 )


/*----------------------------------------------------------------------------*/

// Tasks
static void HeartBeatTask(void *pvParameters);
static void ADCReadingTask(void *pvParameters);
static void UARTPrintingTask(void *pvParameters);
static void ProcessingTask(void *pvParameters);
static void LCDTask(void *pvParameters);

// callbacks & functions
void callback(adc_result input);
void buttonCallback(void);
const char* getMove(int play);
void restartGame();
void InitializeLCD();
enum message_code getMessageWinner(void);

//Task sync tools and variables
SemaphoreHandle_t xButtonPressed;   //semáforo para activar la tarea ProcessingTask cuando se pulsa S1
QueueHandle_t xQueueCommands;       //cola para que tanto la tarea ADCReadingTask como ProcessingTask envien comandos de tipo message_code a la tarea UARTPrintingTask
QueueHandle_t xQueueADC;
SemaphoreHandle_t xPlayMutex;
static Graphics_Context g_sContext;

typedef enum message_code{
    play_update_message = 0,
    i_win_message = 1,
    machine_wins_message = 2,
    tie_message = 3,
} message_code;

typedef enum{
    rock = 0,
    paper = 1,
    scissors = 2,
}play;

TickType_t xTicks;
play my_play                = paper;    //variables globales que contienen la jugada del usuario (my_play) y la jugada de la máquina (machine_play)
play machine_play           = NULL;

//Helper variables
bool firstInitialization    = true;
bool ignoreNextReading      = false;
bool pendingNewGame         = false;
bool readFloatingVal        = false;

//Game stadistics
int gameWon                 = 0;
int gameLost                = 0;
int gameTied                = 0;

//Strings for each LCD line
char LCDL1[TX_UART_MESSAGE_LENGTH] = "";
char LCDL2[TX_UART_MESSAGE_LENGTH] = "";
char LCDL3[TX_UART_MESSAGE_LENGTH] = "";
char LCDL4[TX_UART_MESSAGE_LENGTH] = "";
char LCDL5[TX_UART_MESSAGE_LENGTH] = "";
char LCDL6[TX_UART_MESSAGE_LENGTH] = "";
char LCDL7[TX_UART_MESSAGE_LENGTH] = "";
/*----------------------------------------------------------------------------*/

static void HeartBeatTask(void *pvParameters){
    for(;;){
        led_toggle(MSP432_LAUNCHPAD_LED_RED);
        vTaskDelay( pdMS_TO_TICKS(HEART_BEAT_ON_MS) );
        led_toggle(MSP432_LAUNCHPAD_LED_RED);
        vTaskDelay( pdMS_TO_TICKS(HEART_BEAT_OFF_MS) );
    }
}

void InitializeLCD() {
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128);
    Graphics_setForegroundColor(&g_sContext, GRAPHICS_COLOR_BLACK);
    Graphics_setBackgroundColor(&g_sContext, GRAPHICS_COLOR_WHITE);
    GrContextFontSet(&g_sContext, &g_sFontFixed6x8);
    Graphics_clearDisplay(&g_sContext);
}

static void LCDTask(void *pvParameters){
    for(;;){
        Graphics_drawString(&g_sContext,
                            LCDL1,
                            AUTO_STRING_LENGTH,
                            10,
                            10,
                            OPAQUE_TEXT);

        Graphics_drawString(&g_sContext,
                            LCDL2,
                            AUTO_STRING_LENGTH,
                            10,
                            20,
                            OPAQUE_TEXT);

        Graphics_drawString(&g_sContext,
                            LCDL3,
                            AUTO_STRING_LENGTH,
                            10,
                            30,
                            OPAQUE_TEXT);

        Graphics_drawString(&g_sContext,
                            LCDL4,
                            AUTO_STRING_LENGTH,
                            10,
                            40,
                            OPAQUE_TEXT);

        Graphics_drawString(&g_sContext,
                            LCDL5,
                            AUTO_STRING_LENGTH,
                            10,
                            50,
                            OPAQUE_TEXT);

        Graphics_drawString(&g_sContext,
                            LCDL6,
                            AUTO_STRING_LENGTH,
                            10,
                            70,
                            OPAQUE_TEXT);
        Graphics_drawString(&g_sContext,
                            LCDL7,
                            AUTO_STRING_LENGTH,
                            10,
                            110,
                            OPAQUE_TEXT);
        vTaskDelay( pdMS_TO_TICKS(DELAY_MS) );
    }
}

static void ADCReadingTask(void *pvParameters) {
    float x;
    for(;;){
        if (!ignoreNextReading) {
            edu_boosterpack_joystick_read();
            if( xQueueReceive( xQueueADC, &x, portMAX_DELAY ) == pdPASS){

               xSemaphoreTake(xPlayMutex, portMAX_DELAY);
               //Right choice
               if (x > 13000) {
                   int newPlay = (((int)my_play+1) > 2) ? 0 : (int)my_play+1;
                   my_play = newPlay;
                   ignoreNextReading = true;
                   message_code message = play_update_message;
                   xQueueSendFromISR(xQueueCommands, &message, NULL);
               }

               //Left choice
               if (x < 3000) {
                   int newPlay = (((int)my_play-1) < 0) ? 2 : (int)my_play-1;
                   my_play = newPlay;
                   ignoreNextReading = true;
                   message_code message = play_update_message;
                   xQueueSendFromISR(xQueueCommands, &message, NULL);
               }
               xSemaphoreGive(xPlayMutex);
            }
        } else {
            ignoreNextReading = false;
        }

        vTaskDelay( pdMS_TO_TICKS(DELAY_MS) );
    }
}

static void UARTPrintingTask(void *pvParameters) {
    char toPrint[TX_UART_MESSAGE_LENGTH];
    message_code message;
    for(;;){
        if( xQueueReceive( xQueueCommands, &message, portMAX_DELAY ) == pdPASS){
            if (message == play_update_message) {
                strncpy(LCDL1, "Chose your move: ", TX_UART_MESSAGE_LENGTH);
                sprintf(toPrint,  "%s", getMove(my_play));
                strncpy(LCDL2, toPrint, TX_UART_MESSAGE_LENGTH);
            } else {
                strncpy(LCDL3, "The AI chosed: ", TX_UART_MESSAGE_LENGTH);
                sprintf(toPrint,  "%s", getMove(machine_play));
                strncpy(LCDL4, toPrint, TX_UART_MESSAGE_LENGTH);

                if (message == i_win_message) {
                    strncpy(LCDL5, "You win!", TX_UART_MESSAGE_LENGTH);
                    gameWon++;
                } else if (message == machine_wins_message) {
                    strncpy(LCDL5, "You lose!", TX_UART_MESSAGE_LENGTH);
                    gameLost++;
                }else if (message == tie_message) {
                    strncpy(LCDL5, "Tie!", TX_UART_MESSAGE_LENGTH);
                    gameTied++;
                }

                sprintf(toPrint,  "Win %d Tie %d Los %d!", gameWon, gameTied, gameLost);
                strncpy(LCDL6, toPrint, TX_UART_MESSAGE_LENGTH);
                strncpy(LCDL7, "S1 to play again!", TX_UART_MESSAGE_LENGTH);
                pendingNewGame = true;
            }
        }

        vTaskDelay( pdMS_TO_TICKS(DELAY_MS) );
    }
}

void startGame() {
    char toPrint[TX_UART_MESSAGE_LENGTH];

    //Clear LCD strings
    memset(LCDL2, 0, TX_UART_MESSAGE_LENGTH);
    memset(LCDL3, 0, TX_UART_MESSAGE_LENGTH);
    memset(LCDL4, 0, TX_UART_MESSAGE_LENGTH);
    memset(LCDL5, 0, TX_UART_MESSAGE_LENGTH);
    memset(LCDL6, 0, TX_UART_MESSAGE_LENGTH);

    //Clear display
    Graphics_clearDisplay(&g_sContext);

    //Set new game strings
    strncpy(LCDL1, "Chose your move: ", TX_UART_MESSAGE_LENGTH);
    sprintf(toPrint,  "%s", getMove(my_play));
    strncpy(LCDL2, toPrint, TX_UART_MESSAGE_LENGTH);

    //Set scores
    sprintf(toPrint,  "Win %d Tie %d Los %d!", gameWon, gameTied, gameLost);
    strncpy(LCDL7, toPrint, TX_UART_MESSAGE_LENGTH);

    firstInitialization = false;
    ignoreNextReading = false;
}

const char* getMove(int play) {
    if (play == rock) {
        return "ROCK    ";
    }

    if (play == scissors) {
        return "SCISSORS";
    }

    if (play == paper) {
        return "PAPER   ";
    }

    return 'Unkown move';
}

static void ProcessingTask(void *pvParameters) {
    message_code winner;

    for(;;){
        if (xSemaphoreTake(xButtonPressed, portMAX_DELAY) == pdPASS) {
            if (xTicks == NULL || (xTaskGetTickCount()-xTicks) > pdMS_TO_TICKS(DELAY_DEBOUNCING)) {
                xTicks = xTaskGetTickCount();
                int randVal = rand() % 3;
                if (randVal == 0) {
                    machine_play = rock;
                }else if (randVal == 1) {
                    machine_play = paper;
                } else {
                    machine_play = scissors;
                }

                winner = getMessageWinner();
                xQueueSendFromISR(xQueueCommands, &winner, NULL);
            }
        }
        vTaskDelay( pdMS_TO_TICKS(DELAY_MS) );
    }
}

enum message_code getMessageWinner(void) {
    if (my_play == machine_play) {
        return tie_message;
    } else {
        if (my_play == rock) {
            if (machine_play == scissors) {
                return i_win_message;
            }
        }else if(my_play == paper) {
            if (machine_play == rock) {
                return i_win_message;
            }
        }else if(my_play == scissors) {
            if (machine_play == paper) {
                return i_win_message;
            }
        }
    }

    return machine_wins_message;
}

void callback(adc_result input) {
    float x = input[0];

    if (readFloatingVal) {
        float floatValue = input[1];
        srand(floatValue);
        readFloatingVal = false;
    }

    xQueueSendFromISR(xQueueADC, &x, NULL);
}

void buttonCallback(void) {
    if (pendingNewGame) {
        startGame();
        pendingNewGame = false;
    } else {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xSemaphoreGiveFromISR(xButtonPressed,  xHigherPriorityTaskWoken);
    }
}
/*----------------------------------------------------------------------------*/

int main(int argc, char** argv)
{
    int32_t retVal = -1;
    bool useLotId  = false;

    // Initialize semaphores and queue
    xButtonPressed = xSemaphoreCreateBinary ();
    xQueueCommands = xQueueCreate( QUEUE_SIZE, sizeof( message_code ) );
    xQueueADC      = xQueueCreate( QUEUE_SIZE, sizeof( adc_result ) );
    xPlayMutex     = xSemaphoreCreateMutex();
    /* Initialize the board */
    board_init();
    InitializeLCD();

    /* Initialize the UART */  //configurada para trabajar a 57600bauds/s
    uart_init(NULL);

    /* Initialize the button */
    edu_boosterpack_buttons_init();
    edu_boosterpack_buttons_set_callback(MSP432_EDU_BOOSTERPACK_BUTTON_S1, buttonCallback);

    /* Initialize the joystick*/
    edu_boosterpack_joystick_init();
    edu_boosterpack_joystick_set_callback(callback);

    if (useLotId) {
        unsigned char *lotIdPointer = (*(volatile unsigned char*)0x00201030);
        srand(*lotIdPointer);
    }else {
        readFloatingVal = true;
        edu_boosterpack_joystick_read();
    }

    startGame();

    if ( (xButtonPressed != NULL) && (xQueueCommands != NULL) && (xQueueADC != NULL) && (xPlayMutex != NULL)) {

        /* Create tasks */
        retVal = xTaskCreate(HeartBeatTask, "HeartBeatTask", HEARTBEAT_STACK_SIZE, NULL, HEARTBEAT_TASK_PRIORITY, NULL );
        if(retVal < 0) {
            led_on(MSP432_LAUNCHPAD_LED_RED);
            while(1);
        }

        retVal = xTaskCreate(ADCReadingTask, "ADCReadingTask", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL );
        if(retVal < 0) {
            led_on(MSP432_LAUNCHPAD_LED_RED);
            while(1);
        }

        retVal = xTaskCreate(UARTPrintingTask, "UARTPrintingTask", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL );
        if(retVal < 0) {
            led_on(MSP432_LAUNCHPAD_LED_RED);
            while(1);
        }

        retVal = xTaskCreate(ProcessingTask, "ProcessingTask", TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL );
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
