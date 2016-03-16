//Reciever Code

//Libraries
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Initialize Variables and Transciever Code
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//-----------Alteration--------------
//    To keep wires together, and appearing more organized
int indicatorLED = 6;
//-----------------------------------

//Setup Void Code
void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(indicatorLED, OUTPUT);
}

//Void Loop Code
void loop(void){

//Declare Boolean Variable

//Checks for radio connection
 if (radio.available()){
   bool terminate = false;  
   
   //Always check for a command to be given from the transmitter
   while (!terminate){
     
     //Read the transmission being given from the transmiter
     terminate = radio.read(msg, 1);      
     
          
     //-----------Alteration--------------
     
     //     Code to determine the signal being received is
     
     delay(50);
     //If the termination button has been pressed
     if (msg[0] == 50 ){
       Serial.println("WARNING! TERMINATION PROTOCOLS ACTIVATED! COMMENCING EMERGENCY SHUTDOWN!");
       digitalWrite(indicatorLED, LOW);
       terminate = true;
     }
     //If the command to either deactivate the emergency protocals or to resume progress has been given
     else if(msg[0] == 90){
       Serial.println("All systems normal");
       digitalWrite(indicatorLED, HIGH);
     }
     delay(50);
     }
   }
   //-----------------------------------
   
 //If there is no detection of the transmitter, the reciever will shut down the motor
 //-----------Alteration--------------
 //     Had to add LED code and delay, for this is not just to indicate that there is no transmission. This is a
 //     condition in which determines wheter the LED remains on or off.
 else{
   Serial.println("WARNING! LOST CONNECTION WITH TRANSMITTER! COMMENCING EMERGENCY SHUTDOWN!");
   digitalWrite(indicatorLED, LOW);
   delay(100);
 }
 //-----------------------------------
}

