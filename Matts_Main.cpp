#include <stdio.h>
#include <time.h>
#include "E101.h"

int p = 0;
int kp = 320;
int whiteNum = 0;
int speedScale = 1;

int generateError(){
	take_picture();
	p = 0;
	for(int i = 0; i<320; i++){
		//printf("%i", i);		
		if(get_pixel(80, i, 3)>50){ 
			p += (i-160);
			whiteNum++;
			}
		}
	return p/kp;
}

int main(){
	init();
	//display_picture(1, 1);
	int count = 0;
	int a = 0;
	int b = 0;
	while (count < 2000){
		int joe = generateError();
		printf("%i\n", joe);
		//display_picture(1,1);
		if(joe > -2 || joe <2){
			a = 100;
			b = 100;
		}
		if(joe>0){
			a = 100;
			b = joe;
		}
		else{
			a = joe;
			b = 100;
		}
		set_motor(1, 100);
		set_motor(2, 100);
		sleep1(0, 50);
		set_motor(1, b/speedScale);
		set_motor(2, a/speedScale);
		sleep1(0, 25);
		count++;
	}
	stop(0);
	return (0);
}
