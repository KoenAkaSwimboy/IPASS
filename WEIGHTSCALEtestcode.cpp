#include "weightscale.hpp"

namespace target = hwlib::target;

// int main(void ){
// 	hwlib::wait_ms( 1000 ); 										
			
// 	auto SCK = target::pin_out( target::pins::d7 ); 
// 	auto DT = target::pin_in( target::pins::d6 ); 	
//     auto button = target::pin_in( target::pins::d4);		 					

// 	weightscale WEIGHTSCALE = weightscale(DT, SCK, button, 1, 25);	        //Data pin, Clock pin, button, calibrationweight, times of average
 
// 	WEIGHTSCALE.start(128);						//start the chip (gain of 128, must be 32, 64 or 128)                     

// 	while(true){                                //test readAvg() the number gets higher, the more kilogram you put on the loadcell
//         hwlib::cout << "Average: " << WEIGHTSCALE.readAvg() << '\n';
//     }

//     // while(true){                                //test getOffset() the number gets higher, the more kilogram you put on the loadcell
//     //     hwlib::cout << "Offset: " << WEIGHTSCALE.getOffset() << '\n';
//     // }

//     // while(true){                                //test getWeight() the number gets higher, the more kilogram you put on the loadcell
//     //     hwlib::cout << "Weight: " << WEIGHTSCALE.getWeight() << '\n';
//     // }
// }