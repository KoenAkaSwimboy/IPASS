#ifndef WEIGHTSCALE_HPP
#define WEIGHTSCALE_HPP

#include "hx711.hpp"

///@file

///\brief
///Weightscale
///\details
///This is a weightscale that gives back the number of kilograms that is
///on the physical weightscale. This class is a subclass of 
///the hx711 class.
///The button, calWeight, maxTries, offset, Scale, gain and 
///times components are private attributes. 
///The appropriate constructers and functions are provided
class weightscale : public hx711::hx711{
private:
	hx711 WEIGHTSCALE;
	hwlib::pin_in & button;
	float calWeight;
	unsigned long offset;
	unsigned int Scale;
	int gain;
	unsigned int times;
	int maxTries;

public:

	///\brief
	///default constructor
	///\details
	///This constructor gives the DT and SCK to the class HX711
	///and initialize the button attribute as a
	///button (pin_in) and initialize the calWeight and maxT attributes as
	///an integer and the times attribute as an unsigned integer. 
	weightscale(hwlib::pin_in & DT, hwlib::pin_out & SCK, hwlib::pin_in & button, 
				float calWeight, unsigned int times=100, int maxTries=1000);

	///\brief
	///start the application
	///\details
	///This function does nothing until the button is pressed. When pressed, 
	///it starts the HX711 chip. After, it sets the amount of measurements 
	///and maximum of tries. Finally it calls the calibration function and stops.
	void start(int gain) override;
	
	
	///\brief
	///Calibrate the weightscale
	///\details
	///This function calibrates the weightscale, first
	///it sets the tare weight. Then it asks the user to put the 
	///calibrate weight on the weightscale and press the button.
	///When button is pressed the function gets the offset. After this
	///it calculates the scale by dividing the given calWeight with the offset.
	///Finally it sets the scale and stops.
	void calibrate();

	///\brief
	///Return the weight in kilograms
	///\details
	///Get the weight from the HX711 getWeight() function. That function returns a
	///float, hwlib::cout can't print a float so this function rounds up the numbers.
	float getWeight() override;
};

#endif