/*******************************************************************************

input_to_command.cpp

Class that statefully converts character inputs to Teleop_Commands. For 
documentation, please read header file (input_to_command.hpp)

Copyright 2017 Eric Klinkhammer

Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*******************************************************************************/

#include "input_to_command.hpp"

bool Input_To_Command::isReady() {
  return ready_;
}

Teleop_Command* Input_To_Command::getCommand() {

  int vel_r, vel_l, elev_step; 
  if (elevator_on_ == 1) {
    vel_r = 0;
    vel_l = 0;
    if (elevator_switch_ == 1) {
      elev_step = elevator_dir_;
    } else {
      elev_step = elevator_dir_ * 2;
    }
  } else {
    elev_step = 0;
    if (direction_ == 1) { // forward
      vel_r = fvels_[vel_];
      vel_l = fvels_[vel_];
    } else if (direction_ == 2) { // left
      vel_r = tfvels_[vel_];
      vel_l = tbvels_[vel_];
    } else if (direction_ == 3) { // back
      vel_r = bvels_[vel_];
      vel_l = bvels_[vel_];
    } else if (direction_ == 4) { // right
      vel_r = tbvels_[vel_];
      vel_l = tfvels_[vel_];
    } else {
      vel_r = 0;
      vel_l = 0;
    }
  }

  Teleop_Command* t = new Teleop_Command(vel_r, vel_l, 0, elev_step);
  return t;
}

void Input_To_Command::acceptChar(char input) {
  elevator_switch_ = 0;
  ready_ = false;
  switch (input) {
  case 'W':
  case 'w':
    direction_ = 1;
    elevator_on_ = 0;
    ready_ = true;
    break;
  case 'A':
  case 'a':
    direction_ = 2;
    elevator_on_ = 0;
    ready_ = true;
    break;
  case 'S':
  case 's':
    direction_ = 3;
    elevator_on_ = 0;
    ready_ = true;
    break;
  case 'D':
  case 'd':
    direction_ = 4;
    elevator_on_ = 0;
    ready_ = true;
    break;
  case 'F':
  case 'f':
    elevator_on_ = 0;
    vel_ += 1;
    break;
  case 'C':
  case 'c':
    elevator_on_ = 0;
    vel_ -= 1;
    break;
  case 'E':
  case 'e':
    elevator_on_ = 1;
    elevator_dir_ = 1;
    vel_ = 0;
    ready_ = true;
    break;
  case 'R':
  case 'r':
    elevator_on_ = 1;
    elevator_dir_ = -1;
    vel_ = 0;
    ready_ = true;
    break;
  case 'Q':
  case 'q':
    elevator_switch_ = 1;
    elevator_on_ = 1;
    vel_ = 0;
    ready_ = true;
    break;
  default:
    break;
  }

  if (vel_ >= max_vel_) {
    vel_ = max_vel_;
  } else if (vel_ < 0) {
    vel_ = 0;
  }
}
