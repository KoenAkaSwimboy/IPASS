#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & calibraionSw, hwlib::pin_in & startSw, int calWeight):
		hx711(DT, SCK),
		WEIGHTSCALE(DT, SCK),
		calibrationSw( calibrationSw ),
		startSw( startSw ),
		calWeight( calWeight )
        {}

void weightscale::start(int gain){
	while(!startSw.read()); 					//wait till start switch is pressed
	hwlib::cout<<"Starting... \n";
	WEIGHTSCALE.start(gain);					//start the weightscale
	hwlib::cout<<"Calibrating... \n";
	calibrate();								//calibrate
}

void weightscale::calibrate(){
	WEIGHTSCALE.tare(times);					//read and set the tare
	hwlib::cout<<"Please put " << calWeight << " on the weightscale and press the calibration button \n";
	while(!calibrationSw.read());				//wait till the calibration button is pressed
	hwlib::cout<<"Getting data... \n";
	offset = WEIGHTSCALE.getData(times);
	Scale = offset/calWeight;
	setScale(Scale);
	hwlib::cout<<"Done calibrating! \n";
	return;
}

unsigned long weightscale::weight(){
	return WEIGHTSCALE.getWeight(times);
}



