#ifndef HX711_HPP
#define HX711_HPP

#include "hwlib.hpp"

///@file

///\brief
///HX711
///\details
///HX711 returns the data from the chip.
///The gian, GAIN, tries, maxT, Data, DT, SCK, 
///times, avg, tare, calWeight and scale
///components are private attributes.
///The appropiate constructers and functions are provided
class hx711{
private:
	int gain=128;
	uint8_t GAIN;
	int tries;
	int maxT=1000;				//default is 1000
	unsigned long Data;
	hwlib::pin_in & DT;
	hwlib::pin_out & SCK;
	unsigned int times=100;		//default is 100
	unsigned long avg;
	unsigned long tare;
	int calWeight;
	float scale;
	float calibrationWeight;

public:

	///\brief
	///default constructor 
	///\details
	///This consturctor initialize the DT attribute as
	///an output and input (pin_in_out) and the SCK
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
	///Set the gain, see datasheet
	void setGain(int gain);
	
	///\brief
	///Power the chip
	///\details
	///To turn the chip on, SCK pin must be low, see datasheet
	void powerOn();

	///\brief
	///Power the chip down, see datasheet
	void powerDown();

	///\brief
	///Start the chip
	///\details
	///First set the gain, then turn the chip on.
	virtual void start(int gain);
	
	///\brief
	///Get the data from the chip
	///\details

	unsigned long read();

	///\brief
	///Make the chip ready for the next conversion
	///\details
	///Depending on the gain, 
	void nextConver();

	///\brief
	///Calculate an average over several measurements
	unsigned long readAvg();

	///\brief
	///Take the average over several measurements and set this as the tare
	void setTare();

	///\brief
	///Read the avrage of 'times' minus the offset
	unsigned long getOffset();

	///\brief
	///getData() devide through the calibration weight
	virtual unsigned long getWeight();

	///\brief
	///Set the scale
	///\details
	///The scale is the value that is 'one gram'
	void setScale();

	///\brief
	///Set the calibration weight
	void setCalibrationW(float calWeight);

	///\brief
	///Set the amount of measurements
	void setTimes(int TIMES);

	///\brief
	///Set the maxium amount of tries
	void setMaxT(int MAXT);
};

#endif