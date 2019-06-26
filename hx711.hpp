#include "hwlib.hpp"

namespace target = hwlib::target;

class hx711{
private:
	unsigned long Count=0;
	unsigned long grams=0;
	unsigned long calGrams=0; 
	long sample=0; 
	float val=0;
	hwlib::pin_in_out & DT;
	hwlib::pin_out & SCK;
	hwlib::pin_in & calSw;
	bool toGramsBool=false;

public:
	hx711(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & calSw, bool toGramsBool):
		DT( DT ),
		SCK( SCK ),
		calSw( calSw ),
		toGramsBool( toGramsBool ) {}

unsigned long readCount(bool firstT){
	DT.direction_set_output();
	DT.direction_flush();
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
				Count++;
            }
        }
    }
    SCK.write(1);
    Count=Count^0x800000;
    SCK.write(0);
	hwlib::cout<< "please put 10g on the weightscale and press the blue button\n";
	while(firstT){
		if(calSw.read()){
			calibrate(Count);
			break;
		}
	}
	return toGrams(calGrams, sample, val);
}

unsigned long toGrams(unsigned long grams, long sample, float val){
		return(((grams-sample)/val)-2*((grams-sample)/val));	
}

void calibrate(unsigned long calGrams){
	hwlib::cout <<"in calibrate\n";
	for(int i=0; i<100; i++){
		sample+=calGrams;
	}
	sample/=100;
	calGrams=0;
	while(calGrams<1000){
		calGrams=readCount(false);
		calGrams=sample-calGrams;
	}for(int j=0; j<100; j++){
		calGrams=readCount(false);
		val+=sample-calGrams;
	}
	val=val/100;						//gemiddelde
	val=val/10; 						//calibratie gewicht
	// return toGrams(calGrams, sample, val);
}
};

