# Makefile for the socket programming example
#

simple_server_objects = ServerSocket.o Socket.o simple_server_main.o
simple_client_objects = ClientSocket.o Socket.o simple_client_main.o 
destination_client_objects = ClientSocket.o Socket.o destination_client.o

all : simple_server simple_client destination_client

simple_server: $(simple_server_objects)
	g++ -o simple_server $(simple_server_objects)


simple_client: $(simple_client_objects)
	g++ -o simple_client $(simple_client_objects)

destination_client: $(destination_client_objects)
	g++ -o destination_client $(destination_client_objects)

Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
simple_server_main: simple_server_main.cpp
simple_client_main: simple_client_main.cpp
destination_client: destination_client.cpp

clean:
	rm -f *.o simple_server simple_client destination_client 
