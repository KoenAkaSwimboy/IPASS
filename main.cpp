#include "weightscale.hpp"

namespace target = hwlib::target;

int main( void ){
	hwlib::wait_ms( 1000 ); 										//wacht tot de terminal is gestart

	auto startSw = target::pin_in( target::pins::d6 ); 				//switch om de weegschaal aan tezetten
	auto calSw = target::pin_in( target::pins::d7 );				//switch om de calibratie te starten
	auto DT = target::pin_in_out( target::pins::d4 ); 				//data in
	auto SCK = target::pin_out( target::pins::d5 );   				//clock

	auto weight = weightscale(DT, SCK, calSw, startSw);				//weegschaal

	weight.start();													//start de aplicatie
}