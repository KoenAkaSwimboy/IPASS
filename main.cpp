#include "hwlib.hpp"
#include "hx711.hpp"

int main( void ){
	auto led = hwlib::target::pin_in_out( hwlib::target::pins::d8 );
	led.direction_set_output();
	led.direction_flush();
	
	while(true){
		hwlib::cout<<"yes";
		unsigned int test = readCount();
		hwlib::cout<<test;
		if(test>0){
		led.write(1);
		led.flush();}}
}