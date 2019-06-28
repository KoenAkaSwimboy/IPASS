#include "hx711.hpp"

hx711::hx711(hwlib::pin_in_out & DT, hwlib::pin_out & SCK):
		DT( DT ),
		SCK( SCK ) 
        {}

unsigned long hx711::readCount(){
	DT.direction_set_output();
	DT.direction_flush();
	DT.write(1);
	SCK.write(0);
    DT.direction_set_input();
	DT.direction_flush();
	DT.refresh();
	unsigned char i;
	while(DT.read()){
		for(i=0; i<24; i++){	
			SCK.write(1);
			Count = Count << 1;
			SCK.write(0);
			DT.refresh();
			if(DT.read()){
				Count++;
			}
		}
	}
	SCK.write(1);
	Count=Count^0x800000;
	SCK.write(0);
	return Count;
}