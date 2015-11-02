#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/time.h>

int main ( int argc, char* argv[] )
{
  try
    {
std::cout<<"test";
      ClientSocket client_socket ( "localhost", 30000 );

      std::string reply;
      timeval my_time;
      double duration;

      try
	{
	  gettimeofday(&my_time, NULL);
          double send_time = my_time.tv_usec;
	  client_socket << "What's up destination socket?";
	  client_socket >> reply;
	  gettimeofday(&my_time, NULL);
	  duration = my_time.tv_usec - send_time;
	}
      catch ( SocketException& ) {}

      std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;
      printf("Sending took %.2lf microseconds\n",duration);
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
