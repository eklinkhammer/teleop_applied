/*******************************************************************************

teleop_command_test.cpp

Unit tests for teleop_command.hpp. Tests various methods of serialization.
Tests are primarily for instruction.

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
#include <boost/asio.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "teleop_command.hpp"


class Teleop_Command_Test : public::testing::Test {

};

TEST_F(Teleop_Command_Test, testSerializeFile) {

  std::ofstream ofs("filename");
  
  const Teleop_Command t(2, 5, 3, 1);

  {
    boost::archive::text_oarchive oa(ofs);
    oa << t;
  }

  Teleop_Command newT;

  {
    std::ifstream ifs("filename");
    boost::archive::text_iarchive ia(ifs);
    ia >> newT;
  }

  system("rm filename");

  EXPECT_EQ(t.vel_r, newT.vel_r);
  EXPECT_EQ(t.vel_l, newT.vel_l);
  EXPECT_EQ(t.vel_e, newT.vel_e);
  EXPECT_EQ(t.elev_step, newT.elev_step);
}

TEST_F(Teleop_Command_Test, testSerialize) {
  std::ostringstream os;

  const Teleop_Command t(1,2,3,4);

  {
    boost::archive::text_oarchive oa(os);
    oa << t;
  }

  std::string outbound_data_ = os.str();
}
