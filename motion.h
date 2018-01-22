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


#include <SmoothMove.h>          // https://github.com/daPhoosa/SmoothMove                --instal to libraries diectory


// **** MOVEMENT ENGINE ****
SmoothMove motion(MACHINE_ACCEL, MAX_VELOCITY, CORNER_ROUNDING);

void configMotion()
{
   motion.setExtrudeRateOverride( 1.1f );
   motion.setExrudeAccel( EXTRUDE_ACCEL );
}