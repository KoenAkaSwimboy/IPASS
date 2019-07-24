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
	float calibrationWeight;
	unsigned long offset;
	int gain;
	float times=100;			//default is 100
	int maxTries;
	unsigned long avg;
	unsigned long tare;
	int scale;
	int average;

public:

	///\brief
	///default constructor
	///\details
	///This constructor gives the DT and SCK to the class HX711
	///and initialize the button attribute as a
	///button (pin_in) and initialize the calWeight and maxT attributes as
	///an integer and the times attribute as an unsigned integer. 
	weightscale(hwlib::pin_in & DT, hwlib::pin_out & SCK, hwlib::pin_in & button, 
				float calibrationWeight, unsigned int times=100, int maxTries=1000);

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
	///Calculate an average of several measurements
	unsigned long readAvg();

	///\brief
	///Set the tare
	///\details
	///Take the average of several measurements and set this as the tare
	void setTare();

	///\brief
	///Read the average of several measurments minus the offset
	int getOffset();

	///\brief
	///Get the weight in grams
	///\details
	///This function returns the weight in kilograms. It takes the offset and 
	///devides it through the scale to get the right amount of kilograms.
	int getWeight();

	///\brief
	///Set the scale
	///\details
	///The scale is the value that is 'one kilogram'. You can get this
	///by dividing the offset through the calibration weight.
	void setScale();
};

#endif