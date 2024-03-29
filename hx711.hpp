#ifndef HX711_HPP
#define HX711_HPP

#include "hwlib.hpp"

///@file

///\brief
///HX711
///\details
///HX711 returns the data from the chip.
///The gain, GAIN, tries, maxT, Data, DT, SCK, 
///times, avg, tare, calWeight and scale
///components are private attributes.
///The appropiate constructers and functions are provided
class hx711{
private:
	bool ready;
	unsigned int gain;			//defualt is 128
	unsigned int GAIN;
	int tries;
	int maxT=1000;				//default is 1000
	unsigned long Data;
	hwlib::pin_in & DT;
	hwlib::pin_out & SCK;

public:

	///\brief
	///default constructor 
	///\details
	///This constructor initializes the DT attribute as
	///an input (pin_in) and the SCK
	///attribute as an output (pin_out).
	hx711(hwlib::pin_in & DT, hwlib::pin_out & SCK);

	///\brief
	///Check if the chip is ready for retrieval
	///\details
	///The chip is ready for retrieval when the data pin is low,
	///see datasheet.
	bool isReady();

	///\brief
	///Wait till the chip is ready for retrieval
	void waitReady();

	///\brief
	///Set the gain
	///\details
	///With every gain there is a certain amount of
	///pulses the clock should give, see the datasheet.
	void setGain(int gain);
	
	///\brief
	///Power the chip
	///\details
	///To turn the chip on, SCK pin must be low, see datasheet
	void powerOn();

	///\brief
	///Start the chip
	///\details
	///First set the gain to 128, then turn the chip on.
	virtual void start();

	///\brief
	///Start the chip
	///\details
	///First set the gain, then turn the chip on.
	virtual void start(int gain);
	
	///\brief
	///Get the data from the chip
	///\details
	///First this function checks if the chip is ready for retrieval
	///if so, for 24 times the data is shifted out. Each SCK pulse
	///shifts out one
	///bit, for more information see the datasheet. When the data
	///is shifted out, the function calls nextConver() to make the
	///chip ready for the next conversion.
	unsigned long read();

	///\brief
	///Make the chip ready for the next conversion
	///\details
	///Depending on the gain, the clock gets a certain amount of
	///pulses to make the chip ready for the next conversion.
	///see the datasheet for more information.
	void nextConver();

	///\brief
	///Set the maximum amount of tries
	void setMaxT(int MAXT);
};

#endif