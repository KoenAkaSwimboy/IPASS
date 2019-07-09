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
	while(!isReady()){
		hwlib::wait_ms(1);
	}
	return isReady();
}

void hx711::setGain(int gain){
	if(gain<64){
		GAIN=2;
	}else if(gain<128){
		GAIN=3;
	}else{
		GAIN=1;
	}
};

void hx711::powerOn(){
	SCK.write(0);
}

void hx711::powerOff(){
	SCK.write(0);
	SCK.write(1);
;}

void hx711::start(int gain){
	setGain(gain);
	powerOn();
}

unsigned long hx711::readCount(void){
	if(waitReady()){						//wacht tot de chip klaar is om data te verzenden/ontvangen
	DT.direction_set_output();
	DT.direction_flush();
	DT.write(1);
	SCK.write(0);
    DT.direction_set_input();
	DT.direction_flush();
	DT.refresh();
	unsigned char i;
	Count =0;
	while(DT.read()){
		for(i=0; i<24; i++){	
			SCK.write(1);
			Count = (Count << 1);
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
	return Count;}
}