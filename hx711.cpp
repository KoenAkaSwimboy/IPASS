#include "hx711.hpp"

hx711::hx711(hwlib::pin_in_out & DT, hwlib::pin_out & SCK):
		DT( DT ),
		SCK( SCK ) 
        {}

bool hx711::isReady(){
	DT.direction_set_input();
	DT.direction_flush();
	DT.refresh();
	return DT.read();
}

bool hx711::waitReady(){
	tries=0;
	while(!isReady() and tries<getMaxT()){
		hwlib::wait_ms(1);
		tries++;
	}
	return true;
}

void hx711::setGain(int gain){
	if(gain<64){								//gain 32 channel B
		GAIN=2;
	}else if(gain<128){							//gain 64 channel A
		GAIN=3;
	}else{										//gain 128 channel A
		GAIN=1;
	}
}

void hx711::powerOn(){
	SCK.write(0);
}

void hx711::powerDown(){
	SCK.write(0);
	SCK.write(1);
}

void hx711::start(int gain){
	setGain(gain);
	powerOn();
}

unsigned long hx711::read(){
	while(!waitReady());						//wacht tot de chip klaar is om data te verzenden/ontvangen
	DT.direction_set_output();
	DT.direction_flush();
	DT.write(1);
	SCK.write(0);
	DT.direction_set_input();
	DT.direction_flush();
	DT.refresh();
	Count =0;
	for(int j=0; j< 24+GAIN; j++){
		for(unsigned char i=0; i<24; i++){	
			SCK.write(1);
			Count <<= 1;
			SCK.write(0);
			DT.refresh();
			if(DT.read()){
				Count++;
			}
		}
	}
	SCK.write(1);
	Count=(Count^0x800000);
	SCK.write(0);
	return Count;
}

unsigned long hx711::readAvg(unsigned int times){				//take the avg of input times
	avg=0;																//reset avg
	for(unsigned int k=0; k<times; k++){
		avg+=read();
	}
	return avg/times;
}

void hx711::tare(unsigned int times){							//set the tare with a avg of 100 times
	setTare(readAvg(times));
}

unsigned long hx711::getData(unsigned int times){				//read the avg of 100 times minus the offset
	return readAvg(times) - getTare();
}

unsigned long hx711::getWeight(unsigned int times) {
	return getData(times)/getScale();
}

unsigned long hx711::getTare(){											//get the tare
	return Tare;
}

void hx711::setTare(unsigned long TARE){								//set the tare
	Tare = TARE;
}

float hx711::getScale(){												//get the scale
	return scale;
}

void hx711::setScale(float SCALE){										//set the scale (number thats '1 gram')
	scale = SCALE;
}

int hx711::getMaxT(){
	return maxT;
}

void hx711::setMaxT(int MAXT){
	maxT = MAXT;
}

