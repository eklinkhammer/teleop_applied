/*******************************************************************************

input_to_command.hpp

Class that converts input characters to teleop commands. Class is stateful,
and uses state to remember direction and speed settings. The motivation 
behind this decision was that the user can independently toggle speed
and direction.

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

#ifndef _INPUT_TO_TELEOP
#define _INPUT_TO_TELEOP

#include "teleop_command.hpp"

/*
 Processes inputted characters and creates Teleop_Commands. The Commands are
   based on both the last inputted character as well as internal state.

 Internal state seems necessary for a single input character system.
 */
class Input_To_Command {
  
 public:

  Input_To_Command(){};
  /*
     Creates and returns a Teleop_Command. The Command is based entirely on
       internal state. Caller responsible for delete

     Args: 
       None
     Mutates:
       None
     Returns:
       Teleop_Command class reference. 
   */
  Teleop_Command* getCommand();

  /*
     Returns if instance is ready to create a command. Only ready afer
       wasder
  */
  bool isReady();

  /*
    Accepts a user inputted character to convert into a Teleop_Command. Does
      not return a Teleop_Command, even for input characters that have direct
      commands (wasded), because nothing exists for other characters.
     
    Args:
      char i:
        w - up
	a - left
	s - down
	d - right
	e - elevator up
	r - elevator down
	q - toggle elevator
	f - faster
	c - slower
	? - ignore

    Mutates:
      direction_       : corresponds to wasd
      elevator_on_     : wasdfc -> off. erq -> on
      elevator_dir_    : toggles with q
      vel_             : toggles with fc, erq -> 0
      elevator_switch_ : q -> 1, all -> 0
      ready_           : fc -> false
    Returns:
      None
  */
  void acceptChar(char);
  
 private:
  const int max_vel_ = 9;
  int fvels_[10] = {0, 40, 45, 50, 55, 60, 65, 70, 80, 100};
  int bvels_[10] = {0, -8, -10, -12, -15, -20, -25, -30, -50, -100};
  int tfvels_[10] = {0, 58, 65, 70, 75, 80, 85, 90, 95, 100};
  int tbvels_[10] = {0, -18, -25, -30, -40, -60, -70, -80, -90, -100};
  int vel_ = 0;
  int elevator_on_ = 0;
  int elevator_dir_ = 1;
  int elevator_switch_ = 0;
  int direction_ = 0;
  bool ready_ = false;
};

#endif // _INPUT_TO_TELEOP
