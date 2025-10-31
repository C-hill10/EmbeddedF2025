//Use g++ -std=c++11 -o Lab4EX3 Lab4EX3.cpp -lwiringPi

#include <string>
#include <iostream>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <unistd.h>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;
using namespace std::chrono;
int kobuki;
int b=230; //distance between the kobuki wheels
double w=0.785;//angular velocity
unsigned int bumper;
unsigned int drop;
unsigned int cliff;
unsigned int button; 
bool Rbump;
bool Lbump;
bool Cbump;
bool Lwheel;
bool Rwheel;
bool Rcliff;
bool Ccliff;
bool Lcliff;
void movement(int, int);
void readData();
void turnRight();
void turnLeft();
void stopKobuki();
float read_sonar();
void dontFall();
void helpMeeeeeee();
void dontCorner();
int main(){
	//Create connection to the Kobuki
	wiringPiSetup();
	kobuki = serialOpen("/dev/kobuki", 115200);

	while(serialDataAvail(kobuki) != -1){
		readData();
		float distance = read_sonar();
		/*Read the initial data. If there are no flags,
		the default condition is forward.*/
		bool tooClose = (distance<20);
		if(Rbump || Lbump || Cbump|| Lwheel || Rwheel ||Rcliff || Ccliff || Lcliff || tooClose){
			if(Ccliff||Rcliff||Lcliff){
				dontFall();
			}
			if(tooClose){
				if((rand()%2)==1){
					turnRight();
				}else{
					turnLeft();
				}
			}
			if(Rbump||Lbump||Cbump){
				dontCorner();
			}
			if(Lwheel ||Rwheel){
				helpMeeeeeee();
			}
			
			
		}else{
		/*Move slowly to give the sensors enough time to read data,
		the recommended speed is 100mm/s*/
		movement(100,0);
		usleep(20000);
		}
		/*Create different states as to satisfy the conditions above.
		Remember, a single press of a bumper may last longer
		than one data cycle.*/

		/*Cleanly close out of all connections using Button 1.*/

		/*Use serialFlush(kobuki) to discard all data received, or waiting to be send down the given device.*/
	}
}

