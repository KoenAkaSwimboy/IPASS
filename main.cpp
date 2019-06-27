#include "hx711.hpp"

namespace target = hwlib::target;

int main( void ){
	hwlib::wait_ms( 1000 ); //wacht tot de terminal is gestart
	

	auto startSw = target::pin_in( target::pins::d3 );  //switch om de weegschaal aan tezetten
	auto calSw = target::pin_in( target::pins::d2 );	//switch om de calibratie te starten
	auto DT = target::pin_in_out( target::pins::d4 ); 	//data in
	auto SCK = target::pin_out( target::pins::d5 );   	//clock

	auto weight = hx711(DT, SCK, calSw);				//weegschaal
	
	while(true){
		startSw.refresh();
		if(startSw.read()){
			hwlib::cout<< "moment graag \n";
			unsigned long skrt = weight.readCount();
			weight.calibrate(skrt);
			while(true){
				hwlib::cout<<weight.getWeight() << " KKKKK ";
			}
		}
	}
}