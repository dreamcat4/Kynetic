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

#include "arduino.h"

#define SERIAL_PORT Serial

// **********************************
// **** MACHINE MOTION SETTINGS ****
// ********************************
const float MACHINE_ACCEL_XY = 5000.0f;  // mm/s^2
const float MAX_VELOCITY_XY  = 300.0f;   // mm/s

const float MACHINE_ACCEL_Z  = 500.0f;  // mm/s^2
const float MAX_VELOCITY_Z   = 50.0f;   // mm/s

const float CORNER_ROUNDING  = 0.2f;   // mm

const float EXTRUDE_ACCEL    = 10000.0f; // mm/s^2


// **************************
// **** HEATER SETTINGS ****
// ************************
const int MIN_HEATER_PERIOD = 100;  // ms
const int MAX_EXTRUDER1_TEMP = 275; // C
const int MAX_BED_TEMP = 150; // C

#define EXTRUDER1_SENSOR_TYPE 1
#define BED_SENSOR_TYPE 1

#define EXTRUDER1_PID   20.0f, 0.50f, 50.0f, 0.72f   // Prorotional, Integral, Derivative, FeedForward
#define BED_HEATER_PID 100.0f, 0.25f, 50.0f, 1.50f

#define OVER_SAMPLE_CNT 4


// **************************
// **** BUTTON SETTINGS ****
// ************************
#define SELECT_BUTTON_PRESSED 1
#define UP_BUTTON_PRESSED     1
#define DOWN_BUTTON_PRESSED   1


// ***********************************************
// **** HOME POSITION AND ENDSTOP PARAMETERS ****
// *********************************************
#define FAST_HOME_VEL  40.0f     // [mm/s]
#define SLOW_HOME_VEL  4.0f      // [mm/s]
#define SLOW_HOME_DIST 3.0f      // [mm]

#define X_HOME_OFFSET 0.0f
#define Y_HOME_OFFSET 0.0f
#define Z_HOME_OFFSET -0.1f  

#define X_HOME_DIRECTION 1.0f  // Set as either 1.0 or -1.0 for direction
#define Y_HOME_DIRECTION 1.0f
#define Z_HOME_DIRECTION 1.0f

#define X_ENDSTOP_NO_CONTACT LOW // switch state when not in contact with axis
#define Y_ENDSTOP_NO_CONTACT LOW
#define Z_ENDSTOP_NO_CONTACT LOW


// ********************************
// **** MACHINE TRAVEL LIMITS ****
// ******************************
#define X_TRAVEL_MAX  100.0f
#define X_TRAVEL_MIN -100.0f
#define Y_TRAVEL_MAX  100.0f
#define Y_TRAVEL_MIN -100.0f
#define Z_TRAVEL_MAX  100.0f
#define Z_TRAVEL_MIN    0.0f



// ************************
// **** MACHINE TYPES ****
// **********************
// ( Only enable one type of machine )

//#define MACHINE_TYPE_CARTESIAN

//#define MACHINE_TYPE_COREXY

#define MACHINE_TYPE_DELTA
#ifdef  MACHINE_TYPE_DELTA // delta arm geometry configuration
   #define DELTA_ARM_RADIUS         107.0f // 109.0 -- decrease if center is low, increase if outside is low
   #define DELTA_ARM_LENGTH         207.3f //   
   #define DELTA_MIN_ARM_ANGLE       10.0f // [deg]
   #define DELTA_CLEARANCE_FROM_HOME 25.0f

   #define A_MOTOR_HOME_OFFSET 484.7f    // 485.0f axis zero from home position [mm]
   #define B_MOTOR_HOME_OFFSET 486.0f
   #define C_MOTOR_HOME_OFFSET 486.1f  
#endif



// **** MOTOR SETTINGS ****
#define A_MOTOR_STEP_PER_MM 80.0f
#define A_MOTOR_DIRECTION   1

#define B_MOTOR_STEP_PER_MM 80.0f
#define B_MOTOR_DIRECTION   1

#define C_MOTOR_STEP_PER_MM 80.0f
#define C_MOTOR_DIRECTION   1

#define D_MOTOR_STEP_PER_MM 160.0f
#define D_MOTOR_DIRECTION   1

#define E_MOTOR_STEP_PER_MM 80.0f
#define E_MOTOR_DIRECTION   1

#define F_MOTOR_STEP_PER_MM 80.0f
#define F_MOTOR_DIRECTION   1


