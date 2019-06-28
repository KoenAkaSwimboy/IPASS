#include "weightscale.hpp"

weightscale::weightscale(hwlib::pin_in_out & DT, hwlib::pin_out & SCK, hwlib::pin_in & confirmSw, hwlib::pin_in & startSw):
		hx711(DT, SCK),
		confirmSw( confirmSw ),
		startSw( startSw ) 
        {}

void weightscale::calibrate(){
		avg=0;
		for(unsigned int j=0; j<100; j++){
			avg=readCount()+avg; 								//tel de laatste waarde toe bij avg
		}
		avg/=100;													//gemiddelde van 100x
		hwlib::cout<< "please put 48g on the weightscale and press the blue button\n";
		while(true){
			confirmSw.refresh();
		 	if(confirmSw.read()){
				hwlib::cout<<"Calibrating... \n";
				oneGram=0;
				for(unsigned int k=0; k<100; k++){
					oneGram=readCount()+oneGram;				//tel de laatste waarde toe bij avg
				}
				oneGram=oneGram/100;								//bereken het gemiddelde
				oneGram=oneGram-avg;								//bereken het verschil tussen het nieuwe en oude gemiddelde
				oneGram=oneGram/48; 								//calibratie gewicht, antwoord hiervan staat gelijk aan 1 gram
				return;
			 }
		 }
	}

unsigned long weightscale::getWeight(){
	return (readCount()/oneGram);							//pak de laatste waarde en deel deze door wat gelijk staat aan 1 gram waardoor je het aantal grammen krijgt
}

void weightscale::start(){
	while(true){
		startSw.refresh();
		if(startSw.read()){
			hwlib::cout<< "Starting... \n";
			calibrate();
			while(true){
				startSw.refresh();
				if(startSw.read()){							//als de aan/uit knop wordt ingedrukt kill het proces
					return;	
				}
				hwlib::cout<<getWeight() << " ---- ";
			}
		}
	}		
}