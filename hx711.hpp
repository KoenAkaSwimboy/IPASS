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

#endif