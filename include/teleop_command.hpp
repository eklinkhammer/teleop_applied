/*******************************************************************************

teleop_command.hpp

Serializable struct for passing teleop commands. Intended for use on raspberry
Pi in OSU ROB 521 Applied Robotics Project.

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
#ifndef TELEOP_COMMAND_HPP
#define TELEOP_COMMAND_HPP

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Teleop_Command {
public:
  int vel_r;
  int vel_l;
  int vel_e;
  int elev_step;
  Teleop_Command(){};
  Teleop_Command(double r, double l, double e, double s) :
    vel_r(r), vel_l(l), vel_e(e), elev_step(s)
  {}
};

namespace boost {
  namespace serialization {
    template<class Archive>
    void serialize(Archive & ar, Teleop_Command & t, const unsigned int version) {
      ar & t.vel_r;
      ar & t.vel_l;
      ar & t.vel_e;
      ar & t.elev_step;
    }
  }
}

#endif // TELEOP_COMMAND_HPP
