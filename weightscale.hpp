#ifndef WEIGHTSCALE_HPP
#define WEIGHTSCALE_HPP

#include "hx711.hpp"

class weightscale : public hx711::hx711{
private:
	long avg; 
	int oneGram;
	hwlib::pin_in & confirmSw;
	hwlib::pin_in & startSw;
	int calWeight=0;

public:
	weightscale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & confirmSw, hwlib::pin_in & startSw, int calWeight);

	int calibrate();
	long getWeight(int onegram);
	void start();
};

#endif