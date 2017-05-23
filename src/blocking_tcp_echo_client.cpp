//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <ncurses.h>

#include "teleop_command.hpp"
#include "input_to_command.hpp"

using boost::asio::ip::tcp;

enum { max_length = 1024 };

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
