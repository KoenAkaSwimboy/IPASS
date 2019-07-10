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
	int gain;
	uint8_t GAIN;
	int tries;
	int maxT=500;				//default is 500
	unsigned long Count;
	hwlib::pin_in_out & DT;
	hwlib::pin_out & SCK;
	int times;
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
	hx711(hwlib::pin_in_out & DT, hwlib::pin_out & SCK);

	bool isReady();

	bool waitReady();

	void setGain(int gain);
	
	void powerOn();

	void powerDown();

	void start(int gain);
	
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

	unsigned long readAvg(unsigned int times);

	void tare(unsigned int times);

	unsigned long getData(unsigned int times);

	unsigned long getWeight(unsigned int times);

	unsigned long getTare();

	void setTare(unsigned long TARE);

	float getScale();

	void setScale(float SCALE);

	int getMaxT();

	void setMaxT(int MAXT);
};

#endif