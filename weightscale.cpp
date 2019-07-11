#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in & DT, hwlib::pin_out & SCK, hwlib::pin_in & calibrationSw, 
						 hwlib::pin_in & startSw, int calWeight, unsigned int times, int maxT):
	hx711(DT, SCK),
	WEIGHTSCALE(DT, SCK),
	calibrationSw( calibrationSw ),
	startSw( startSw ),
	calWeight( calWeight ),
	times ( times ),
	maxT ( maxT )
	{}

void weightscale::start(int gain){				//override the start function
	// while(startSw.read()); 						//wait till the start/shut down switch is pressed (pull down switch)
	hwlib::cout<<"Starting... \n";
	WEIGHTSCALE.start(gain);					//start the weightscale
	WEIGHTSCALE.setTimes(times);				//set how many times avg dinges help
	WEIGHTSCALE.setMaxT(maxT);					//set the maximum tries
	hwlib::cout<<"Calibrating... \n";
	calibrate();								//calibrate
	return;
}

void weightscale::calibrate(){
	WEIGHTSCALE.tare();							//read and set the tare
	hwlib::cout<<"Please put " << calWeight << " gram on the weightscale and press the calibration button \n";
	while(calibrationSw.read());				//wait till the calibration button is pressed (pull down switch)
	hwlib::cout<<"Getting data... \n";
	offset = WEIGHTSCALE.getData();
	Scale = offset/calWeight;
	setScale(Scale);
	hwlib::cout<<"Done calibrating! \n";
	return;
}

unsigned long weightscale::weight(){
	return WEIGHTSCALE.getWeight();
}



