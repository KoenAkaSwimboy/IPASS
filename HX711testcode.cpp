#include "hx711.hpp"

namespace target = hwlib::target;

int main(void ){
	hwlib::wait_ms( 1000 ); 										
			
	auto SCK = target::pin_out( target::pins::d7 ); 
	auto DT = target::pin_in( target::pins::d6 ); 	
    int weight=0;			 					

	hx711 chip = hx711(DT, SCK);	        //Data pin, Clock pin

	chip.start(128);						//start the chip (gain of 128, must be 32, 64 or 128)
    chip.setTimes(25);
    chip.setCalibrationW(1);

	// while(true){                            //test read()
    //     weight = chip.read();
    //     hwlib::cout<<"Weight: " << weight << '\n';
	// }

    // while(true){                            //test readAvg()
    //     weight = chip.readAvg();        
    //      hwlib::cout<<"Weight: " << weight << '\n';
    // }

    chip.setTare();                          //test getWeight()
    hwlib::cout<<" Put 1kg on the loadcell \n";
    for(unsigned int i=0; i<100; i++){
        hwlib::wait_ms(10);
    } 
    chip.setScale();
    while(true){                           
        weight = chip.getWeight();
         hwlib::cout<<"Weight: " << weight << '\n';
    }
}