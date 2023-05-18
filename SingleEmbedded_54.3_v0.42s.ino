

// Dish 54.x remote I2C interface
//
// Copyright (c) 2021-2022 - Dish Technologies - TSI Systems - Jason Spotanski
// All Rights Reserved
//
// Redistribution and use of this source code and binary forms, with or without modification,
// are permitted provided that redistributions and use of source code must retain the above ownership, copyright notice and revision history.
//
//  v0.11  8/2021 - JS
//    -Original test release
//
//  v0.21 11/2021 - JS
//    -Converted to single character commands and remove LF requirement from command
//
//  v0.30 03/2022 - JS
//    - Added remote reset capability
//    - Added four-hour idle auto remote hardware reset to improve reliability
//    
//  v0.31 03/25/2022 - JS
//    - Increase delays in Trigger and sendrelease
//
//  v0.32 09/27/2022 - JS
//    - Added 20ms delay to sendRelease to prevent stuck button press cmd
// 
//  v0.33 10/3/2022 - JS
//    - Increased delay to 50ms on sendRelease to further help with stuck key issue
//
//  V0.40 10/7/2022 - JS
//    - Added dynamic configuration register value - read keypad decode configuration on startup and set CFG_REG based on init string to prevent issues with firmware updates
//    
//  V0.41 10/10/2022 - JS
//    - Set initFlag upon remote reset to refetch configuration byte
//  
//  V0.42 10/27/2022 - JS
//    - Add press/hold HOME button (for quick SYSINFO on ATV STBs only)
//    - Add press/hold for DIAMOND buttons

// BASED ON SPARKFUN PRO MINI 3.3v
// NOTES: DISABLE Q12 ON ALL REMOTES TO DISABLE BACKLIGHT.

 
#include "Wire.h"
#include <Arduino.h>

String ver = "Rev 0.42_54.3";

#define I2C_SLAVE_ADDR 52  //IN DECIMAL - 0x34 HEX (TEXAS INSTRUMENTS TCA8418 KEYPAD DECODER IC)
#define INTERRUPT_OUT 13   //DIGITAL PIN TO TRIGGER INTERRUPT - PULLED LOW TO TRIGGER
#define REMOTE_1 4  //RESET PIN FOR REMOTE 1

const int remoteTiming = 5;  //  1 FOR 54.1 REMOTES / 5 FOR 54.3 REMOTES

volatile byte readMode = 0; //different readModes 
volatile int receivedValue = 0;

const unsigned long fourHour = 1000UL * 60UL * 60UL * 4UL;  //FOUR HOUR COUNTER FOR REMOTE RESET
unsigned long previousMillis = 0;
unsigned int idleCounter = 0;

String command;
byte KEY_CMD;
byte KEY_RELEASE;
boolean needRelease;
boolean holdButton = 0;
boolean longholdButton = 0;
boolean initFlag = 1;     // Flag triggers update to CFG_REG initalization string on powerup / reset

boolean debug = 0;          //debug mode 

byte location;
byte CFG_REG;

// REGISTER VALUES
byte BLANK = 0x00;
byte INT_REG = 0x00;
byte EVT_REG = 0x00;

void setup(){
  pinMode(REMOTE_1, OUTPUT);
  digitalWrite(REMOTE_1, HIGH);  //activate remote
  
  Serial.begin(115200);
  Serial.flush();
  Serial.println("TSI SYSTEMS - Dish 54.1 / 54.3 Remote Interface");

  Serial.println(ver);
  Serial.println("'?' For list of commands");  
  if (debug){Serial.print("Starting up Slave as address...0x");}
  if (debug){Serial.println(I2C_SLAVE_ADDR, HEX);}  //display as hex

  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onReceive(receiveEvent); 
  Wire.onRequest(requestEvent);

  pinMode(INTERRUPT_OUT, OUTPUT);   
  digitalWrite(INTERRUPT_OUT, HIGH);  
  delay(100);  

  delay(500);  
  digitalWrite(INTERRUPT_OUT, LOW); //// grab the init 
  delay(15);    
  digitalWrite(INTERRUPT_OUT, HIGH); 
  delay(500);  

  INT_REG = 0x01;
  EVT_REG = 0x01; 
  resetRemotes();
  
}

