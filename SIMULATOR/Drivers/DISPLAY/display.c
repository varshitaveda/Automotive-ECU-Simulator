/*
 * display.c
 *
 *  Created on: Jul 30, 2026
 *      Author: Veda Varshita A
 */

#include "display.h"
#include "ssd1306.h"
#include "fonts.h"
#include <stdio.h>
#include <string.h>

void Display_Update(VehicleData_t *data, ECU_Fault_t *fault)
{
    char buff1[32];
    uint8_t faultCount = 0;

    faultCount += fault->overTemperature;
    faultCount += fault->lowFuel;
    faultCount += fault->overSpeed;
    faultCount += fault->overRPM;

    SSD1306_Fill(SSD1306_COLOR_BLACK);

    sprintf(buff1,"TEMP:%3dC",data->temperature);
    SSD1306_GotoXY(1,0);
    SSD1306_Puts(buff1,&Font_7x10,SSD1306_COLOR_WHITE);

    sprintf(buff1,"FUEL:%3d%%",data->fuel);
    SSD1306_GotoXY(1,10);
    SSD1306_Puts(buff1,&Font_7x10,SSD1306_COLOR_WHITE);

    sprintf(buff1,"SPD :%3dkmph",data->speed);
    SSD1306_GotoXY(1,20);
    SSD1306_Puts(buff1,&Font_7x10,SSD1306_COLOR_WHITE);

    sprintf(buff1,"RPM :%4d",data->rpm);
    SSD1306_GotoXY(1,30);
    SSD1306_Puts(buff1,&Font_7x10,SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(1,40);
    SSD1306_Puts("STATUS:",&Font_7x10,SSD1306_COLOR_WHITE);

    SSD1306_GotoXY(1,50);

    if(faultCount == 0)
    {
        SSD1306_Puts("OK",&Font_7x10,SSD1306_COLOR_WHITE);
    }
    else if(faultCount == 1)
    {
        /* Keep original messages for single faults */

        if(fault->overTemperature)
        {
            SSD1306_Puts("OVERHEATING",&Font_7x10,SSD1306_COLOR_WHITE);
        }
        else if(fault->lowFuel)
        {
            SSD1306_Puts("LOW FUEL",&Font_7x10,SSD1306_COLOR_WHITE);
        }
        else if(fault->overSpeed)
        {
            SSD1306_Puts("HIGH SPEED",&Font_7x10,SSD1306_COLOR_WHITE);
        }
        else if(fault->overRPM)
        {
            SSD1306_Puts("HIGH RPM",&Font_7x10,SSD1306_COLOR_WHITE);
        }
    }
    else
    {
        /* Multiple faults -> display abbreviations */

        char multiFault[20] = "";

        if(fault->overTemperature)
        {
            strcat(multiFault,"T");
        }

        if(fault->overSpeed)
        {
            if(strlen(multiFault) > 0)
                strcat(multiFault,"+");

            strcat(multiFault,"S");
        }

        if(fault->overRPM)
        {
            if(strlen(multiFault) > 0)
                strcat(multiFault,"+");

            strcat(multiFault,"R");
        }

        if(fault->lowFuel)
        {
            if(strlen(multiFault) > 0)
                strcat(multiFault,"+");

            strcat(multiFault,"L");
        }

        SSD1306_Puts(multiFault,&Font_7x10,SSD1306_COLOR_WHITE);
    }

   SSD1306_UpdateScreen();
}

void Display_IgnitionOff(void)
{
    SSD1306_Fill(SSD1306_COLOR_BLACK);

    SSD1306_GotoXY(10,20);
    SSD1306_Puts("IGNITION OFF",&Font_7x10,SSD1306_COLOR_WHITE);

    SSD1306_UpdateScreen();
}

void Display_IgnitionOn(void)
{
    SSD1306_Fill(SSD1306_COLOR_BLACK);

    SSD1306_GotoXY(10,20);
    SSD1306_Puts("IGNITION ON",&Font_7x10, SSD1306_COLOR_WHITE);

    SSD1306_UpdateScreen();
}
