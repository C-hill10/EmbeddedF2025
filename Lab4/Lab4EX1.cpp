//Use g++ -std=c++11 -o Lab4EX1 Lab4EX1.cpp -lwiringPi

#include <string>
#include <iostream>
#include <wiringSerial.h>
#include <wiringPi.h>
#include <unistd.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

int kobuki;

int main(){
	wiringPiSetup();
	kobuki = serialOpen("/dev/kobuki", 115200);
	unsigned int bumper;
	unsigned int drop;
	unsigned int cliff;
	unsigned int button;
	unsigned int read;

	while(serialDataAvail(kobuki) != -1){

		while(true){
		//If the bytes are a 1 followed by 15, then we are
		//parsing the basic sensor data packet
			read = serialGetchar(kobuki);
			if(read == 1){
				if(serialGetchar(kobuki) == 15) break;
			}
		}

		//Read past the timestamp
		serialGetchar(kobuki);
		serialGetchar(kobuki);

		/*Read the bytes containing the bumper, wheel drop,
			and cliff sensors. You can convert them into a usable data type.*/
		char bumper=serialGetchar(kobuki);
		char drop=serialGetchar(kobuki);
		char cliff= serialGetchar(kobuki);
		/*Print the data to the screen.*/
		cout<<"Left bumper ="<<(bumper&0x01)<<" Center bumper ="<<(bumper&0x02)<<" Right bumper = "<<(bumper&0x04)<<endl;
		cout<<"Left wheel ="<<(drop&0x01)<<" Center wheel ="<<(drop&0x02)<<" Right wheel = "<<(drop&0x04)<<endl;
		cout<<"Left cliff ="<<(cliff&0x01)<<" Center cliff ="<<(cliff&0x02)<<" Right cliff = "<<(cliff&0x04)<<endl;
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
		if(button & 0x02){
			serialClose(kobuki);
			break;
		}

		serialGetchar(kobuki);
		serialGetchar(kobuki);
		serialGetchar(kobuki);

		//Pause the script so the data read receive rate is the same as the Kobuki send rate.
		usleep(20000);
			
		
	}

	return(0);
}
