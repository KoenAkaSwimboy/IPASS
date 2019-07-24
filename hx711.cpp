#include "hx711.hpp"

hx711::hx711(hwlib::pin_in & DT, hwlib::pin_out & SCK):	//constructor
		DT( DT ),
		SCK( SCK ) 
        {}

bool hx711::isReady(){									//check of de chip ready is
	DT.refresh();
	return !DT.read();									//the chip is ready if data pin is low (datasheet)
}

void hx711::waitReady(){								//wait till the chip is ready
	ready = isReady();
	tries=0;
	while(!ready and tries<maxT){
		ready = isReady();
		hwlib::wait_ms(1);
		tries++;
	}
	if(tries==maxT){									//the chip is not ready
		hwlib::cout<<" The chip is not ready please try again";
	}
}

void hx711::setGain(int gain){
	if(gain==128){										//gain 128 channel A
		GAIN=1;
	}else if(gain==64){									//gain 64 channel A
		GAIN=3;
	}else{												//gain 32 channel B
		GAIN=2;
	}
}

void hx711::powerOn(){									//turn the chip 'on' 
	SCK.write(0);
	hwlib::wait_us(1);									//wait 1 nano second to let the clock settle
}

void hx711::start(){									//default gain is 128
	setGain(128);
	powerOn();
}

void hx711::start(int gain){							//start the chip
	setGain(gain);
	powerOn();
}

unsigned long hx711::read(){							//get the data from the chip
	waitReady();										//wait till the chip is ready
	SCK.write(0);
	hwlib::wait_us(1);
	Data=0;												//make sure Data is 0
	for(unsigned char i=0; i<24; i++){	
		SCK.write(1);
		hwlib::wait_us(1);								//wait 1 nano second to let the clock settle
		Data<<=1;										//shift the bit out
		SCK.write(0);
		hwlib::wait_us(1);
		DT.refresh();
		if(DT.read()){
			Data++;
		}
	}
	nextConver();										//make the chip ready for the next conversion (datasheet)
	Data=(Data^0x800000);
	return Data;
}

void hx711::nextConver(){								//make the chip ready for the next conversion
	for(unsigned int j=0; j<GAIN; j++){					
		SCK.write(1);
		hwlib::wait_us(1);								//wait 1 nano second to let the clock settle
		SCK.write(0);
		hwlib::wait_us(1);								//wait 1 nano second to let the clock settle
	}
}

void hx711::setMaxT(int MAXT){							//set the maximum tries, defualt is 500
	maxT = MAXT;
}