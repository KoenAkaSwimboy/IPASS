#include "weightscale.hpp"

namespace target = hwlib::target;

int main( void ){
	hwlib::wait_ms( 1000 ); 										
			
	auto DT = target::pin_in_out( target::pins::d6 ); 				
	auto SCK = target::pin_out( target::pins::d7 ); 
  	auto startSw = target::pin_in( target::pins::d5 ); 				
	auto calSw = target::pin_in( target::pins::d4 );	

	auto chip = hx711(DT, SCK);

	while(true){
	chip.start(128);}

	// auto weightScale = weightscale(DT, SCK, calSw, startSw, 250);

	// long weight = weightScale.start(1);
	// while(weight>=0){
	// 	weight = weightScale.start(0);
	// 	hwlib::cout<< weight << " gram; ";
	// }
}