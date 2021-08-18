#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "tm4c123gh6pm.h"
#include <string.h>
#include "GPIO_Driver.h"


#ifndef __Debug_Driver_H__
#define __Debug_Driver_H__

extern void Debug_Led(char color[10],bool state);										//To Control the led depend on the color
extern void Debug_Intialization(void);													//To Intialize Led Pins

#endif
