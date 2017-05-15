#include <stdio.h>
#include <time.h>
#include "E101.h" //this is our custom ENGR101 C library.

void main()
bool cam = true;
double errNear;
double errFar;
double errPID;
int driveLeft;
int driveRight;

while(true){
cam = set_mode()
if(cam=true){
	near = read_cam();
	far = read_cam();
}
else{
	read_ir(); //write processes for this
}
errPID = pid(errNear, errFar);
driveLeft = scale_pid(errPID, 0.95); // tune gain L
driveRight = scale_pid(errPID, 1); //tune gain R

set_motor(0, driveLeft);
set_motor(1, driveRight);

}
