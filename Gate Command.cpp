bool open_gate(){

	char ip[24] = {1,3,0,1,9,5,0,0,6,1,9,6}; // 130.195.6.196
	char message[24] = {p,l,e,a,s,e}; // "please"
	
	int connect_to_server(ip, 1024);
	int send_to_server(message);
	receive_from_server(char code[24]);
	send_to_server(code);
	
	/*if(receive_from_server(//??)//==confirmation){
	return true;
	}
	else{return false;}
	*/
	
}
