#ifndef WEIGHTSCALE_HPP
#define WEIGHTSCALE_HPP

#include "hx711.hpp"

///@file

///\brief
///Weightscale
///\details
///This a weightscale that gives back the number of grams that is
///on the physical weightscale. This class is a subclass of 
///the hx711 class.
///The avg, oneGram, calibrationSw, startSw and calWeight components
///are private attributes. 
///The appropiate constructers and functions are provided
class weightscale : public hx711::hx711{
private:
	hx711 WEIGHTSCALE;
	hwlib::pin_in & calibrationSw;
	hwlib::pin_in & startSw;
	int calWeight;
	int maxTries;
	unsigned long offset;
	unsigned int Scale;
public:

	///\brief
	///default constructor
	///\details
	///This constructor gives the DT en SCK to the class HX711
	///and initialize the calibrationSw and startSw attributes as
	///switches (pin_in) and initialize the calWeight attribute as
	///an integer. 
	weightscale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & calibrationSw, hwlib::pin_in & startSw, int calWeight);

	///\brief
	///Calibrate the weightscale
	///\details
	///This function calibrates the weightscale, first
	///it takes the average of 100 times of the current data
	///from the HX711 chip and allocate this to avg. Then it 
	///asks the user to put the calibrate weight on the 
	///weightscale. Again it takes the avarage of 100 times
	///of the current data from the HX711 chip and allocate this
	///to oneGram. Next it takes avg out of oneGram to get the
	///difference between the average of '0' gram and the calibrate
	///weight. It divides this number by the calibrate weight in grams
	///and returns this number.
	void calibrate();

	///\brief
	///Get the weight in grams
	///\details
	///This function takes the average of 25 times of
	///the current data from the HX711 chip and devides
	///this by oneGram to get the number of grams and returns
	///this number.
	long getWeight(int onegram);

	///\brief
	///start the application
	///\details
	///ask the user if its the first time starting the application
	///if so the function checks if the start button is being pressed.
	///When it is pressed, calibrate the weightscale. When this is done,
	///check if the power button is pressed, if so return -1 and close 
	///the fuction. If not return getWeight. If it's not the firstime,
	///just check if the power button is pressed, if so return -1 and if 
	///not return getWeight.
	void start(int gain);

	unsigned long weight();
};

#endif