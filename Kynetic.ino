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

#include "config.h"
#include "Kynetic_pins.h"

#include "motors.h"
#include "dataStreams.h"
#include "timers.h"
#include "motion.h"
#include "gCode.h"

#include "3DMath.h"
#include "Machines\cartesian.h"
#include "Machines\coreXY.h"
#include "Machines\delta.h"

#include "kynetic.h"


void setup() {

   startSerial();

   startSD();

   startStepperTickISR();

   setPins();

   armMotors();
  
   startPollTimers();
}


void loop() {
   
   // Nested if-else priority scheme
   //  * After any operation completes, higher priority operations are given the first opportunity to run
   //  * All operations should run quickly so that higher priority operations are not delayed excessively
   
   if( motionControl.check() )  // Highest Priority
   {
      if( runProgram )
      {
         motorController();
      }
      else
      {
         if( machine.executeHome() )
         {
            Vec3 cart;

            machine.fwdKinematics( A_motor.getPositionMM(), B_motor.getPositionMM(), C_motor.getPositionMM(), cart.x, cart.y, cart.z ); // compute current cartesian start location

            display(cart);

            runProgram = true;

            gCodeSetPosition( cart.x, cart.y, cart.z, 0.0f );

            motion.startMoving( cart.x, cart.y, cart.z );

            startPollTimers();
         }
      }
   }
   else if( false && motionControl.precheck(10) ) // prevent executing other code if very close to next motion control operation
   {
      // do nothing
   }
   else if( runProgram && blockExecute.check() ) // Execute G code, feed blocks to the motion controller 
   {
      if( motion.bufferVacancy() )
      {
         executeCode();
         getNextProgramBlock = true; // don't get the next program line until this one has been handed to the motion controller
         //Serial.println("*");
      }
   }
   else if( getNextProgramBlock ) // Read SD card and Parse G code
   {
      // runProgram && getNextProgramBlock 
      if( !readNextProgramLine() )
      {
         fileComplete = true;
         //Serial.println("1");
      }
      else
      {
         //Serial.println("0");
      }
      getNextProgramBlock = false;
   }
   else if ( buttonsAndUI.check() ) // check if any buttons are depressed and update Display
   {
      if( digitalRead(SELECT_BUTTON_PIN) == SELECT_BUTTON_PRESSED )
      {
         if( runProgram )
         {
            runProgram = false;
         }
         else
         {
            machine.startHome( true, true, true );
         }
      }
   }
   else if( motionUpdate.check() )
   {
      // update tick rate to account for unexpected ISR call rates at high Hz
      //static uint32_t previousTickRate = STEPPER_TICK_HZ; // start at expected value
      //previousTickRate += (previousTickRate - stepperTickCount) >> 3; // low pass filter to reduce the effect of jitter
      //stepperTickCount = 0;
      stepperTickCount = stepperTickCount >> 1;
      //motion.setTickRateHz( previousTickRate );
      //SERIAL_PORT.println( stepperTickCount );
      // this might not be needed, but some frequencies are not available, so this will mitigate the error
   }
   else if( maintenance.check() ) // Lowest Priority
   {

      
      //SERIAL_PORT.print( A_motor.getPositionMM() ); SERIAL_PORT.print( "\t" );
      //SERIAL_PORT.print( B_motor.getPositionMM() ); SERIAL_PORT.print( "\t" );
      //    SERIAL_PORT.println( C_motor.getPositionMM() );
      
      //SERIAL_PORT.println( digitalRead(SELECT_BUTTON_PIN) );
      
   }   

}




