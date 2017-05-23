/*******************************************************************************

driver_test.cpp

Unit tests for driver_test.cpp. Tests that internal state of Driver object
is appropriately changed with each Teleop_Command. If PI were defined,
the internal state would then be used to power the robot.

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

#include "driver.hpp"
#include "teleop_command.hpp"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

class Driver_Test : public::testing::Test {

};

TEST_F(Driver_Test, testVelsWithinBounds) {

}

TEST_F(Driver_Test, testDelay) {

}

TEST_F(Driver_Test, testDelayDiff) {

}

TEST_F(Driver_Test, testDelayRem) {

}
