#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in & DT, hwlib::pin_out & SCK, hwlib::pin_in & button, 
						 float calWeight, unsigned int times, int maxTries):
	hx711(DT, SCK),
	WEIGHTSCALE(DT, SCK),
	button( button ),
	calWeight( calWeight ),
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
	WEIGHTSCALE.setTimes(times);				//Set the amount of measurements
	WEIGHTSCALE.setMaxT(maxTries);				//set the maximum tries
	WEIGHTSCALE.setCalibrationW(calWeight);		//set the calibaration weight
	calibrate();								//calibrate
	return;
}

void weightscale::calibrate(){
	WEIGHTSCALE.setTare();						//set the tare
	hwlib::cout<<"Please put the calibration weight on the weightscale and press the button \n";
	while(button.read()){						//wait till the calibration button is pressed (pull down buttonitch)
		button.refresh();
	}		
	hwlib::cout<<"Calibrating... \n";
	WEIGHTSCALE.setScale();
	hwlib::cout<<"Done calibrating! \n";
	return;
}

float weightscale::getWeight(){
	float weight = WEIGHTSCALE.getWeight();
	if(weight>=0.5 and weight<1.5){
		weight=1;
	}else if(weight>=1.5 and weight<2.5){
		weight=2;
	}else if(weight>=2.5 and weight<3.5){
		weight=3;
	}else if(weight>=3.5 and weight<4.5){
		weight=4;
	}else if(weight>=4.5 and weight<5.5){
		weight=5;
	}else if(weight>=5.5 and weight<6.5){
		weight=6;
	}else if(weight>=6.5 and weight<7.5){
		weight=7;
	}else if(weight>=7.5 and weight<8.5){
		weight=8;
	}else if(weight>=8.5 and weight<9.5){
		weight=9;
	}else if(weight>=9.5 and weight<=10){
		weight=10;
	}else{
		weight=0;
	}
	return weight;
}