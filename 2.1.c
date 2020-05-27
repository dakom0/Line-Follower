/*Damillola Komolafe*/
/*EEGR 409*/
/*Dr. Nyarko*/
/*Project 1.4-b*/

#include <stdio.h>
#include <wiringPi.h>
#include <string.h>

int main()
{


	unsigned int stime = 0;
	unsigned int rtime = 0;
	float period = .1;
	int dutycycle = 30;
	/*int duration = 20;*/
	int high;
	int low;
	int LeftSensorCount = 0;
	int RightSensorCount = 0;

	wiringPiSetup();


	pinMode(1, OUTPUT); // physical header pin 11
	pinMode(4, OUTPUT); // physical header pin 15
	pinMode(0, INPUT);  // physical header pin 16, Right Sensor
	pinMode(2, INPUT);  // physical header pin 18, Left Sensor


	high = (period * 1000) * (dutycycle / 100.0);
	low = (period * 1000) - high;



	rtime = millis();

	do

	{
		// Increment sensor and count when it is on the line reset otherwise,
		// 0 means white:low and 1 means black:high

		if (digitalRead(0) == HIGH) ++RightSensorCount;
		else RightSensorCount = 0;

		if (digitalRead(2) == HIGH) ++LeftSensorCount;
		else LeftSensorCount = 0;

		// move wheels foreward
		printf("Drive Forward\n\n");
		digitalWrite(4, HIGH); //left wheel
		digitalWrite(1, HIGH); // right wheel 
		stime = millis();
		while (millis() - stime < high);
		digitalWrite(4, LOW);
		digitalWrite(1, LOW);
		stime = millis();
		while (millis() - stime < low);

		//if the left is > 1 and right > 1 then stay straight
		//if the left sensor < 1 but right > 1 turn right
		//if the left sensor > 1 but right < 1 turn left

		if (LeftSensorCount > 1 && RightSensorCount > 1)
		{
			digitalWrite(0, LOW);
			digitalWrite(2, LOW);
			printf(" line found");
			break;
		}

		if (LeftSensorCount < 1 && RightSensorCount > 1)
		{
			printf("Left\n\n");
			digitalWrite(4, HIGH); // left wheel
			digitalWrite(1, LOW); // right wheel 
			stime = millis();
			while (millis() - stime < high);
			digitalWrite(4, HIGH);
			digitalWrite(1, LOW);
			stime = millis();
			while (millis() - stime < low);
		}

		else if (LeftSensorCount > 1 && RightSensorCount < 1)
		{
			printf("Right\n\n");
			digitalWrite(4, LOW); //left wheel
			digitalWrite(1, HIGH); // right wheel 
			stime = millis();
			while (millis() - stime < high);
			digitalWrite(4, LOW);
			digitalWrite(1, HIGH);
			stime = millis();
			while (millis() - stime < low);
		}





	} while (millis());//-rtime) < duration*1000);


	return 0;

}

