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
	bool ready;
	unsigned int gain;			//defualt is 128
	unsigned int GAIN;
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
	bool on;					//for testing
	int next;					//for testing

public:

	///\brief
	///default constructor 
	///\details
	///This consturctor initialize the DT attribute as
	///an output and input (pin_in) and the SCK
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
	///Power the chip down
	///\details
	///By pulsing the clock one time, the chip enters a power down mode
	////see datasheet.
	void powerDown();

	virtual void start();

	///\brief
	///Start the chip
	///\details
	///First set the gain, then turn the chip on.
	virtual void start(int gain);
	
	///\brief
	///Get the data from the chip
	///\details
	///First this function checks if the chip is ready for retrival
	///if so, for 24 times the data is shifted out. Each SCK pulse
	///(SCK.write(1) ... SCK.write(0) is one pulse) shifts out one
	///bit, for more information see the datasheet. When the data
	///is shifted out, the function calls nextConver() to make the
	///chip ready for the next conversion.
	unsigned long read();

	///\brief
	///Make the chip ready for the next conversion
	///\details
	///Depending on the gain, the clock gets a cetain amount of
	///pulses to make the chip ready for the next conversion.
	///see the datasheet for more information.
	void nextConver();

	///\brief
	///Calculate an average over several measurements
	unsigned long readAvg();

	///\brief
	///Set the tare
	///\details
	///Take the average over several measurements and set this as the tare
	void setTare();

	///\brief
	///Read the avrage over several measurments minus the offset
	unsigned long getOffset();

	///\brief
	///Get the weight in grams
	///\details
	///This function returns the weight in grams. It takes the offset and 
	///devides it through the scale to get the right amount of grams.
	virtual unsigned long getWeight();

	///\brief
	///Set the scale
	///\details
	///The scale is the value that is 'one gram'. You can get this
	///by deviding the offset through the calibrationweight.
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

	///\brief
	///Get the gain, for testing
	unsigned int getGain();

	///\brief
	///Get the	on, for testing
	bool getOn();

	///\brief
	///Get the gain, for testing
	bool getReady();

	///\brief
	///Get the gain, for testing
	float getCalWeight();

	///\brief
	///Get the times, for testing
	int getTimes();

	///\brief
	///Get the maxT, for testing
	int getMaxT();

	///\brief
	///Get the next, for testing
	int getNext();
};

#endif