//  Dish 54.x remote I2C interface
//  TSI SYSTEMS - J. Spotanski 2021
 
#include "Wire.h"
#include <Arduino.h>

#define I2C_SLAVE_ADDR 52  //IN DECIMAL - 0x34 HEX (TEXAS INSTRUMENTS TCA8418 KEYPAD DECODER IC)
#define INTERRUPT_OUT 13


const int remoteTiming = 5;  //  1 FOR 54.1 REMOTES / 5 FOR 54.3 REMOTES

volatile byte readMode = 0; 
volatile int receivedValue = 0;

String command;
byte KEY_CMD;
byte KEY_RELEASE;
boolean needRelease;
boolean holdButton = 1;
boolean longholdButton = 0;
boolean debug = 1;          //debug mode 

// REGISTER VALUES
byte BLANK = 0x00;
byte CFG_REG = 0xA7;
byte INT_REG = 0x00;
byte EVT_REG = 0x00;

void setup(){
    Serial.begin(115200);
    Serial.flush();

    Serial.println("TSI SYSTEMS - Dish 54.1 / 54.3 Remote Interface");
    Serial.println("Rev 0.21s_54.3");
    Serial.println("'?' For list of commands");  
    
    if (debug){Serial.print("Starting up Slave as address...0x");}
    if (debug){Serial.println(I2C_SLAVE_ADDR, HEX);}  //display as hex
  
    Wire.begin(I2C_SLAVE_ADDR);
    Wire.onReceive(receiveEvent); 
    Wire.onRequest(requestEvent);
  
    pinMode(INTERRUPT_OUT, OUTPUT);   //moved
    digitalWrite(INTERRUPT_OUT, HIGH);  
    delay(100);  
  
    delay(500);  
    digitalWrite(INTERRUPT_OUT, LOW); //// grab and trash the init 
    delay(15);    
    digitalWrite(INTERRUPT_OUT, HIGH); 
    delay(500);  
    
    INT_REG = 0x01;
    EVT_REG = 0x01; 
}

void loop(){
   if (needRelease == 1) {
          sendrelease();
      }
	  
   if(Serial.available()>0){
     int inByte = Serial.read();
     Serial.flush();
     Serial.println(inByte);

     switch (inByte) {  
    	 case '1':
              KEY_CMD = 0xB6;
              KEY_RELEASE = 0x36;
              needRelease = 1;
              Trigger();
    		  break;
    
    	 case '2':
              KEY_CMD = 0xB7;
              KEY_RELEASE = 0x37;
              needRelease = 1;
              Trigger();
    		  break;
    
    	 case '3':
              KEY_CMD = 0xB8;
              KEY_RELEASE = 0x38;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '4':
              KEY_CMD = 0xB3;
              KEY_RELEASE = 0x33;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '5':
              KEY_CMD = 0xB4;
              KEY_RELEASE = 0x34;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '6':
              KEY_CMD = 0xB5;
              KEY_RELEASE = 0x35;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '7':
              KEY_CMD = 0xBD;
              KEY_RELEASE = 0x3D;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '8':
              KEY_CMD = 0xBE;
              KEY_RELEASE = 0x3E;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '9':
              KEY_CMD = 0xBF;
              KEY_RELEASE = 0x3F;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '0':
              KEY_CMD = 0xC1;
              KEY_RELEASE = 0x41;
              needRelease = 1;
              Trigger();
    		  break;
          


      default:
        Serial.println("INVALID COMMAND RECEIVED\n");                                                              
      }
  }
  
  delay(50);
}

void Trigger() {
      digitalWrite(INTERRUPT_OUT, LOW); 
      delay(remoteTiming);  
      digitalWrite(INTERRUPT_OUT, HIGH);
      delay(50);  //slow down cmds sent to remote mp
}

void sendrelease(){
    if (holdButton == 1) {
      delay(1700);
      holdButton = 0;
    }

    else if (longholdButton == 1)  {
      delay(5000);
      longholdButton = 0;
    }

    delay(90);
    needRelease = 0;
    if (debug){Serial.print("Sending release\n"); }
    KEY_CMD = KEY_RELEASE;
    delay(20);
    Trigger();
}

void requestEvent(){
  if(readMode == 1) {

    Wire.write(CFG_REG); // 0xA7
    Wire.write(INT_REG);// 0x00
    Wire.write(EVT_REG);// 0x00
    Wire.write(KEY_CMD); // sat - 0x8C 0x0C
    Wire.write(BLANK);
    Wire.write(BLANK);    
    Wire.write(BLANK);
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);
    Serial.println("COMMAND SENT"); 
    if (debug){Serial.println(KEY_CMD);}
    //delay(100);  //was 100
    }

    else if(readMode == 128) {
    Serial.println("GOT 0x80/n"); 
    }  
   
    else {
    if (debug){Serial.println("GOT DIFFERENT READ MODE"); }
    if (debug){Serial.println(readMode); }
    Serial.flush();
    }  
}

void receiveEvent(int howMany){
  if (debug){Serial.println("receive event");}
  byte byteCount = 0;
  byte byteCursor = 0;
  byte receivedValues[45];
  byte receivedByte = 0;
  byte command = 0;
  byte byteRead = 0;
  receivedValue = 0;
  while(0 < Wire.available()) // loop through all but the last
  {
    byteRead = Wire.read();
    
    if(byteCount == 0) {
      readMode = byteRead;
      command = byteRead;
      if (debug){Serial.print("COMMAND I GOT: ");}
      if (debug){Serial.println(command);}      
    } else {
      receivedByte = byteRead;
      if (debug){Serial.print("got more than a command: ");}
      receivedValues[byteCursor] = receivedByte;
      if (debug){Serial.println(receivedByte);}
      byteCursor++;
    }
    byteCount++;
    
  }
  for(byte otherByteCursor = byteCursor; otherByteCursor>0; otherByteCursor--) {
    receivedValue = receivedValue + receivedValues[otherByteCursor-1] * pow(256, byteCursor-1)  ;
    //Serial.println("qoot: ");
    if (debug){Serial.print(byteCursor-1);}
    if (debug){Serial.print(":");}
    if (debug){Serial.println(receivedValue);}
  }

  if(command == 2) { //command from microcontroller to clear keypress interrupt
    if (debug){Serial.println("clear interrupt");}
    //delay(200);
    byteRead = Wire.read();   //read one byte  / 0xFF for 54.3 / 0x00 for 54.1
    Wire.write(0x00);    //  0x00 for response back to microcontroller
    //Serial.flush();
   return;
 
  }  else { 
   return;
  }
}




 
