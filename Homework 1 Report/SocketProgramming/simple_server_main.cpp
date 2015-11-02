#include "ServerSocket.h"
#include "SocketException.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include "hw1helper.h"

int main ( int argc, char* argv[] )
{
 // bool directEcho = false;
 // bool useUDP = true;
  std::cout << "running....\n";
  

  // UDP CODE
  if (useUDP)
  {
   // DIRECT ECHO PART
   if (directEcho)
   {
    struct sockaddr_in clientAddr;
    struct sockaddr_in thisAddr;

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    thisAddr.sin_family = AF_INET;
    thisAddr.sin_port = htons(PORT_TWO);
    thisAddr.sin_addr.s_addr = htonl(INADDR_ANY);
   
    bind (sock, (struct sockaddr*)&thisAddr, sizeof(thisAddr));

    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(PORT_TWO);
    clientAddr.sin_addr.s_addr = INADDR_ANY; 
    
    unsigned char buffer[256];
    socklen_t myAddrLen = sizeof(thisAddr);
   
    while(true)
    {
        int len = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&clientAddr, &myAddrLen);
        sendto(sock, buffer, len, 0, (struct sockaddr*)&clientAddr, myAddrLen); 
    }
   }

   // RELAY PART
   else if (!directEcho)
   {
     struct sockaddr_in clientAddr;
     struct sockaddr_in thisAddr;
     struct sockaddr_in destAddr;

     int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

     thisAddr.sin_family = AF_INET;
     thisAddr.sin_port = htons(PORT_TWO);
     thisAddr.sin_addr.s_addr = inet_addr(SERVER);
   
     bind (sock, (struct sockaddr*)&thisAddr, sizeof(thisAddr));

     clientAddr.sin_family = AF_INET;
     clientAddr.sin_port = htons(PORT_TWO);
     clientAddr.sin_addr.s_addr = inet_addr(CLIENT);  

     destAddr.sin_family = AF_INET;
     destAddr.sin_port = htons(PORT_TWO);
     destAddr.sin_addr.s_addr = inet_addr(DESTINATION); 

     unsigned char buffer[2048];
     socklen_t myAddrLen = sizeof(thisAddr);
   
     while(true)
     {
         int len = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&clientAddr, &myAddrLen);
     	 std::cout<<"I got the first packet from the client!\n";
  	  
         sendto(sock, buffer, len, 0, (struct sockaddr*)&destAddr, sizeof(destAddr)); 
	 std::cout<<"I sent a packet to the destination!\n";
         int len2 = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&destAddr, &myAddrLen);
         
     	 std::cout<<"I got a packet from the destination!\n";
	 
	 sendto(sock, buffer, len2, 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr)); 
     	 std::cout<<"I sent a packet to the client!\n";
    }

   }
  } 

  // TCP PART
  else 
  {
  try
    {
      // Create the socket
      ServerSocket server_sock1 ( PORT_ONE );
      ServerSocket server_sock2 ( PORT_TWO );   
      while ( true )
	{

	  ServerSocket client_sock;
	  server_sock1.accept ( client_sock );
	  
          ServerSocket dest_sock;
          
	  if (!directEcho)
   	  {
	     server_sock2.accept (dest_sock);
	  }

	  try
	  {
              if (!directEcho)
	      {
	        while ( true )
		{
		    std::string data; 
		    std::cout << "Receiving from client\n";  
	      	    client_sock >> data;

		    std::cout << "Sending to destination\n";
		    dest_sock <<  data;
		  
		    std::cout << "Receiving from destination\n";
                    dest_sock >> data;
	
		    std::cout << "Sending back to client\n";
                    client_sock << data;
	        }
	      }
	      else if (directEcho)
              {
                while(true)
	        {
		   std::string data;
  		   std::cout << "Receiving from client\n";
		   client_sock >> data;

		   std::cout << "Echoing back to the client\n";
		   client_sock << data;
		}
              }
	  }
	    catch ( SocketException& ) {}
          }
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
  }

  return 0;
}
