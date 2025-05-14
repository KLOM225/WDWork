#include "Acceptor.hpp"
#include "TcpConnection.hpp"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
 
int main(void)
{
	//Acceptor acceptor("192.168.30.129", 8000);
	Acceptor acceptor(8000);
	acceptor.ready();
	cout << "connecting" << endl;
	TcpConnection conn(acceptor.accept());
	cout << conn.toString() << " has connected!" << endl;
	conn.send("welcome to server.");
	printf("> recv client data:\n");
	cout << conn.receive() << endl;

	return 0;
}

