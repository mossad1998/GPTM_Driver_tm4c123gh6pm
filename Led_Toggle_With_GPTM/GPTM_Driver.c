#include "GPTM_Driver.h"

volatile uint32_t* TIMERS_R[]={&TIMER0_CTL_R,&TIMER1_CTL_R,&TIMER2_CTL_R,                       //Array of CTL Registers for each timer
                               &TIMER3_CTL_R,&TIMER4_CTL_R,&TIMER5_CTL_R};

volatile uint32_t* TIMERS_CFG_R[]={&TIMER0_CFG_R,&TIMER1_CFG_R,&TIMER2_CFG_R,                   //Array of CFG Registers for each timer
                                   &TIMER3_CFG_R,&TIMER4_CFG_R,&TIMER5_CFG_R};

volatile uint32_t* TIMERS_TAMR_R[]={&TIMER0_TAMR_R,&TIMER1_TAMR_R,&TIMER2_TAMR_R,               //Array of TAMR Registers for each timer
                                   &TIMER3_TAMR_R,&TIMER4_TAMR_R,&TIMER5_TAMR_R};

volatile uint32_t* TIMERS_TAPR_R[]={&TIMER0_TAPR_R,&TIMER1_TAPR_R,&TIMER2_TAPR_R,               //Array of TAPR Registers for each timer
                                   &TIMER3_TAPR_R,&TIMER4_TAPR_R,&TIMER5_TAPR_R};

volatile uint32_t* TIMERS_Aload_R[]={&TIMER0_TAILR_R,&TIMER1_TAILR_R,&TIMER2_TAILR_R,           //Array of TAILR Registers for each timer
                                     &TIMER3_TAILR_R,&TIMER4_TAILR_R,&TIMER5_TAILR_R};

volatile uint32_t* TIMERS_Clear_R[]={&TIMER0_ICR_R,&TIMER1_ICR_R,&TIMER2_ICR_R,                 //Array of ICR Registers for each timer
                                     &TIMER3_ICR_R,&TIMER4_ICR_R,&TIMER5_ICR_R};

volatile uint32_t* TIMERS_Flag_R[]={&TIMER0_RIS_R,&TIMER1_RIS_R,&TIMER2_RIS_R,                  //Array of RIS Registers for each timer
                                     &TIMER3_RIS_R,&TIMER4_RIS_R,&TIMER5_RIS_R};



void CLK_Enable_GPTM_Module(int timer_number)                                                   //To Eable CLK for specific timer
{
    SYSCTL_RCGCTIMER_R |= (1UL << timer_number);
    volatile uint32_t dummy ;
    dummy = SYSCTL_RCGCTIMER_R ;                                                                //To wait untill enabling the CLK
}

void Enable_Timer_Number(int timer_number,char type[10])                                        //Enable or Disable a specific timer
{
    if(strcmp(type , "Enable")==0)
        {
        *TIMERS_R[timer_number] |= 1UL << 0;                                                    //To Enable specific timer
        }
    else if (strcmp(type , "Disable")==0)
        {
        *TIMERS_R[timer_number] &= ~(1UL << 0);                                                 //To Disable specific timer
        }
}

void Timer_Number_Option(int timer_number,char option[10])                                      //To select timer option from 16, 32, or RTC
{
    if((strcmp(option,"16"))==0)
        *TIMERS_CFG_R[timer_number] = 0x4;                                                      //16 bits option
    else if((strcmp(option,"32"))==0)
        *TIMERS_CFG_R[timer_number] = 0x0;                                                      //32 bits option
    else if ((strcmp(option,"RTC"))==0)
        *TIMERS_CFG_R[timer_number] = 0x1;                                                      //RTC option
}

void Timer_Number_Mode(int timer_number,char mode[10])                                          //To select timer option from one shot, periodic, or capture
{
    if((strcmp(mode,"one_shot"))==0)
        *TIMERS_TAMR_R[timer_number] |= 0x1;                                                    //One Shot mode
    else if((strcmp(mode,"periodic"))==0)
        *TIMERS_TAMR_R[timer_number] |= 0x2;                                                    //Periodic mode
    else if((strcmp(mode,"capture"))==0)
        *TIMERS_TAMR_R[timer_number] |= 0x3;                                                    //Capture mode
}

void Timer_Number_Prescaler (int Timer_Number ,int System_Clock, int Timer_Clock)               //To load Prescaler value
{
    int divider = System_Clock/Timer_Clock;                                                     //Calculate divider
    int bits = (int)(log(divider)/log(2));                                                      //Calculate number of Bits
    if (bits >8)
    {
        Debug_Led("Red",1);                                                                     //nuber of bits greater than 16 bits
        //printf("Load Bits is Greater than 16");
    }
    *TIMERS_TAPR_R[Timer_Number] = divider-1;                                                   //Load divider value
}

void Timer_Number_Ticks(int timer_number,int ticks)                                             //To load Number of ticks
{
    *TIMERS_Aload_R[timer_number] = ticks-1;                                                    //Load Ticks
    *TIMERS_Clear_R[timer_number]= 1;                                                           //clear timer flag
}

void GPTM_Delay_Unit(int timer_number,int Counts,char Unit[10])                                 //Delay using GPTM  Timer
{
    if((strcmp(Unit,"Seconds"))==0)                                                             //Seconds delay
    {
        Timer_Number_Ticks(1,320000);                                                           //Ticks for one second
        Enable_Timer_Number(1,"Enable");
        for(int i=0;i<Counts;i++)
        {
             while((*TIMERS_Flag_R[timer_number] & 0x1)==0);                                    //Number of seconds
             *TIMERS_Clear_R[timer_number]= 1;
        }
    }
    else if((strcmp(Unit,"Millisecond"))==0)                                                    //milliseconds delay
    {
        Timer_Number_Ticks(1,320);                                                              //ticks for one milliseconds
        Enable_Timer_Number(1,"Enable");
        for(int i=0;i<Counts;i++)
        {
             while((*TIMERS_Flag_R[timer_number] & 0x1)==0);                                    //Number of milliseconds
             *TIMERS_Clear_R[timer_number]= 1;
        }
    }
}
