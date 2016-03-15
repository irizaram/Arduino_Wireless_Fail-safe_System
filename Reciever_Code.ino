//Reciever Code

//Libraries
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

//Initialize Variables and Transciever Code
int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int indicatorLED = 3;

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
//  currentStatus - used to swap statuses of the reciever 
bool currentStatus = true;

//Checks for radio connection
 if (radio.available()){
   bool terminate = false;  
   
   //Always checks if termination command given (button)
   while (!terminate){
     terminate = radio.read(msg, 1);      
     
     //If the termination switch has been detected
     if (msg[0] == 111 ){
       currentStatus = true;
       delay(10);
       Serial.println("WARNING! TERMINATION PROTOCALS ACTIVATED! COMMENCING EMERGENCY SHUTDOWN!");
       digitalWrite(indicatorLED, LOW);
       terminate = true;
       delay(10);
     }
     
     //If the termination switch hasn't been detected yet
     else{
       Serial.println("All systems are normal");
       digitalWrite(indicatorLED, HIGH);
   }
   }
 }
 //If there is no detection of the transmitter, the reciever will shut down the motor
 else{
   //Check to see if transmitter is being detected
   if(msg[0] == 500){
     Serial.println("All systems are normal");
     digitalWrite(indicatorLED, HIGH);
   }
   else{
   Serial.println("WARNING! LOST CONNECTION WITH TRANSMITTER! COMMENCING EMERGENCY SHUTDOWN!");
   digitalWrite(indicatorLED, LOW);
   }
 }
}
