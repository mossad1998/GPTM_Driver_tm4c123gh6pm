#include "Debug_Driver.h"
                
void Debug_Led(char color[10],bool state)
{
	if(strcmp(color ,"Red")==0)
	{
		if(state == 1)
			PIN_WRITE_DIGITAL('F',1,"HIGH");								//Turn on Red Led						
		else
			PIN_WRITE_DIGITAL('F',1,"LOW");									//Turn on Red Led
	}
	
		else if(strcmp(color ,"Blue")==0)
	{
		if(state == 1)
			PIN_WRITE_DIGITAL('F',2,"HIGH");								//Turn on Blue Led
		else
			PIN_WRITE_DIGITAL('F',2,"LOW");									//Turn on Blue Led
	}
	
			else if(strcmp(color ,"Green")==0)
	{
		if(state == 1)
			PIN_WRITE_DIGITAL('F',3,"HIGH");								//Turn on Green Led
		else
			PIN_WRITE_DIGITAL('F',3,"LOW");									//Turn off Green Led
	}

}
void Debug_Intialization(void)
{
  CLK_Enable('F');															//Enable clk For Port F
  GPIO_PORT_UNLOCK('F');													//Unlock Port F
        
  PIN_ANALOG_DIGITAL('F',1,"Digital");										//Set pin F1 as Digital
  PIN_FUNCTION_SELECT('F',1,"General I/O");									//Set pin F1 as general input/output
  PIN_INPUT_OUTPUT('F',1,"Output");											//Set pin F1 as Output

  PIN_ANALOG_DIGITAL('F',2,"Digital");										//Set pin F2 as Digital
  PIN_FUNCTION_SELECT('F',2,"General I/O");									//Set pin F2 as general input/output
  PIN_INPUT_OUTPUT('F',2,"Output");											//Set pin F2 as Output
	
  PIN_ANALOG_DIGITAL('F',3,"Digital");										//Set pin F3 as Digital
  PIN_FUNCTION_SELECT('F',3,"General I/O");									//Set pin F3 as general input/output
  PIN_INPUT_OUTPUT('F',3,"Output");											//Set pin F3 as Output
  
  Debug_Led("Red",0);														//Turn off Red Led
  Debug_Led("Blue",0);														//Turn off Blue Led
  Debug_Led("Green",0);														//Turn off Green Led
}
