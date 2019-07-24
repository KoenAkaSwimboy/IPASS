#include "hx711.hpp"
#include "ostream"

#define CATCH_CONFIG_MAIN  
#include "catch.hpp"

TEST_CASE( "start, one_parameter" ){
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d7 ); 
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );
    hx711 test(DT, SCK);
    test.start(64);
    REQUIRE(test.getGain() == 64);
    REQUIRE(test.getOn());
}

TEST_CASE( "start, default" ){
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d7 ); 
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );
    hx711 test(DT, SCK);
    test.start();
    REQUIRE(test.getGain() == 128);
    REQUIRE(test.getOn());
}

TEST_CASE( "setCalibrationW" ){
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d7 ); 
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );
    hx711 test(DT, SCK);
    test.setCalibrationW(50);
    REQUIRE(test.getCalWeight()==50);
}

TEST_CASE( "setTimes" ){
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d7 ); 
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );
    hx711 test(DT, SCK);
    test.setTimes(50);
    REQUIRE(test.getTimes()==50);
}

TEST_CASE( "setMaxT" ){
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d7 ); 
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );
    hx711 test(DT, SCK);
    test.setMaxT(200);
    REQUIRE(test.getMaxT()==200);
}

TEST_CASE( "nextConver" ){
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d7 ); 
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );
    hx711 test(DT, SCK);
    test.setGain(128);
    test.nextConver();
    REQUIRE(test.getNext()==1);
}

TEST_CASE( "read" ){                                    //Do nothing with the loadcell while running the code
    auto SCK = hwlib::target::pin_out( hwlib::target::pins::d7 ); 
    auto DT = hwlib::target::pin_in( hwlib::target::pins::d6 );
    hx711 test(DT, SCK);
    test.setGain(128);
    test.setMaxT(1000);
    unsigned long readingO = test.read();
    unsigned long readingT = test.read();
    int difference = readingO - readingT;
    REQUIRE(difference<100 and difference>-100);
    REQUIRE(test.getOn());
    REQUIRE(test.getNext()==1);
}