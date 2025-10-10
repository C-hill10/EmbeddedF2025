//Use g++ joystick.cc -std=c++11 -o Lab3EX3B Lab3EX3B.cpp

#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include "joystick.hh"
#include <cstdlib>
#define  PORT 8080
using namespace std;

int createSocket();
bool Close=false;
int sock = 0;
int speed=0;
int radius=0;
double w=0.785;//angular velocity
int b=230; //distance between the kobuki wheels
char Ctrl;
int main(int argc, char const *argv[]){
	
	//Open the file stream for the joystick
	Joystick joystick("/dev/input/js0");
	JoystickEvent event;
	if(!joystick.isFound()){
		cout << "Error opening joystick" << endl;
		exit(1);
	}


	//Create the connection to the server
	createSocket();

	while(true){

		/*Sample the events from the joystick*/
		if (joystick.sample(&event))
		{
			if (event.isButton())
			{
				printf("isButton: %u | Value: %d\n", event.number, event.value);
				/*Interpret the joystick input and use that input to move the Kobuki*/
				if(event.number==7 && event.value==1){
					//stopKobuki();
					Ctrl='S';
				}else{
					if(event.number==8 && event.value==1){
						Close=true;
						Ctrl='C';
						cout<<"kobuki has been closed"<<endl;
						break;
					}
				}
				
			}
			if (event.isAxis())
			{
				printf("isAxis: %u | Value: %d\n", event.number, event.value);
				/*Interpret the joystick input and use that input to move the Kobuki*/
				if(event.number==6){
					 if(event.value==-32767){
						//movement((int)((w*b)/2),1);
						Ctrl='L';
					cout<<"left turn done"<<endl;
				}
					else{ if(event.value==32767){
						//movement((int)((w*b)/2),-1);
						Ctrl='R';
					cout<<"right turn done"<<endl;
					}
				}
				}else{
					if(event.number==7){
					if(event.value==-32767){
						//movement(100,0);
						Ctrl='F';
					cout<<"moved forward"<<endl;
				}
					else{ if(event.value==32767){
						//movement(-100,0);
					    Ctrl='B';
					cout<<"moved backwards"<<endl;
					}
				}
				}
				}
			}
			/*Convert the event to a useable data type so it can be sent*/
		   cout<<"sending Control "<<Ctrl<<endl;
		   /*Send the data to the server*/
		   send(sock,&Ctrl,sizeof(Ctrl),0);
		   cout<<"Command sent"<<endl;
		   usleep(20000);
		}

	
		if(Close){
		/*Closes out of all connections cleanly*/
			cout<<"running close connection"<<endl;
		//When you need to close out of the connection, please
		//close TTP/IP data streams.
		//Not doing so will result in the need to restart
		//the raspberry pi and Kobuki
		sleep(1);
			close(sock);
			exit(0);

		/*Set a delay*/
		usleep(20);
	}
}
	return 0;
}

//Creates the connection between the client and
//the server with the controller being the client
int createSocket(){
	struct sockaddr_in address;
	struct sockaddr_in serv_addr;

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\nSocket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port   = htons(PORT);

	/*Use the IP address of the server you are connecting to*/
	if(inet_pton(AF_INET, "10.227.22.73" , &serv_addr.sin_addr) <= 0){
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\nConnection Failed \n");
		return -1;
	}
	return 0;
}

