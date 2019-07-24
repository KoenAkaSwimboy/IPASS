#include "hx711.hpp"

namespace target = hwlib::target;

// int main(void ){
// 	hwlib::wait_ms( 1000 ); 										
			
// 	auto SCK = target::pin_out( target::pins::d7 ); 
// 	auto DT = target::pin_in( target::pins::d6 ); 	
//     int weight=0;			 					

// 	hx711 chip = hx711(DT, SCK);	        //Data pin, Clock pin

// 	chip.start(128);						//start the chip (gain of 128, must be 32, 64 or 128)

// 	// while(true){                            //test read() the number gets higher, the more kilogram you put on the loadcell
//     //     weight = chip.read();
//     //     hwlib::cout<<"Weight: " << weight << '\n';
// 	// }