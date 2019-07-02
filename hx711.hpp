#ifndef HX711_HPP
#define HX711_HPP

#include "hwlib.hpp"

///@file

///\brief
///HX711
///\details
///HX711 returns the data from the chip.
///The Count, DT and SCK components are protected attributes 
///HX711 is the supperclass of weightscale).
///The appropiate constructers and functions are provided
class hx711{
protected:
	unsigned long Count;
	hwlib::pin_in_out & DT;
	hwlib::pin_out & SCK;

public:

	///\brief
	///default constructor 
	///\details
	///This consturctor initialize the DT attribute as
	///an output and input (pin_in_out) and the SCK
	///attribute as an output (pin_out).
	hx711(hwlib::pin_in_out & DT, hwlib::pin_out & SCK);

	///\brief
	///Get the data from the chip
	///\details
	///This function gets the data from the chip. The function
	///sets DT (Data pin) as an output and sets it to 1 and the SCK
	///to 0. After this it sets DT as an input, it sets Count to 0
	///to make sure there isn't a random value in Count. While DT
	///is 1, pulse the clock 24 times to read the data. Return 
	///the data. this code is from the datasheet of the HX711 chip.
	unsigned long readCount(void);
};

#endif