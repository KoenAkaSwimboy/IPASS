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
private:
	int gain=128;
	uint8_t GAIN;
	int tries;
	int maxT=500;				//default is 500
	unsigned long Count;
	hwlib::pin_in & DT;
	hwlib::pin_out & SCK;
	unsigned int times=100;		//default is 100
	unsigned long avg;
	unsigned long Tare;
	int calWeight;
	unsigned long readTare;
	float scale;

public:

	///\brief
	///default constructor 
	///\details
	///This consturctor initialize the DT attribute as
	///an output and input (pin_in_out) and the SCK
	///attribute as an output (pin_out).
	hx711(hwlib::pin_in & DT, hwlib::pin_out & SCK);

	bool isReady();

	bool waitReady();

	void setGain(int gain);
	
	void powerOn();

	void powerDown();

	virtual void start(int gain);
	
	///\brief
	///Get the data from the chip
	///\details
	///This function gets the data from the chip. The function
	///sets DT (Data pin) as an output and sets it to 1 and the SCK
	///to 0. After this it sets DT as an input, it sets Count to 0
	///to make sure there isn't a random value in Count. While DT
	///is 1, pulse the clock 24 times to read the data. Return 
	///the data. this code is from the datasheet of the HX711 chip.
	unsigned long read();

	void nextConver();

	unsigned long readAvg();

	void tare();

	unsigned long getData();

	unsigned long getWeight();

	unsigned long getTare();

	void setTare(unsigned long TARE);

	float getScale();

	void setScale(float SCALE);

	void setTimes(int TIMES);

	void setMaxT(int MAXT);
};

#endif