void loop(){
   if (needRelease == 1){
	  delay(50);
      sendrelease();
   }
      
   unsigned long currentMillis = millis();

   if (currentMillis - previousMillis >= fourHour){  // RESET REMOTE WHEN SITTING IDLE
      previousMillis = currentMillis;
      
      idleCounter++;
      if( idleCounter == 1)
          {
            Serial.println( "-IDLE RESET OF ALL REMOTES-");
            resetRemotes();
            idleCounter = 0;
          }
   }	

   if (debug){Serial.print("CFG_REG Value...0x");}
   if (debug){Serial.println(CFG_REG, HEX);}   //Debug display of CFG_REG value
     
   if(Serial.available()>0){
     int inByte = Serial.read();
     Serial.flush();
     if (debug){Serial.println(inByte);}

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
      
	 case 'A': //DIAMOND
          KEY_CMD = 0xC0;
          KEY_RELEASE = 0x40;
          needRelease = 1;
          Trigger();
		  break;
      
	 case 'B':  // DOUBLE DIAMOND
          KEY_CMD = 0xC2;
          KEY_RELEASE = 0x42;
          needRelease = 1;
          Trigger();
		  break;
      
	 case 'C':  //VOL+
          KEY_CMD = 0xA9;
          KEY_RELEASE = 0x29;
          needRelease = 1;
          Trigger();
		  break;
      
	 case 'D':  //VOL-
          KEY_CMD = 0xAC;
          KEY_RELEASE = 0x2C;
          needRelease = 1;
          Trigger();
		  break;
      
	 case 'E':  //CH +
          KEY_CMD = 0xAB;
          KEY_RELEASE = 0x2B;
          needRelease = 1;
          Trigger();
		  break;

	 case 'F':  //CH -
          KEY_CMD = 0xAE;
          KEY_RELEASE = 0x2E;
          needRelease = 1;
          Trigger();
		  break;

	 case 'G':  // RECALL
          KEY_CMD = 0xAA;
          KEY_RELEASE = 0x2A;
          needRelease = 1;
          Trigger();
		  break;
                                                                        
	 case 'H':  // MUTE
          KEY_CMD = 0xAD;
          KEY_RELEASE = 0x2D;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'I':  // SKIP BACK
          KEY_CMD = 0x9F;
          KEY_RELEASE = 0x1F;
          needRelease = 1;
          Trigger();
		  break;
                                                                        
	 case 'J':  // REW
          KEY_CMD = 0x9F;
          KEY_RELEASE = 0x1F;
          needRelease = 1;
          holdButton = 1;
          Trigger();
		  break;
                                                               
	 case 'K':  // PAUSE / PLAY
          KEY_CMD = 0xA0;
          KEY_RELEASE = 0x20;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'L':   // SKIP FORWARD
          KEY_CMD = 0xA1;
          KEY_RELEASE = 0x21;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'M':  // FFWD
          KEY_CMD = 0xA1;
          KEY_RELEASE = 0x21;
          needRelease = 1;
          holdButton = 1;
          Trigger();
		  break;
                                                               
	 case 'N':  // BACK
          KEY_CMD = 0xA2;
          KEY_RELEASE = 0x22;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'O':  // LIVE
          KEY_CMD = 0xA2;
          KEY_RELEASE = 0x22;
          needRelease = 1;
          holdButton = 1;
          Trigger();
		  break;
                                                               
	 case 'P':  // INFO
          KEY_CMD = 0xA4;
          KEY_RELEASE = 0x24;
          needRelease = 1;
          Trigger();
		  break;
                                                              
	 case 'Q':  // HELP
          KEY_CMD = 0xA4;
          KEY_RELEASE = 0x24;
          needRelease = 1;
          holdButton = 1;
          Trigger();
		  break;
                                                               
	 case 'R':  // UP
          KEY_CMD = 0x96;
          KEY_RELEASE = 0x16;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'S':  //DOWN
          KEY_CMD = 0xA3;
          KEY_RELEASE = 0x23;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'T':  // LEFT
          KEY_CMD = 0x98;
          KEY_RELEASE = 0x18;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'U':  // RIGHT
          KEY_CMD = 0x9A;
          KEY_RELEASE = 0x1A;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'V':  // SELECT
          KEY_CMD = 0x99;
          KEY_RELEASE = 0x19;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'W':  // OPTIONS
          KEY_CMD = 0x95;
          KEY_RELEASE = 0x15;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'X':  // VOICE BUTTON
          KEY_CMD = 0x97;
          KEY_RELEASE = 0x17;
          needRelease = 1;
          longholdButton = 1;
          Trigger();
		  break;
                                                               
	 case 'Y':  // DVR
          KEY_CMD = 0x8B;
          KEY_RELEASE = 0x0B;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'Z': // HOME
          KEY_CMD = 0x8C;
          KEY_RELEASE = 0x0C;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'a':// guide
          KEY_CMD = 0x83;
          KEY_RELEASE = 0x03;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'b':  // sat
          KEY_CMD = 0xEF;
          KEY_RELEASE = 0x6F;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'c':  // tv
          KEY_CMD = 0xF0;
          KEY_RELEASE = 0x70;
          needRelease = 1;
          Trigger();
		  break;
                                                              
	 case 'd': // aux
          KEY_CMD = 0xF1;
          KEY_RELEASE = 0x71;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'e':  // input
          KEY_CMD = 0xF2;
          KEY_RELEASE = 0x72;
          needRelease = 1;
          Trigger();
		  break;
                                                               
	 case 'f': // power
          KEY_CMD = 0x81;
          KEY_RELEASE = 0x01;
          needRelease = 1;
          Trigger();
		  break;
      
	 case 'g':  //UNPAIR REMOTE
          KEY_CMD = 0xEF;  //SAT button
          KEY_RELEASE = 0x6F;
          needRelease = 0;
          longholdButton = 0;
          Trigger();
          requestEvent();
          delay(6000);    //PRESS AND HOLD SAT BUTTON TO START, THEN WAIT BEFORE PRESSING BOTH KEYS BELOW
          sendrelease();
          delay(4000);
          KEY_CMD = 0x8C;  //HOME button
          needRelease = 0;
          Trigger();
          requestEvent();       
          delay(50);
          KEY_CMD = 0x83;  //GUIDE button
          needRelease = 0;
          longholdButton = 0;
          Trigger();    
          requestEvent();       
          delay(8000);  // BOTH GUIDE AND HOME BUTTONS ARE PRESSED AND HELD, THEN RELEASED BELOW
          KEY_CMD = 0x0C;  //HOME release CMD
          needRelease = 0;
          Trigger();
          requestEvent();
          delay(50);
          KEY_CMD = 0x03;  //GUIDE release CMD 
          needRelease = 0;       
          Trigger();
          requestEvent();
		  break;

	 case 'h':  // PRESS / HOLD HOME
          KEY_CMD = 0x8C;
      	  KEY_RELEASE = 0x0C;
          needRelease = 1;
          holdButton = 1;
          Trigger();
		  break;

	 case 'i':  // PRESS / HOLD DIAMOND
          KEY_CMD = 0xC0;
      	  KEY_RELEASE = 0x40;
          needRelease = 1;
          holdButton = 1;
          Trigger();
		  break;

	 case 'j':  // PRESS / HOLD DOUBLE DIAMOND
          KEY_CMD = 0xC2;
      	  KEY_RELEASE = 0x42;
          needRelease = 1;
          holdButton = 1;
          Trigger();
		  break;            


   case '=': // RESET ALL REMOTES 
          resetRemotes();
          break;
   
   
   case '?':  //HELP - COMMAND LISTING
	    Serial.println("TSI SYSTEMS - Dish 54.1 / 54.3 Remote Interface");
        Serial.println(ver);
        Serial.println("0-9 - 'NUMERIC KEYS'");
		Serial.println("A - 'DIAMOND KEY'");
		Serial.println("B - 'DOUBLE DIAMOND KEY'");
		Serial.println("C - VOL+");
		Serial.println("D - VOL -");
		Serial.println("E - CH+");
		Serial.println("F - CH-");
		Serial.println("G - RECALL");
		Serial.println("H - MUTE");
		Serial.println("I - 'SKIP BACK'");
		Serial.println("J - REW");
		Serial.println("K - PAUSEPLAY");
		Serial.println("L - 'SKIP FORWARD'");
		Serial.println("M - FFWD");
		Serial.println("N - BACK");
		Serial.println("O - LIVE");
		Serial.println("P - INFO");
		Serial.println("Q - HELP");
		Serial.println("R - UP");
		Serial.println("S - DOWN");
		Serial.println("T - LEFT");
		Serial.println("U - RIGHT");
		Serial.println("V - SELECT");
		Serial.println("W - OPTIONS");
		Serial.println("X - VOICE");
		Serial.println("Y - DVR");
		Serial.println("Z - HOME");
		Serial.println("a - GUIDE");
		Serial.println("b - SAT");
		Serial.println("c - TV");
		Serial.println("d - AUX");
		Serial.println("e - INPUT");
		Serial.println("f - POWER");
		Serial.println("g - UNPAIR - 'REMOTE UNPAIR FROM STB / WILL TAKE SEVERAL SECONDS'");
		Serial.println("h - PRESS/HOLD HOME");
		Serial.println("i - PRESS/HOLD DIAMOND");
		Serial.println("j - PRESS/HOLD DOUBLE DIAMOND");
        Serial.println();
        Serial.println("= - HARDWARE RESET REMOTE");
		break;
      
    default:
        Serial.println("INVALID COMMAND RECEIVED\n");                                                              
     }
  }
  delay(50);
}

