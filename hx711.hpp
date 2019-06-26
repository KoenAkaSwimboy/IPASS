#include "hwlib.hpp"

namespace target = hwlib::target;

class hx711{
private:
	unsigned long Count=0;
	unsigned long grams=0;
	unsigned long calGrams; 
	long sample=0; 
	long val=0;
	unsigned long test=0;
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

unsigned long readCount(){
	DT.direction_set_output();
	DT.direction_flush();
    DT.write(1);
    SCK.write(0);
    DT.direction_set_input();
    DT.direction_flush();
	DT.refresh();
	unsigned char i;
    while(DT.read()){
        for(i=0; i<24; i++){	
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
	return Count;
}

unsigned long toGrams(unsigned long grams, long sample, float val){
		unsigned long som = (((grams-sample)/val)-2*((grams-sample)/val));
		hwlib::cout<<" sample: " << sample << " grams: " << grams << "\n som" << som;
		return(((grams-sample)/val)-2*((grams-sample)/val));	
}

void calibrate(unsigned long calGrams){
	hwlib::cout <<"in calibrate\n";
	for(int i=0; i<100; i++){
		calGrams=readCount();	//pak de laatste waarde
		sample+=calGrams; 			//ken de laatste waarde toe aan sample
		hwlib::cout<<"sample: "<< sample << " grams: " << calGrams << " :: ";
	}
	sample/=100;		//gemiddelde van 100x
	hwlib::cout<< "please put 48g on the weightscale and press the blue button\n";
	while(true){
		if(calSw.read()){
			// while(test<1000){
			// 	test=readCount();			//pak de laatste waarde
			// 	test=sample-test;		//als het verschil tussen het gemiddelde en de laatste waarde groter is dan 1000 ga door
				for(int j=0; j<100; j++){
					calGrams=readCount();	//pak de laatste waarde	
					val+=calGrams - sample;		//voor 100x voeg het verschil tussen de laatste waarde en het gemiddelde aan elkaar toe
				}
				val=val/100;						//bereken het gemiddelde
				val=val/48; 						//calibratie gewicht
				// int som = (((calGrams-sample)/val)-2*((calGrams-sample)/val));
				int som = calGrams/val;
					hwlib::cout<<"sample: " << sample << " grams: " << calGrams << "\n val: " << val << " som: " << som;
		}
	}
}
};

// if(firstT){
// 		hwlib::cout<< "please put 48g on the weightscale and press the blue button\n";
// 		while(firstT){
// 			if(calSw.read()){
// 				calibrate(Count);
// 				firstT=false;
// 			}
// 		}
// 	}