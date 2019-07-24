#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in & DT, hwlib::pin_out & SCK, hwlib::pin_in & calibrationSw, 
						 hwlib::pin_in & startSw, int calWeight, unsigned int times, int maxTries):
	hx711(DT, SCK),
	WEIGHTSCALE(DT, SCK),
	calibrationSw( calibrationSw ),
	startSw( startSw ),
	calWeight( calWeight ),
	times ( times ),
	maxTries ( maxTries )
	{}

void weightscale::start(int gain){				//override the start function
	while(startSw.read()); 						//wait till the start/shut down switch is pressed (pull down switch)
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
	hwlib::cout<<"Please put " << calWeight << " kilogram on the weightscale and press the calibration button \n";
	while(calibrationSw.read());				//wait till the calibration button is pressed (pull down switch)
	hwlib::cout<<"Calibrating... \n";
	WEIGHTSCALE.setScale();
	hwlib::cout<<"Done calibrating! \n";
	WEIGHTSCALE.setTimes(25);
	return;
}

unsigned long weightscale::getWeight(){
	unsigned long weight = WEIGHTSCALE.getWeight();
	if(weight>10000){
		weight=0;
	}
	return weight;
}