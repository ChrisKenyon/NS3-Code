#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char* argv[] )
{
  try
    {
      std::cout<<"test";
      ClientSocket destination_socket ( "localhost", 30000 );

      std::string message;

      try
	{
	   std::cout<<"reading... shit";
	   destination_socket >> message;
 	   message = "eat my balls";
	   std::cout << "Destination client received message from server:\n\"" << message << "\"\n";
	   destination_socket << message;
	}
      catch ( SocketException& ) {}

      std::cout << "Destination client is relaying message back to the server\n"
;
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
