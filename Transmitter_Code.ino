  //Transmitter Code
  
  //Libraries
  #include  <SPI.h>
  #include "nRF24L01.h"
  #include "RF24.h"
  
  //Initialize variables and Transciever Code
  int msg[1];
  RF24 radio(9,10);
  const uint64_t pipe = 0xE8E8F0F0E1LL;
  int inputSwitch = 7;
  
  //Setup Void Code
  void setup(void){
    Serial.begin(9600);
    radio.begin();
    radio.openWritingPipe(pipe);
  }
  
  //Loop Void Code
  void loop(void){
    
   //If the termination switch is pushed down
   if (digitalRead(inputSwitch) == HIGH){
     
     //Transmit to the other transmitter the "terminate code"
     msg[0] = 111;
     radio.write(msg, 1);
   }
   
   //If the terminatoin switch is not being pushed down
   else{
     //Transmit the "all clear" code
     msg[0]=500;
     radio.write(msg, 1);
     }
   }
