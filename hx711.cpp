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

bool hx711::waitReady(int maxT){
	tries=0;
	while(!isReady() and tries<maxT){
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
	hwlib::cout<<" avg: " <<readAvg(100, 500);
}

unsigned long hx711::read(int maxT){
	waitReady(maxT);						//wacht tot de chip klaar is om data te verzenden/ontvangen
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
	// hwlib::cout<<" Count: "<<Count;
	return Count;
}

unsigned long hx711::readAvg(unsigned int times, int maxT){
	avg=0;									//reset avg
	for(unsigned int k=0; k<times; k++){
		avg+=read(maxT);
	}
	return avg/times;
}



int hx711::getTries(){
	return tries;
}
