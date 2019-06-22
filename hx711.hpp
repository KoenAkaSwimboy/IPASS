#include "hwlib.hpp"

unsigned long readCount(void){
	auto DT = hwlib::target::pin_in_out( hwlib::target::pins::d4 );
	auto SCK = hwlib::target::pin_out( hwlib::target::pins::d5 );
	DT.direction_set_output();
	DT.direction_flush();
	
	auto led = hwlib::target::pin_in_out( hwlib::target::pins::d8 );
	led.direction_set_output();
	led.direction_flush();
	led.write(0);
	led.flush();
	
    unsigned long Count=0;
    DT.write(1);
    SCK.write(0);
    DT.direction_set_input();
    DT.direction_flush();
	DT.refresh();
    while(DT.read()){
        for(unsigned int i=0; i<24; i++){	
            SCK.write(1);
            Count = Count << 1;
            SCK.write(0);
            DT.refresh();
            if(DT.read()){
				hwlib::cout<<"please print";				//cout test
				Count++;
            }
        }
    }
    SCK.write(1);
    Count=Count^0x800000;
    SCK.write(0);
	led.write(1);				//led
	led.flush();				//test
    return(Count);
}

unsigned long toGrams(unsigned long grams, long sample, float val){
		return(((grams-sample)/val)-2*((grams-sample)/val));	
}

unsigned long calibrate(unsigned long calGrams){
	long sample=0;
	float val=0;
	for(int i=0; i<100; i++){
		sample+=calGrams;
	}
	sample/=100;
	calGrams=0;
	while(calGrams<1000){
		calGrams=readCount();
		calGrams=sample-calGrams;
	}for(int j=0; j<100; j++){
		calGrams=readCount();
		val+=sample-calGrams;
	}
	val=val/100;						//gemiddelde
	val=val/100; 						//calibratie gewicht
	return toGrams(calGrams, sample, val);
}

