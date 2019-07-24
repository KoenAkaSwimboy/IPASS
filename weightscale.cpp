#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in & DT, hwlib::pin_out & SCK, hwlib::pin_in & button, 
						 float calibrationWeight, unsigned int times, int maxTries):
	hx711(DT, SCK),
	WEIGHTSCALE(DT, SCK),
	button( button ),
	calibrationWeight( calibrationWeight ),
	times ( times ),
	maxTries ( maxTries )
	{}

void weightscale::start(int gain){				//override the start function
	hwlib::cout<<"Please empty the weightscale and press the button \n";
	while(button.read()){						//wait till the button is pressed (pull down buttonitch)
		button.refresh();	
	}; 						
	hwlib::cout<<"Starting... \n";
	WEIGHTSCALE.start(gain);					//start the weightscale
	WEIGHTSCALE.setMaxT(maxTries);				//set the maximum tries
	calibrate();								//calibrate
	return;
}

unsigned long weightscale::readAvg(){							//Calculate an average over several measurements
	avg=0;												//reset avg
	for(unsigned int k=0; k<times; k++){
		avg+=WEIGHTSCALE.read();
	}
	return avg/times;
}

void weightscale::setTare(){									//set the tare with an average over several measurements
	readAvg();											//This seems to improve the tare accuratie
	tare = readAvg();
}

int weightscale::getOffset(){									//read the average over several measurements times minus the offset
	average = readAvg();
	return average- tare;
}

int weightscale::getWeight() {								//getData devided through the scale ('one gram')
	return getOffset()/scale;
}

void weightscale::setScale(){									//set the scale (number thats '1 kilogram')
	scale = getOffset()/calibrationWeight;
}

void weightscale::calibrate(){
	setTare();						//set the tare
	hwlib::cout<<"Please put the calibration weight on the weightscale and press the button \n";
	while(button.read()){						//wait till the calibration button is pressed (pull down buttonitch)
		button.refresh();
	}		
	hwlib::cout<<"Calibrating... \n";
	setScale();
	hwlib::cout<<"Done calibrating! \n";
	return;
}