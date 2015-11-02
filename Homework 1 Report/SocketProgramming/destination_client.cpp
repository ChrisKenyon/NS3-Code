#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include "hw1helper.h"

int main ( int argc, char* argv[] )
{
  if (useUDP)
  {
   sockaddr_in servAddr;
   sockaddr_in thisAddr;

   int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   thisAddr.sin_family = AF_INET;
   thisAddr.sin_port = htons(PORT_TWO);
   thisAddr.sin_addr.s_addr = inet_addr(DESTINATION);
  
   bind (sock, (struct sockaddr*)&thisAddr, sizeof(thisAddr));

   servAddr.sin_family = AF_INET;
   servAddr.sin_port = htons(PORT_TWO);
   servAddr.sin_addr.s_addr = inet_addr(SERVER); 
   
   unsigned char buffer[256];
   socklen_t myAddrLen = sizeof(thisAddr);

   std::cout<<"I'm looking for a packet!\n";
   int len = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&servAddr, &myAddrLen);
   std::cout<<"I, the destination client, received a packet!\n";
   
   sendto(sock, buffer, len, 0, (struct sockaddr*)&servAddr, myAddrLen);   
   std::cout<<"I, the destination client, sent a packet!\n";
   
   close(sock);
  }

  // TCP PART
  else
  {
 
   try
    {
      ClientSocket destination_socket ( SERVER, PORT_TWO );

      std::string message;

      try
	{
	   std::cout<<"reading... ";
	   destination_socket >> message;
 	  
	   std::cout << "Destination client received message from server:\n\"" << message << "\"\n";
	   message = "Not much client socket!";
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
  }
  return 0;
}