void resetRemotes(){
      digitalWrite(REMOTE_1, LOW);  //REMOTES TO RESET STATE
      initFlag = 1;     // Set initFlag flag to trigger relearn of CFG_REG configuration parameters (firmware updates)
      delay(200);
      if (debug){Serial.println("RESET REMOTES COMPLETE");}
      digitalWrite(REMOTE_1, HIGH);  //enable remote
}

void Trigger() {
      digitalWrite(INTERRUPT_OUT, LOW); 
      delay(remoteTiming);  
      digitalWrite(INTERRUPT_OUT, HIGH);
      delay(60);  //slow down cmds sent to remote mp
      previousMillis = millis(); // RESTART IDLE REMOTE RESET COUNTDOWN
      
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
    delay(120);
    needRelease = 0;
    if (debug){Serial.print("Sending release\n"); }
    KEY_CMD = KEY_RELEASE;
    delay(20);
    Trigger();
   //return;  
      }

void requestEvent(){
  if(readMode == 1) {

    Wire.write(CFG_REG);
    Wire.write(INT_REG);
    Wire.write(EVT_REG);
    Wire.write(KEY_CMD);
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
    //
    Serial.flush();
    }  
   //return;
  //delay(100);
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
    
    if(byteCount ==0) {
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


  if(command == 1) { 
    if (debug){Serial.println("COMMAND 1 RECEIVED");}
    if (initFlag){      // allows setting of initFlag once during remote boot  
      CFG_REG = receivedByte;
      initFlag = 0;
      }  
    return;
  } 


  if(command == 2) { //command from microcontroller to clear keypress interrupt
    if (debug){Serial.println("COMMAND 2 RECEIVED");}
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




 
