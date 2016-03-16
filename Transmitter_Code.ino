  //Transmitter Code
  
  //Libraries
  #include  <SPI.h>
  #include "nRF24L01.h"
  #include "RF24.h"
  
  //Initialize variables and Transciever Code
  int msg[1];
  RF24 radio(9,10);
  const uint64_t pipe = 0xE8E8F0F0E1LL;
  //-----------Alteration--------------
  //    Changed input switch location so the wires remained closer together, and appeared neat and organized
  //    and implemented boolean value to determine which signal to transmit
  int inputSwitch = 8;
  boolean currentStatus = false;
  //-----------------------------------
  
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
     
     //-----------Alteration--------------
     //   Created boolean system to determine which signal to transmit. Also implemented delays so that the
     //   signal doesn't change to rapidly as the button is being pressed.
     
     //If the current status is all clear, transmit to the "emergency protocol command"
     if(currentStatus == false){
       currentStatus = true;
     }
     //If the "emergency protocol command" is being given, and the button is pressed again, cancel the command, and resume proper protocol
     else{
       currentStatus = false;
     }
     delay(100);
   }
   //-----------------------------------
   
   //Determinne the kind of signal to transmit
   
   //-----------Alteration--------------
   //   Implemented new signal to be transmitted, assuring that the transmitter is always being detected by the receiver.
   //-If the "emergency protocol command" has been given
   if(currentStatus == true){
     msg[0] = 50;
   }
   //-If the "emergency protocol command" has not been given, or has been canceled
   else if(currentStatus == false){
     msg[0]=90;
   }
   //-----------------------------------
   //Transmit the coommand to the receiver
   radio.write(msg, 1);
 }
