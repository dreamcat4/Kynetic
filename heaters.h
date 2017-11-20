/*
   Kynetic CNC Control Software
   Copyright (C) 2017 Phillip Schmidt

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.
      
      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.
      
      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/


#include "slowPWM.h"
#include "heaterPID.h"

heaterPID extruder1_PID( HEATER_CONTROL_HZ, EXTRUDER1_PID );
slowPWM   extruder1_PWM( MIN_HEATER_PERIOD );

heaterPID bed_PID( HEATER_CONTROL_HZ, BED_HEATER_PID );
slowPWM   bed_PWM( MIN_HEATER_PERIOD );



void heaterController()  // set heater PWM based off of PID results
{
   

}


void heaterManager()  // operate heaters
{
   // do cool things... ha ha
   static int bed, tip;
   bed = !bed;

   digitalWrite(BED_HEATER_PWM_PIN, bed);
   digitalWrite(EXTRUDER1_PWM_PIN,  tip);

   tip = ! tip;
}
