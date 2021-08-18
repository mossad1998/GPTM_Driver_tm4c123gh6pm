#include "tm4c123gh6pm.h"
#include "GPIO_Driver.h"
#include "GPTM_Driver.h"
#include "Clock_Driver.h"

//Example of using GPTM_Driver

/* This driver uses the GPIO_Driver and GPTM_Driver libraries which provide definitions for
   different functions that help to intialize Tiva c  peripherals.
   To use this driver you will also need to use tm4c123gh6pm to map 
   registers correctly.
   This example used to turn on the red led for 20ms and turn off the same led
   for the same period of time.
   Used pins
   ===========
   Pin F1 as Output led
   History
   =======
   2021/August/18  - First release (Mosad)
   mo.eldibani@gmail.com
*/

int main()
{
  Debug_Intialization();                                                        //Led Intialization        
  Set_Clock_MHz(16,80);                                                         //Main Clk Speed
  CLK_Enable_GPTM_Module(1);                                                    //Enable Clk For Timer Module 1
  Enable_Timer_Number(1,"Disable");                                             //Disable Timer        
  Timer_Number_Option(1,"16");                                                  //16 bits Option Timer
  Timer_Number_Mode(1,"periodic");                                              //Periodic Mode For Timer Module 1
  Timer_Number_Prescaler(1,80000000,320000);                                    //Set Prescaler Value

      while(1)
      {       
          Debug_Led("Red",1);                                                   //Turn On Red Led
          GPTM_Delay_Unit(1,20,"Millisecond");                                  //Delay with 20 ms
          Debug_Led("Red",0);                                                   //Turn Off Red Led
          GPTM_Delay_Unit(1,20,"Millisecond");                                  //Delay with 20 ms
      }
}
