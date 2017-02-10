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

#include "Arduino.h"

#define SERIAL_PORT Serial


// **** MACHINE SETTINGS ****
const float MACHINE_ACCEL = 1000.0f;   // mm/s^2
const float MAX_VELOCITY  = 200.0f;    // mm/s
const int   STEPPER_TICK_PERIOD = 10;  // us
const uint32_t STEPPER_TICK_HZ  = 1000000UL / STEPPER_TICK_PERIOD; // Hz

const int MOTION_CONTROL_HZ = 1000; // Hz
const int BUTTONS_UI_HZ     = 20;   // Hz
const int MAINTENANCE_HZ    = 1;    // Hz

const float MACHINE_VEL_STEP = 60.0f * MACHINE_ACCEL / MOTION_CONTROL_HZ; // [mm/min]  max vel change per step at max acceleration

const float motionSmoothingCycles = 3.0f;
const float motionSmoothingRate   = MOTION_CONTROL_HZ / motionSmoothingCycles;


// **** HOME POSITION AND ENDSTOP PARAMETERS ****
#define FAST_HOME_VEL  40.0f     // [mm/s]
#define SLOW_HOME_VEL  5.0f      // [mm/s]
#define SLOW_HOME_DIST 5.0f      // [mm]

#define A_MOTOR_HOME_OFFSET 300.0f    // axis zero from home position [mm]
#define B_MOTOR_HOME_OFFSET 300.0f
#define C_MOTOR_HOME_OFFSET 300.0f

#define X_MAX_ENDSTOP_NO_CONTACT HIGH // switch state when not in contact with axis
#define Y_MAX_ENDSTOP_NO_CONTACT HIGH
#define Z_MAX_ENDSTOP_NO_CONTACT HIGH
#define X_MIN_ENDSTOP_NO_CONTACT HIGH
#define Y_MIN_ENDSTOP_NO_CONTACT HIGH
#define Z_MIN_ENDSTOP_NO_CONTACT HIGH

// **** MACHINE TRAVEL LIMITS ****
#define X_TRAVEL_MAX 100
#define X_TRAVEL_MIN 100


// **** MACHINE TYPES ****
// ( Only enable one type of machine )

//#define MACHINE_TYPE_CARTESIAN

//#define MACHINE_TYPE_COREXY

#define MACHINE_TYPE_DELTA

#ifdef MACHINE_TYPE_DELTA // delta arm geometry configuration
   #define DELTA_ARM_RADIUS 109.0f
   #define DELTA_ARM_LENGTH 207.3f
   #define DELTA_MIN_ARM_ANGLE 10.0f      // [deg]
   #define DELTA_CLEARANCE_FROM_HOME 25.0f
#endif



// **** MOTOR SETTINGS ****
#define A_MOTOR_STEP_PER_MM 80.0f
#define A_MOTOR_DIRECTION   1

#define B_MOTOR_STEP_PER_MM 80.0f
#define B_MOTOR_DIRECTION   1

#define C_MOTOR_STEP_PER_MM 80.0f
#define C_MOTOR_DIRECTION   1

#define D_MOTOR_STEP_PER_MM 80.0f
#define D_MOTOR_DIRECTION   1

#define E_MOTOR_STEP_PER_MM 80.0f
#define E_MOTOR_DIRECTION   1

#define F_MOTOR_STEP_PER_MM 80.0f
#define F_MOTOR_DIRECTION   1

