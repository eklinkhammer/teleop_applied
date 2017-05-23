/*******************************************************************************

teleop_command.cpp

Serializable struct for passing teleop commands for OSU ROB 521 Applied Robotics
Challenge. 

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

#include <iostream>
#include "teleop_command.hpp"
#include "driver.hpp"


int main() {
  std::ofstream ofs("filename");

  const Teleop_Command t(0.1, 0.2, 0.4, 1.0);

  {
    boost::archive::text_oarchive oa(ofs);
    oa << t;
  }

  Teleop_Command newt;
  {
    std::ifstream ifs("filename");
    boost::archive::text_iarchive ia(ifs);
    ia >> newt;
  }

  std::cout << "New vel_r" << newt.vel_r << "\n";

  #ifdef PI
  std::cout << "PI is defined." << std::endl;
  #endif
  return 0;
};
