//use g++ -std=c++11 -o Lab4EX2 Lab4EX2.cpp -lwiringPi


#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;
using namespace std::chrono;
int b=230; //distance between the kobuki wheels
double w=0.785;//angular velocity
void stopKobuki();
int kobuki;
float read_sonar();
void movement(int, int);
bool turn =false;
int main(){
	wiringPiSetup();
	kobuki = serialOpen("/dev/kobuki", 115200);

	/*Move from a random point within the area designated "X" to the
	point B as shown on the diagram. Use a sonar sensor to navigate through the channel.
	You can reuse your code from Lab 2 and 3*/
	while(true){
		float distance= read_sonar();
		if(distance>20){
			movement(200,0);
			usleep(20000);
		}else{
			if(!turn){
				stopKobuki();
				for(int i=0;i<66;i++){
					movement((int)(w*b)/2,-1);
					turn=true;
					usleep(20000);
				} 
			}else {
				stopKobuki();
				for(int i=0;i<67;i++){
					movement((int)(w*b)/2,1);
					usleep(20000);
				}
			}
		}
	}
	/*Note: the Kobuki must completely pass point B as shown to receive full credit*/


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