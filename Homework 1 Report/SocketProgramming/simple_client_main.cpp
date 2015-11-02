#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/socket.h>
#include "hw1helper.h"

timeval my_time;
double duration;

int main ( int argc, char* argv[] )
{
  if (useUDP)
  {
   sockaddr_in servAddr;
   sockaddr_in thisAddr;

   char *msg = "Testing UDP"+ '\0';
   int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   thisAddr.sin_family = AF_INET;
   thisAddr.sin_port = htons(PORT_TWO);
   thisAddr.sin_addr.s_addr = inet_addr(CLIENT);
   
   servAddr.sin_family = AF_INET;
   servAddr.sin_port = htons(PORT_TWO);
   servAddr.sin_addr.s_addr = inet_addr(SERVER); 
   
   unsigned char buffer[256];
   socklen_t myAddrLen = sizeof(thisAddr);

   gettimeofday(&my_time, NULL);
   double send_time = my_time.tv_usec;
   sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr*)&servAddr, sizeof(servAddr));   
   recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&servAddr, &myAddrLen);
   gettimeofday(&my_time, NULL);
   duration = my_time.tv_usec - send_time;
   
   printf("Received message from server: %s AND it took:  %f usec \n",buffer, duration);  
  }
  else
  {

  try
     {
      ClientSocket client_socket (SERVER, PORT_ONE);

      std::string reply;

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
  }

  return 0;
}
