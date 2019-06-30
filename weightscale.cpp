#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & confirmSw, hwlib::pin_in & startSw):
		hx711(DT, SCK),
		confirmSw( confirmSw ),
		startSw( startSw ) 
        {}

int weightscale::calibrate(){
		avg=0;
		for(unsigned int j=0; j<100; j++){
			avg=(readCount()+avg);
			// hwlib::cout<<" readCount avgg: " << readCount(); 									//tel de laatste waarde toe bij avg
		}
		avg/=100;													//gemiddelde van 100x
		hwlib::cout<< "please put 48g on the weightscale and press the blue button\n";
		while(true){
			confirmSw.refresh();
		 	if(!confirmSw.read()){
				hwlib::cout<<"Calibrating... \n";
				oneGram=0;
				for(unsigned int k=0; k<100; k++){
					oneGram=(readCount()+oneGram);
					// hwlib::cout<<" readCount oneGram: " << readCount();					//tel de laatste waarde toe bij avg
				}
				oneGram=(oneGram/100);								//bereken het gemiddelde
				oneGram=(oneGram-avg);								//bereken het verschil tussen het nieuwe en oude gemiddelde
				oneGram=(oneGram/48); 								//calibratie gewicht, antwoord hiervan staat gelijk aan 1 gram
				// hwlib::cout<<" Gram: " << oneGram << '\n';
				return oneGram;
			 }
		 }
	}

long weightscale::getWeight(int onegram){
	for(unsigned int l=0; l<25; l++){
		avg=(readCount()+avg);
		// hwlib::cout<<" readCount 2e avgg: " << readCount();
		// hwlib::cout<<readCount();
	}
	avg/=25;
	// hwlib::cout<< " Getal: " << avg/oneGram;
	return (avg/onegram);											//pak de laatste waarde en deel deze door wat gelijk staat aan 1 gram waardoor je het aantal grammen krijgt
}

void weightscale::start(){
	while(true){
		startSw.refresh();
		if(!startSw.read()){
			hwlib::cout<< "Starting... \n";
			int onegram = calibrate();
			while(true){
				startSw.refresh();
				if(!startSw.read()){									//als de aan/uit knop wordt ingedrukt kill het proces
					return;	
				}
				hwlib::cout<< " getWeight: " << getWeight(onegram) << " ---- ";
			}
		}
	}		
}