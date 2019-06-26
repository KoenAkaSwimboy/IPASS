#include "hwlib.hpp"
#include "hx711.hpp"

namespace target = hwlib::target;

int main( void ){
	hwlib::wait_ms( 1000 ); //wacht tot de terminal is gestart
	

	auto startSw = target::pin_in( target::pins::d3 );  //switch om de weegschaal aan tezetten
	auto calSw = target::pin_in( target::pins::d2 );	//switch om de calibratie te starten
	auto DT = target::pin_in_out( target::pins::d4 ); 	//data in
	auto SCK = target::pin_out( target::pins::d5 );   	//clock
	
	while(true){
		startSw.refresh();
		if(startSw.read()){
			// hwlib::cout<<"in de if";
			auto weight = hx711(DT, SCK, calSw, true);
			auto counter = weight.readCount();
			hwlib::cout<<weight.calibrate(counter);
			break;
		}
		}
}