#include "hx711.hpp"

hx711::hx711(hwlib::pin_in & DT, hwlib::pin_out & SCK):	//constructor
		DT( DT ),
		SCK( SCK ) 
        {}

bool hx711::isReady(){									//check of de chip ready is
	DT.refresh();
	return !DT.read();									//the chip is ready if data pin is low (datasheet)
}

bool hx711::waitReady(){								//wait till the chip is ready
	bool ready = isReady();
	tries=0;
	while(!ready and tries<maxT){
		ready = isReady();
		hwlib::wait_ms(1);
		tries++;
	}
	return ready;
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
	hwlib::wait_us(1);									//wait 1 nano second to let the clock settle
}

void hx711::powerDown(){								//power the chip down
	SCK.write(0);
	hwlib::wait_us(1);									//wait 1 nano second to let the clock settle
	SCK.write(1);
	hwlib::wait_us(1);									//wait 1 nano second to let the clock settle
}

void hx711::start(int gain){							//start the chip
	setGain(gain);
	powerOn();
}

unsigned long hx711::read(){							//get the data from the chip
	if(!waitReady()){									//wait till the chip is ready
		hwlib::cout<<"The chip is not ready, please try again \n";
		return -1;
	}
	SCK.write(0);
	hwlib::wait_us(1);
	Data=0;
	DT.refresh();
	for(unsigned char i=0; i<24; i++){	
		SCK.write(1);
		hwlib::wait_us(1);								//wait 1 nano second to let the clock settle
		Data <<= 1;
		DT.refresh();
		if(DT.read()){
			Data++;
		}
	}
	nextConver();										//make the chip ready for the next conversion (datasheet)
	Data=(Data^0x800000);
	hwlib::cout<<" Data: " << Data << " - ";
	return Data;
}

void hx711::nextConver(){								//make the chip ready for the next conversion
	for(unsigned int i=0; i<GAIN; i++){					
		SCK.write(1);
		hwlib::wait_us(1);								//wait 1 nano second to let the clock settle
		SCK.write(0);
		hwlib::wait_us(1);								//wait 1 nano second to let the clock settle
	}
}

unsigned long hx711::readAvg(){							//Calculate an average over several measurements
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
	return readAvg() - Tare;
}

unsigned long hx711::getWeight() {						//getData devided through the calibration weight
	return getData()/scale;
}

void hx711::setTare(unsigned long TARE){				//set the tare
	Tare = TARE;
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