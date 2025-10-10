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
int speed;
int radius;
double w=0.785;//angular velocity
int b=230; //distance between the kobuki wheels
char buffer[5]={0};
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
					speed=0;
					radius=0;
				}else{
					if(event.number==8 && event.value==1){
						Close=true;
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
						speed=(int)((w*b)/2);
						radius=1;
					cout<<"left turn done"<<endl;
				}
					else{ if(event.value==32767){
						//movement((int)((w*b)/2),-1);
						speed=(int)((w*b)/2);
						radius=-1;
					cout<<"right turn done"<<endl;
					}
				}
				}else{
					if(event.number==7){
					if(event.value==-32767){
						//movement(100,0);
						speed=100;
						radius=0;
					cout<<"moved forward"<<endl;
				}
					else{ if(event.value==32767){
						//movement(-100,0);
						speed=-100;
						radius=0;
					cout<<"moved backwards"<<endl;
					}
				}
				}
				}
			}

				
		}

	
		/*Convert the event to a useable data type so it can be sent*/
		 buffer[0] = speed & 0xff;	//Byte 5: Payload Data: Speed(mm/s)
	     buffer[1] = (speed >> 8) & 0xff; //Byte 6: Payload Data: Speed(mm/s)
		 buffer[2] = radius & 0xff;	//Byte 7: Payload Data: Radius(mm)
		 buffer[3] = (radius >> 8) & 0xff;	//Byte 8: Payload Data: Radius(mm)
		/*Print the data stream to the terminal*/
		cout<<"byte 1:"<<buffer[0]<<"byte 2:"<<buffer[1]<<"byte 3:"<<buffer[2]<<"byte 4:"<<buffer[4]<<endl;
		/*Send the data to the server*/
		send(sock,&buffer,sizeof(buffer),0);
		cout<<"Command sent"<<endl;
		if(Close) {
		/*Closes out of all connections cleanly*/

		//When you need to close out of the connection, please
		//close TTP/IP data streams.
		//Not doing so will result in the need to restart
		//the raspberry pi and Kobuki
			close(sock);
			exit(0);

		/*Set a delay*/
		usleep(500000);
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
	if(inet_pton(AF_INET, "XX.XX.XX.XX" , &serv_addr.sin_addr) <= 0){
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\nConnection Failed \n");
		return -1;
	}
	return 0;
}

