#include <stdio.h>
#include <time.h>
#include "E101.h" //this is our custom ENGR101 C library.

//Global Variables
int whiteCount = 0;
int baseSpeed = 70;


int read_cam(int row){
	int sum, p, white, col = 0, sum = 0; //declare variables
	take_picture();

	for(int i=0; i<320 ; i++){ 	//Camera reading Near row
		white = get_pixel(col+i,row,3);
		if (white>127){
		p = 1; // for white
		whiteCount++; //increase global variable whiteCount
		} 
		else {
		p = 0; // for black
		}
		sum = sum + (i-160)*p; //Gives the white a value that is centred at 0 (middle of picture)
		}
		
	return sum; //Return error signal;
}

double scale_pid(double pid, float motorGain){ //call scale passing pid signal and motor gain as input
	float scale = 0.2; // Needs tuning based on max PID output
	double temp; // Storeage variable for gain processing
	int output;
	
	if(pid * scale > 254){ //Limiter
		temp = 254; 
	}
	else{
		temp = (pid * scale); //scales PID and casts to int
	}
	output = temp*motorGain; //compensate for motor
	//printf("%d",output);
	return output;
}

double pid(double inNear,double inFar){ //call pid passing error signal as input
	float dGain = 1.0; //differential gain co-efficient
	float iGain = 0.1; //integral gain co-efficient
	float pGain = 0.3; //proportional gain co-efficient
	double errTotal = 0; //recent error signal input
	double diff; //differential
	double integ; //integral
	double prop; //proportional
	double PID;
	int i = 0; //number of samples collected

	//errNew=input;
	//sleep1(0, 001); //this MUST equal dt

	while(true){
		errTotal += inNear; // adds input to total - used inNear, this could change
		i++; 
		diff = ((inNear-inFar)/2)*dGain; //change from errNear to errFar * gain
		integ = ((errTotal)/i)*iGain; //average err * time step * gain
		prop = inNear*pGain; //Calculate proportional err - used inNear, this could change
		PID = prop+diff+integ; //Sum components
		return PID;
	}
}



int main(){
	init();
	bool cam = true;
	double errNear;
	double errFar; 
	double errPID;
	int driveLeft;
	int driveRight;
	
	while(true){
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
		if(cam==true){
			errNear = read_cam(160);
			errFar = read_cam(80);
		}
		else{
			//read_ir(); //write processes for this
		}
		errPID = pid(errNear,errFar);
		driveLeft = scale_pid(errPID, 1); // tune gain L
		driveRight = scale_pid(errPID, 1); // tune gain R

		set_motor(0, baseSpeed+driveLeft);
		set_motor(1, baseSpeed+driveRight);
		//sleep1(0, 000010); //sleep code for stability?
		}
return 0;
}
