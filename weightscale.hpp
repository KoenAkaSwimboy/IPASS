#ifndef WEIGHTSCALE_HPP
#define WEIGHTSCALE_HPP

#include "hx711.hpp"

class weightscale : public hx711::hx711{
private:
	unsigned long avg; 
	unsigned long oneGram;
	hwlib::pin_in & confirmSw;
	hwlib::pin_in & startSw;

public:
	weightscale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & confirmSw, hwlib::pin_in & startSw);

	void calibrate();
	unsigned long getWeight();
	void start();
};

#endif