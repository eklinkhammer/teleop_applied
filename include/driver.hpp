#ifndef _DRIVER_
#define _DRIVER_

#include "teleop_command.hpp"
#include <stdlib.h>
#include <iostream>

#if PI
#include <wiringPi.h>
#endif

const int MAX_VEL = 100;

// Output Pins
const int PIN_L = 20;
const int PIN_R = 21;
const int PIN_D = 19;
const int PIN_S = 16;

const int PERIOD_PAD = 20000;
const int PERIOD_ZER = 1500;

// Stepper
const double STEP_SF = 2.5*1e6 / 100;

// Elevator
const int TOTAL_TICKS = 23750;
const int TOTAL_STEPS = 16;
const int TICK_STEP = TOTAL_TICKS / TOTAL_STEPS;

class Driver {
public:
  Driver();
  void process_command(Teleop_Command);
  
  // Delay vars
  int delay_l_;
  int delay_r_;
  int delay_diff_;
  int delay_rem_;
  int delay_e_;

  // 0 - 100% wheel velocities
  int vel_l_;
  int vel_r_;

  // Elevator control
  int curr_step_;
  int goal_step_;
  int eticks_;
  
private:
#ifdef PI
  command_pi();
#endif
  // If a is between b and c, return a. Else, return closest boundary
  int bound(int,int,int);

};

#endif
