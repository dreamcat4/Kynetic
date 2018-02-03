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


#include <FrequencyTimer2.h>     // https://github.com/PaulStoffregen/FrequencyTimer2     --included with teensyduino
#include <dStepper.h>            // https://github.com/daPhoosa/dStepper                  --instal to libraries diectory

volatile uint32_t stepperTickCount = STEPPER_TICK_HZ;  // used to track actual tick rate

// **** MOTOR SETUP ****
dStepper A_motor( A_MOTOR_STEP_PER_MM, A_MOTOR_DIRECTION, STEPPER_TICK_HZ, A_MOTOR_STEP_PIN, A_MOTOR_DIR_PIN, A_MOTOR_ENBL_PIN);
dStepper B_motor( B_MOTOR_STEP_PER_MM, B_MOTOR_DIRECTION, STEPPER_TICK_HZ, B_MOTOR_STEP_PIN, B_MOTOR_DIR_PIN, B_MOTOR_ENBL_PIN);
dStepper C_motor( C_MOTOR_STEP_PER_MM, C_MOTOR_DIRECTION, STEPPER_TICK_HZ, C_MOTOR_STEP_PIN, C_MOTOR_DIR_PIN, C_MOTOR_ENBL_PIN);
dStepper D_motor( D_MOTOR_STEP_PER_MM, D_MOTOR_DIRECTION, STEPPER_TICK_HZ, D_MOTOR_STEP_PIN, D_MOTOR_DIR_PIN, D_MOTOR_ENBL_PIN);


void armMotors()
{
   A_motor.enable();
   B_motor.enable();
   C_motor.enable();
   D_motor.enable();
}

void MotorTickISR() // at 60mm/s with 100k tick rate: 9.6% CPU usage
{
   //uint32_t timeNow = micros();

   A_motor.step();
   B_motor.step();
   C_motor.step();
   D_motor.step();
   
   stepperTickCount++;

   //funCounter += micros() - timeNow;
}

void startStepperTickISR()
{
   pinMode(FREQUENCYTIMER2_PIN, OUTPUT);
   FrequencyTimer2::setPeriod(STEPPER_TICK_PERIOD);
   FrequencyTimer2::setOnOverflow(MotorTickISR);
}

void setMotorTickRate()
{
   // update tick rate to account for unexpected ISR call rates at high Hz
   // this might not be needed, but some frequencies are not available, so this will mitigate the error

   static uint32_t startTime;
   uint32_t timeNow = micros();
   uint32_t elapsedTime = timeNow - startTime;
   startTime = timeNow;

   if( elapsedTime < 1100000UL && elapsedTime > 900000UL ) // don't update if excessively delayed/early
   {
      float scaleFactor = 1000000.0f / float(elapsedTime);
      uint32_t tickCount = scaleFactor * float(stepperTickCount) + 0.5f;

      A_motor.setTickRateHz( tickCount );
      B_motor.setTickRateHz( tickCount );
      C_motor.setTickRateHz( tickCount );
      D_motor.setTickRateHz( tickCount );

      //SERIAL_PORT.println( tickCount );
      //SERIAL_PORT.println( scaleFactor, 6 );
   }
   stepperTickCount = 0;
}
