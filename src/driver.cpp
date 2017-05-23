#include "driver.hpp"

Driver::Driver() {
#if PI
  wiringPiSetupGpio();
  pinMode(PIN_L, OUTPUT);
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_S, OUTPUT);
#endif

  vel_r_ = 0;
  vel_l_ = 0;
  curr_step_ = 1;
  goal_step_ = 1;
  eticks_ = 0;

  delay_l_ = PERIOD_ZER;
  delay_r_ = PERIOD_ZER;
  delay_diff_ = 0;
  delay_rem_ = PERIOD_PAD - PERIOD_ZER;
  delay_e_ = (int) (STEP_SF / 75);
}
  
void Driver::process_command(Teleop_Command t) {

  vel_r_ = t.vel_r;
  vel_l_ = t.vel_l;
  
  vel_r_ = bound(t.vel_r, MAX_VEL, -MAX_VEL);
  vel_l_ = bound(t.vel_l, MAX_VEL, -MAX_VEL);
  goal_step_ = curr_step_ + t.elev_step;
  goal_step_ = bound(goal_step_, 16, 0);
  
  delay_l_ = (int) (PERIOD_ZER - 5 * vel_l_);
  delay_r_ = (int) (PERIOD_ZER - 5 * vel_r_);
  delay_diff_ = delay_r_ - delay_l_;
  delay_rem_ = (delay_diff_ > 0) ? PERIOD_PAD - delay_r_ : PERIOD_PAD - delay_l_;
  
#if PI
  command_pi();
#endif
}

#if PI
void Driver::command_pi() {
  if (goal_step_ == curr_step_) {
    digitalWrite(PIN_L, HIGH);
    digitalWrite(PIN_R, HIGH);
    if (delay_diff_ > 0) {
      delayMicroseconds(delay_l_);
      digitalWrite(PIN_L, LOW);
      delayMicroseconds(delay_diff_);
      digitalWrite(PIN_R, LOW);
    } else {
      delayMicroseconds(delay_r_);
      digitalWrite(PIN_R, LOW);
      delayMicroseconds(-delay_diff_);
      digitalWrite(PIN_L, LOW);
      }
    delayMicroseconds(delay_rem_);
  }
  else {
    if (goal_step_ > curr_step_) {
      digitalWrite(PIN_D, HIGH);
    }
    if (goal_step < curr_step) {
      digitalWrite(PIN_D, LOW);
    }
    eticks_ = TICK_STEP*(int)std::abs(goal_step_-curr_step_);
    for (int i = 0; i < eticks_; i++) {
      delayMicroseconds(delay_e_);
      digitalWrite(PIN_S, HIGH);
      delayMicroseconds(delay_e_);
      digitalWrite(PIN_S, LOW);
    }
    curr_step_ = goal_step_;
  }
}
#endif
  
int Driver::bound(int a, int b, int c) {
  if (a > b) return b;
  if (a < c) return c;
  return a;
}

