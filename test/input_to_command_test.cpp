/*******************************************************************************

input_to_command_test.cpp

Unit tests for input_to_command.cpp. Tests that the commander returns the 
  proper Teleop_Command when prompted. Input_To_Command has internal
  state (direction, readiness, and velocities) that allows for single button
  control.

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

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Input_To_Command_Test : public::testing::Test {};

bool command_eq(Teleop_Command* t1, Teleop_Command* t2) {
  return t1->vel_l == t2->vel_l && t1->vel_r == t2->vel_r &&
    t1->elev_step == t2->elev_step;
}


TEST_F(Input_To_Command_Test, testFNotReady) {
  Input_To_Command command;
  command.acceptChar('w');
  command.acceptChar('f');
  EXPECT_FALSE(command.isReady());
}

TEST_F(Input_To_Command_Test, testFSpeedUp) {
  Input_To_Command command;
  command.acceptChar('f');
  command.acceptChar('f');
  command.acceptChar('w');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(45, 45, 0, 0);

  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testFStopElevator) {
  Input_To_Command command;
  command.acceptChar('e');
  command.acceptChar('f');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0,0,0,0);

  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testFRespectMax) {
  Input_To_Command command;
  for (int i = 0; i < 15; i++) {
    command.acceptChar('f');
  }
  command.acceptChar('w');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(100, 100, 0, 0);

  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testCNotReady) {
  Input_To_Command command;
  command.acceptChar('w');
  command.acceptChar('c');
  EXPECT_FALSE(command.isReady());
}

TEST_F(Input_To_Command_Test, testCSlowDown) {
  Input_To_Command command;
  command.acceptChar('f');
  command.acceptChar('f');
  command.acceptChar('c');
  command.acceptChar('w');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(40, 40, 0, 0);

  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testCStopElevator) {
  Input_To_Command command;
  command.acceptChar('e');
  command.acceptChar('c');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0,0,0,0);

  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testCRespectMin) {
  Input_To_Command command;
  command.acceptChar('f');
  for (int i = 0; i < 15; i++) {
    command.acceptChar('c');
  }
  command.acceptChar('w');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 0);

  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testE) {
  Input_To_Command command;
  command.acceptChar('e');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 2);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testEStopVel) {
  Input_To_Command command;
  command.acceptChar('w');
  command.acceptChar('e');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 2);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testEReady) {
  Input_To_Command command;
  command.acceptChar('e');
  EXPECT_TRUE(command.isReady());
}

TEST_F(Input_To_Command_Test, testR) {
  Input_To_Command command;
  command.acceptChar('r');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, -2);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testRStopVel) {
  Input_To_Command command;
  command.acceptChar('w');
  command.acceptChar('r');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, -2);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testRReady) {
  Input_To_Command command;
  command.acceptChar('r');
  EXPECT_TRUE(command.isReady());
}

TEST_F(Input_To_Command_Test, testQR) {
  Input_To_Command command;
  command.acceptChar('q');
  command.acceptChar('r');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, -1);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testQE) {
  Input_To_Command command;
  command.acceptChar('q');
  command.acceptChar('e');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 1);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testQNotReady) {
  Input_To_Command command;
  command.acceptChar('q');
  EXPECT_FALSE(command.isReady());
}

TEST_F(Input_To_Command_Test, testWReady) {
  Input_To_Command command;
  command.acceptChar('w');
  EXPECT_TRUE(command.isReady());
}

TEST_F(Input_To_Command_Test, testW) {
  Input_To_Command command;
  command.acceptChar('f');
  command.acceptChar('w');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(40, 40, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testWStopElevator) {
  Input_To_Command command;
  command.acceptChar('e');
  command.acceptChar('w');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testAReady) {
  Input_To_Command command;
  command.acceptChar('a');
  EXPECT_TRUE(command.isReady());
}

TEST_F(Input_To_Command_Test, testA) {
  Input_To_Command command;
  command.acceptChar('f');
  command.acceptChar('a');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(58, -18, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testAStopElevator) {
  Input_To_Command command;
  command.acceptChar('e');
  command.acceptChar('a');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testSReady) {
  Input_To_Command command;
  command.acceptChar('s');
  EXPECT_TRUE(command.isReady());
}

TEST_F(Input_To_Command_Test, testS) {
  Input_To_Command command;
  command.acceptChar('f');
  command.acceptChar('s');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(-8, -8, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testSStopElevator) {
  Input_To_Command command;
  command.acceptChar('e');
  command.acceptChar('s');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testDReady) {
  Input_To_Command command;
  command.acceptChar('d');
  EXPECT_TRUE(command.isReady());
}

TEST_F(Input_To_Command_Test, testD) {
  Input_To_Command command;
  command.acceptChar('f');
  command.acceptChar('d');
  
  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(-18, 58, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}

TEST_F(Input_To_Command_Test, testDStopElevator) {
  Input_To_Command command;
  command.acceptChar('e');
  command.acceptChar('d');

  Teleop_Command* t = command.getCommand();
  Teleop_Command expected(0, 0, 0, 0);
  EXPECT_TRUE(command_eq(t, &expected));
}
