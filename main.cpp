#include "weightscale.hpp"

namespace target = hwlib::target;

int main(void ){
	hwlib::wait_ms( 1000 ); 										
			
	auto SCK = target::pin_out( target::pins::d7 ); 
	auto DT = target::pin_in( target::pins::d6 ); 				 				
	auto calSw = target::pin_in( target::pins::d4 );		

	weightscale weightScale = weightscale(DT, SCK, calSw, 1, 25);	//Data pin, Clock pin, Calibration button, Start button, calibration weight, times of average, maximum tries

	weightScale.start(128);													//start the weightscale (gain of 128, must be 32, 64 or 128)

	while(true){
		int weight=weightScale.getWeight();
		hwlib::cout<< "Weight: " << weight << " kg\n";
	}
}