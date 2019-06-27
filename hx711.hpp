#include "hwlib.hpp"

namespace target = hwlib::target;

class hx711{
private:
	unsigned long Count=0;
	unsigned long grams=0;
	unsigned long calGrams; 
	unsigned long sample=0; 
	float val=0;
	unsigned long test=0;
	hwlib::pin_in_out & DT;
	hwlib::pin_out & SCK;
	hwlib::pin_in & calSw;

public:
	hx711(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & calSw):
		DT( DT ),
		SCK( SCK ),
		calSw( calSw ) {}

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

	void calibrate(unsigned long calGrams){
		sample=0;
		for(unsigned int i=0; i<100; i++){
			calGrams=readCount();							//pak de laatste waarde
			sample=calGrams+sample; 						//ken de laatste waarde toe aan sample
		}
		sample/=100;										//gemiddelde van 100x
		hwlib::cout<< "please put 48g on the weightscale and press the blue button\n";
		while(true){
			// calSw.refresh();
		 	if(calSw.read()){
				 val=0;
				for(unsigned int j=0; j<100; j++){
					calGrams=readCount();					//pak de laatste waarde	
					val=calGrams+val;						//voor 100x voeg het verschil tussen de laatste waarde en het gemiddelde aan elkaar toe
				}
				val=val/100;								//bereken het gemiddelde
				val = val - sample;							//bereken het verschil tussen het nieuwe en oude gemiddelde
				val=val/48; 								//calibratie gewicht, antwoord hiervan staat gelijk aan 1 gram
				return;
			 }
		 }
	}

	unsigned long getWeight(){
		return (readCount()/val);							//pak de laatste waarde en deel deze door wat gelijk staat aan 1 gram waardoor je het aantal grammen krijgt
	}
};