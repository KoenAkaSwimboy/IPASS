#ifndef HX711_HPP
#define HX711_HPP

#include "hwlib.hpp"

class hx711{
protected:
	unsigned long Count;
	hwlib::pin_in_out & DT;
	hwlib::pin_out & SCK;

public:
	hx711(hwlib::pin_in_out & DT, hwlib::pin_out & SCK);

	unsigned long readCount();
};

class weightScale : public hx711{
private:
	unsigned long avg; 
	unsigned long oneGram;
	hwlib::pin_in & confirmSw;
	hwlib::pin_in & startSw;

public:
	weightScale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & confirmSw, hwlib::pin_in & startSw);

	void calibrate();
	unsigned long getWeight();
	void start();
};

#endif