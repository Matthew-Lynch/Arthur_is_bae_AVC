double pid(double inNear, double inFar){ //call pid passing error signal as input
	//double dt = 0.001 //time step in s
	float dGain = 0.5; //differential gain co-efficient
	float iGain = 0.5; //integral gain co-efficient
	float pGain = 0.5; //proportional gain co-efficient
	double errTotal = 0; //recent error signal input
	//double errNew; //error signal input from dt ago
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
	//sleep1(0, 001); //this MUST equal dt
	prop = inNear*pGain; //Calculate proportional err - used inNear, this could change
	PID = prop+diff+integ; //Sum components
	return PID;
}
}
