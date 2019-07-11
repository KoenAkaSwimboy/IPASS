#include "hx711.hpp"

hx711::hx711(hwlib::pin_in & DT, hwlib::pin_out & SCK):
		DT( DT ),
		SCK( SCK ) 
        {}

bool hx711::isReady(){									//check of de chip ready is
	DT.refresh();
	return !DT.read();									//hwlib::pin_in_out.read() return 0 when true and 1 when false
}

bool hx711::waitReady(){								//wait till the chip is ready
	tries=0;
	while(!isReady() and tries<maxT){
		hwlib::wait_ms(1);
		tries++;
	}
	return true;
}

void hx711::setGain(int gain){
	if(gain==128){										//gain 128 channel A
		GAIN=1;
	}else if(gain==64){									//gain 64 channel A
		GAIN=3;
	}else{												//gain 32 channel B
		GAIN=2;
	}
}

void hx711::powerOn(){									//turn the chip 'on' 
	SCK.write(0);
	hwlib::wait_us(1);
}

void hx711::powerDown(){								//power the chip down
	SCK.write(0);
	hwlib::wait_us(1);
	SCK.write(1);
	hwlib::wait_us(1);
}

void hx711::start(int gain){							//start the chip
	setGain(gain);
	powerOn();
}

unsigned long hx711::read(){							//get the data from the chip
	while(!waitReady());								//wait till the chip is ready
	SCK.write(0);
	hwlib::wait_us(1);
	Count =0;
	DT.refresh();
	while(!DT.read()){
		hwlib::cout<<" in while";
		for(unsigned char i=0; i<24; i++){	
			SCK.write(1);
			hwlib::wait_us(1);
			Count <<= 1;
			SCK.write(0);
			hwlib::wait_us(1);
			DT.refresh();
			if(!DT.read()){
				Count++;
				hwlib::cout<< " Count in If: " << Count;
			}
		}
	}
	for(unsigned int i=0; i<GAIN; i++){					//make the chip ready for the next conversion
			SCK.write(1);
			hwlib::cout<< " Count voor 0x80: " << Count;
			Count=(Count^0x800000);
			hwlib::cout<<" Count na: " << Count;
			SCK.write(0);
		}
	hwlib::cout<<" Count: " << Count;
	return Count;
}


unsigned long hx711::readAvg(){							//take the avg of input times
	avg=0;												//reset avg
	for(unsigned int k=0; k<times; k++){
		avg+=read();
	}
	return avg/times;
}

void hx711::tare(){										//set the tare with a avg of 100 times
	setTare(readAvg());
}

unsigned long hx711::getData(){							//read the avg of 100 times minus the offset
	return readAvg() - getTare();
}

unsigned long hx711::getWeight() {
	return getData()/getScale();
}

unsigned long hx711::getTare(){							//get the tare
	return Tare;
}

void hx711::setTare(unsigned long TARE){				//set the tare
	Tare = TARE;
}

float hx711::getScale(){								//get the scale
	return scale;
}

void hx711::setScale(float SCALE){						//set the scale (number thats '1 gram')
	scale = SCALE;
}

void hx711::setTimes(int TIMES){						//set the times, default is 100
	times = TIMES;
}

void hx711::setMaxT(int MAXT){							//set the maximum tries, defualt is 500
	maxT = MAXT;
}