void movement(int sp, int r){

	//Create the byte stream packet with the following format:
	unsigned char b_0 = 0xAA; /*Byte 0: Kobuki Header 0*/
	unsigned char b_1 = 0x55; /*Byte 1: Kobuki Header 1*/
	unsigned char b_2 = 0x06; /*Byte 2: Length of Payload*/
	unsigned char b_3 = 0x01; /*Byte 3: Sub-Payload Header*/
	unsigned char b_4 = 0x04; /*Byte 4: Length of Sub-Payload*/

	unsigned char b_5 = sp & 0xff;	//Byte 5: Payload Data: Speed(mm/s)
	unsigned char b_6 = (sp >> 8) & 0xff; //Byte 6: Payload Data: Speed(mm/s)
	unsigned char b_7 = r & 0xff;	//Byte 7: Payload Data: Radius(mm)
	unsigned char b_8 = (r >> 8) & 0xff;	//Byte 8: Payload Data: Radius(mm)
	unsigned char checksum = 0;		//Byte 9: Checksum
	
	//Checksum all of the data
	char packet[] = {b_0,b_1,b_2,b_3,b_4,b_5,b_6,b_7,b_8};
	for (unsigned int i = 2; i < 9; i++)
		checksum ^= packet[i];

	/*Send the data (Byte 1 - Byte 9) to Kobuki using serialPutchar (kobuki, );*/
	serialPutchar(kobuki,b_0);
	serialPutchar(kobuki,b_1);
	serialPutchar(kobuki,b_2);
	serialPutchar(kobuki,b_3);
	serialPutchar(kobuki,b_4);
	serialPutchar(kobuki,b_5);
	serialPutchar(kobuki,b_6);
	serialPutchar(kobuki,b_7);
	serialPutchar(kobuki,b_8);
	serialPutchar(kobuki,checksum);


	/*Pause the script so the data send rate is the
	same as the Kobuki data receive rate*/
	usleep(20000);
}
void stopKobuki() {
    movement(0, 0); // Send zero speed to stop
    usleep(100000); // Wait for 100 ms to ensure the stop command is received
}
void readData(){
		//If the bytes are a 1 followed by 15, then we are
		//parsing the basic sensor data packet
		unsigned int read;
			read = serialGetchar(kobuki);
			if(read == 1){
				if(serialGetchar(kobuki) == 15){ 
			

		//Read past the timestamp
		serialGetchar(kobuki);
		serialGetchar(kobuki);

		/*Read the bytes containing the bumper, wheel drop,
			and cliff sensors. You can convert them into a usable data type.*/
		char bumper=serialGetchar(kobuki);
		char drop=serialGetchar(kobuki);
		char cliff= serialGetchar(kobuki);
		/*Print the data to the screen.*/
		 Rbump = (bumper)&0x01;
		 Lbump = (bumper &0x04);
		 Cbump = (bumper&0x02);
		 Lwheel = (drop&0x02);
		 Rwheel = (drop&0x01);
		 Rcliff = ((cliff)&0x01);
		 Ccliff = (cliff&0x02);
		 Lcliff = (cliff&0x04);
		cout<<"Right bumper ="<<Rbump<<" Center bumper ="<<Cbump<<" Left bump = "<<Lbump<<endl;
		cout<<"Left wheel ="<<Lwheel<<" Right wheel = "<<Rwheel<<endl;
		cout<<"Right cliff ="<<Rcliff<<" Center cliff ="<<Ccliff<<" Left cliff = "<<Lcliff<<endl;
		/*Read through 6 bytes between the cliff sensors and
		the button sensors.*/
		serialGetchar(kobuki);
		serialGetchar(kobuki);
		serialGetchar(kobuki);
		serialGetchar(kobuki);
		serialGetchar(kobuki);
		serialGetchar(kobuki);
		/*Read the byte containing the button data.*/
		char button = serialGetchar(kobuki);
		/*Close the script and the connection to the Kobuki when
		Button 1 on the Kobuki is pressed. Use serialClose(kobuki);*/
		if((button >> 1) && 0x01){
			serialClose(kobuki);
		}

		serialGetchar(kobuki);
		serialGetchar(kobuki);
		serialGetchar(kobuki);

		//Pause the script so the data read receive rate is the same as the Kobuki send rate.
		usleep(20000);
			
		
	}
}

}
void turnRight(){
	stopKobuki();
for(int i=0;i<66;i++){
movement((int)(w*b)/2,-1);
usleep(20000);
}
}
void turnLeft(){
stopKobuki();
for(int i=0;i<67;i++){
movement((int)(w*b)/2,1);
usleep(20000);
}
}
float read_sonar()
{
    pinMode(1,OUTPUT);
    digitalWrite(1,LOW);
    usleep(2);
    digitalWrite(1,HIGH);
    usleep(5);
    digitalWrite(1,LOW);
    /*Echo holdoff delay 750 us*/
    usleep(750);


    /*Switch the pinMode to input*/ 
    pinMode(1,INPUT);
    
    
    /*Get the time it takes for signal to leave sensor and come back.*/

    // 1. defind a varable to get the current time t1. Refer to "High_Resolution_Clock_Reference.pdf" for more information
    auto t1 = high_resolution_clock::now();
    int pulse_width;
    while(digitalRead(1))
    {
        // 2. defind a varable to get the current time t2.
        auto t2 = high_resolution_clock::now();
        // 3. calculate the time duration: t2 - t1
        pulse_width = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        if (pulse_width >= 18500){
            break;
        }
        
        // 4. if the duration is larger than the Pulse Maxium 18.5ms, break the loop.
    }



    /*Calculate the distance by using the time duration that you just obtained.*/ //Speed of sound is 340m/s
    float distance = (pulse_width/2.0) *(343)/10000;

    /*Delay before next measurement. The actual delay may be a little longer than what is shown is the datasheet.*/
    usleep(250);
    return distance;
}
void dontFall(){
while(Ccliff||Rcliff||Lcliff){
	turnRight();
	readData();
}
}
void dontCorner(){
	stopKobuki();
	if(Rbump){
		turnLeft();
	}else if(Lbump){
	turnRight();
	}
	else if(Cbump){
		turnRight();
		turnRight();
	}
	else{
		helpMeeeeeee();
	}
		
	}
void helpMeeeeeee(){
	stopKobuki();
	serialFlush(kobuki);
	serialClose(kobuki);
}
