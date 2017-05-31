#include <stdio.h>
#include <time.h>
#include "E101.h" //this is our custom ENGR101 C library.

//Global Variables
int whiteCount = 0;
int baseSpeed = 50;
int s = 0;// counts samples for integral calculation

int read_cam(int row){
	whiteCount = 0;
	int p, white, col = 0, sum = 0; //declare variables
	take_picture();

	for(int i=0; i<320 ; i++){ 	//Camera reading Near row
		white = get_pixel(row,col+i,3);
		if (white>120){
			p = 1; // for white
			whiteCount++; //increase global variable whiteCount
		} 
		else {
			p = 0; // for black
		}
		sum += (i-160)*p; //Gives the white a value that is centred at 0 (middle of picture)
	}

	return sum; //Return error signal;
}

double scale_pid(long pid, float motorGain){ //call scale passing pid signal and motor gain as input

	float scale = 0.005; // Needs tuning based on max PID output
	double temp; // Storeage variable for gain processing
	int output;

	if(pid * scale + baseSpeed> 250){ //Limiter
		temp = 250-baseSpeed; 
	}
	else if(pid * scale + baseSpeed < -250){
		temp = -250;
	}
	else{
		temp = (pid * scale); //scales PID and casts to int
	}
	output = temp*motorGain; //compensate for motor
	//printf("%d",output);
	return output;
}

long pid(double inNear,double inFar){ //call pid passing error signal as input
	float dGain = 0.85; //differential gain co-efficient
	float iGain = 0.05; //integral gain co-efficient
	float pGain = 0.5; //proportional gain co-efficient
	long errTotal = 0; //recent error signal input
	long diff; //differential
	long integ; //integral
	long prop; //proportional
	long PID;
	//int i = 0; //number of samples collected

	//errNew=input;
	//sleep1(0, 001); //this MUST equal dt

	//while(true){
		errTotal += inNear; // adds input to total - used inNear, this could change
		s++; 
		diff = (inFar-inNear)*dGain; //change from errNear to errFar * gain
		integ = ((errTotal)/s)*iGain; //Total Errors / sample count * gain
		prop = ((inNear+inFar)/2.0)*pGain; //Calculate proportional err - used inNear, this could change
		PID = prop+diff+integ; //Sum components
		return PID;
	//}
}

void goBack(int left, int right){

	set_motor(1, baseSpeed);
	set_motor(2, baseSpeed);
}

bool open_gate(){

	char ip[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};// 130.195.6.196
	char message[24] = {'P', 'l', 'e', 'a', 's', 'e'};
	char code[24];

	connect_to_server(ip,1024);
	printf("ip: %s\n",ip);
	send_to_server(message);  
	printf("message to server: %s\n",message);
	receive_from_server(code);
	printf("code received from server: %s___Sending to Server\n", code);
	send_to_server(code);
	//sleep1(0, 1); delay if needed
	return true;
}


int main(){
	init(); //initialise gpio
	bool cam = true;
	double errNear;
	double errFar; 
	long errPID;
	int driveLeft;
	int driveRight;
	//int joe = 0;
	int t = 0;//counts main() loop in s/100
	int lost = 0;
	
	//sleep1(20, 0);
	bool go = open_gate();
	sleep1(1, 0);
	while(go){
		
		//cam = set_mode();
		/* whiteCount = whiteCount/2; // averages the two whitecount readings
		 * if(whiteCount<3){
		 * panic();
		 * }
		 * if(whiteCount>212){ //212 is 2/3rds of frame width
		 * turnLeft();
		 * }
		 * whiteCount = 0; // reset whitecount for next tick
		**/
		//display_picture(1, 0);
		if(cam==true){
			errNear = read_cam(80);
			errFar = read_cam(160);
		}
		else{
			//read_ir(); //write processes for this
		}
		errPID = pid(errNear,errFar);
		
		driveLeft = scale_pid(errPID, 1); // tune gain L
		driveRight = scale_pid(errPID, 1); // tune gain R
		
		

		if(t%50==0){
			printf("t=%f___errNear: %f ___errFar: %f ___PID: %f\n", t, errNear, errFar, errPID);
		}
		
		if(whiteCount < 3){
			lost++;
			goBack(driveLeft, driveRight);
			sleep1(0, 020000);
			t+=2;
			printf("Back: %f___%f\n", driveLeft, driveRight);
			if(lost>10){
				goBack(driveLeft, driveRight);
				sleep1(0, 030000);
				lost=0;
				printf("LOST %f___%f\n", driveLeft, driveRight);
				t+=3;
			}
		}
		else{
			set_motor(2, -baseSpeed+driveLeft);
			set_motor(1, -baseSpeed-driveRight);
		sleep1(0, 010000);
		t++;
		}
		
		//joe++;
		}
		stop(0);
return 0;
}
