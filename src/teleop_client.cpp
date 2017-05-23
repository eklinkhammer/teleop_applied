/*******************************************************************************

teleop_client.cpp

Client accepts user input, converts the input to a Teleop_Command, and 
streams the command to the server. Based on boost example code.

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

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <ncurses.h>

#include "teleop_command.hpp"
#include "input_to_command.hpp"

using boost::asio::ip::tcp;

enum { max_length = 1024 };

/*
  Sends a serialized version of Teleop_Command t to host:port. Writes the
    response in reply.
 */
void send_command(char* reply,
		  const Teleop_Command t, const char* host, const char* port) {

  std::ostringstream os;
  {
    boost::archive::text_oarchive oa(os);
    oa << t;
  }

  std::string outbound_data = os.str();
  const char* message = outbound_data.c_str();

  boost::asio::io_service io_service;

  tcp::socket s(io_service);
  tcp::resolver resolver(io_service);
  boost::asio::connect(s, resolver.resolve({host, port}));

  size_t message_length = std::strlen(message);

  boost::asio::write(s, boost::asio::buffer(message, message_length));

  boost::asio::read(s,
      boost::asio::buffer(reply, message_length));
}

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }

    Input_To_Command commander;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    char ch = 0;
    char reply[max_length];
    
    while (true) {
      ch = getch();
      switch (ch) {
      case 'P':
      case 'p':
	endwin();
	std::cout << "Good bye" << std::endl;
	return 0;
	break;
      default:
	commander.acceptChar(ch);
	if (commander.isReady()) {
	  Teleop_Command* t = commander.getCommand();
	  send_command(reply, *t, argv[1], argv[2]);
	  delete t;
	}
	break;
      }
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
