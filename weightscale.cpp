#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & confirmSw, hwlib::pin_in & startSw, int calWeight):
		hx711(DT, SCK),
		confirmSw( confirmSw ),
		startSw( startSw ),
		calWeight( calWeight ) 
        {}

int weightscale::calibrate(){
		avg=0;
		while(avg<=0){
			avg=0;
			for(unsigned int j=0; j<100; j++){
				avg=(readCount()+avg);
			}
		}
		avg/=100;	
		hwlib::cout<< "please put " << calWeight << " gram on the weightscale and press the blue button\n";
		while(true){
			confirmSw.refresh();
		 	if(!confirmSw.read()){
				hwlib::cout<<"Calibrating... \n";
				oneGram=0;
				while(oneGram<=0 || (oneGram/100)<=avg){
					oneGram=0;
					for(unsigned int k=0; k<100; k++){
						oneGram=(readCount()+oneGram);
					}
				}
				oneGram=(oneGram/100);								
				oneGram=(oneGram-avg);								
				oneGram=(oneGram/calWeight); 								
				return oneGram;
			 }
		 }
	}

long weightscale::getWeight(int onegram){
	while(avg<=0 || (avg/25) < oneGram){
		avg=0;
		for(unsigned int l=0; l<25; l++){
			avg=(readCount()+avg);
		}
	}
	avg/=25;
	return (avg/onegram);
}

long weightscale::start(bool firstTime){
	int onegram;
	if(firstTime){
		while(true){
			startSw.refresh();
			if(!startSw.read()){
				hwlib::cout<< "Starting... \n";
				onegram = calibrate();
				break;
			}
		}
	}
	startSw.refresh();
	if(!startSw.read()){
		return -1;	
	}
	return getWeight(onegram);	
}