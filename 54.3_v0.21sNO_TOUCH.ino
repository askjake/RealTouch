
//  Dish 54.x remote I2C interface
//  DishIP 
//  Jacob Montgomery 2022
 
#include "Wire.h"
#include <Arduino.h>

#define I2C_SLAVE_ADDR 52  //IN DECIMAL - 0x34 HEX (TEXAS INSTRUMENTS TCA8418 KEYPAD DECODER IC)
#define INTERRUPT_OUT A3   
#define STARTUP_OUT A2   


const int remoteTiming = 5;  //  1 FOR 54.1 REMOTES / 5 FOR 54.3 REMOTES
String KEY_RELEASE_TIME_str;
volatile int KEY_RELEASE_TIME = 20;

volatile byte readMode = 0; 
volatile int receivedValue = 0;

String BUTTON;

String command;
byte KEY_CMD;
byte KEY_RELEASE;
boolean needRelease;
boolean holdButton = 0;
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


    Serial.println("DishIP - Dish 54.1 / 54.3 Remote Interface");
    Serial.println("Rev 0.21s_54.3");
    Serial.println("'?' For list of commands");  
    
    if (debug){Serial.print("Starting up Slave as address...0x");}
    if (debug){Serial.println(I2C_SLAVE_ADDR, HEX);}  //display as hex
  
    Wire.begin(I2C_SLAVE_ADDR);

    
    Wire.onReceive(receiveEvent); 
    Wire.onRequest(requestEvent);

  
    pinMode(INTERRUPT_OUT, OUTPUT);   //moved
    digitalWrite(INTERRUPT_OUT, HIGH);  
    pinMode(STARTUP_OUT, OUTPUT);   //moved
    digitalWrite(STARTUP_OUT, LOW);
    delay(1000);  
    digitalWrite(STARTUP_OUT, HIGH);  

    delay(1000);  
  
    delay(500);  
    digitalWrite(INTERRUPT_OUT, LOW); //// grab and trash the init 
    delay(15);    
    digitalWrite(INTERRUPT_OUT, HIGH); 
    delay(500);  

    Serial.println("DishIP - Dish 54.1 / 54.3 Remote Interface");
    Serial.println("Rev 0.21s_54.3");
    Serial.println("'?' For list of commands");  
    
    if (debug){Serial.print("Starting up Slave as address...0x");}
    if (debug){Serial.println(I2C_SLAVE_ADDR, HEX);}  //display as hex
    
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
       case 'r':
           if (Serial.available() > 0) {
              Serial.print("Enter time to release key: ");
              KEY_RELEASE_TIME_str = Serial.readString();
              KEY_RELEASE_TIME = KEY_RELEASE_TIME_str.toInt();
              Serial.println(KEY_RELEASE_TIME, DEC);
              //delay(1000);
           }
          break;
       
    	 case '1':
              KEY_CMD = 0xB6;
              KEY_RELEASE = 0x36;
              BUTTON = 1;
              needRelease = 1;
              Trigger();
    		  break;
    
    	 case '2':
              KEY_CMD = 0xB7;
              KEY_RELEASE = 0x37;
              BUTTON = 2;
              needRelease = 1;
              Trigger();
    		  break;
    
    	 case '3':
              KEY_CMD = 0xB8;
              KEY_RELEASE = 0x38;
              BUTTON = 3;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '4':
              KEY_CMD = 0xB3;
              KEY_RELEASE = 0x33;
              BUTTON = 4 ;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '5':
              KEY_CMD = 0xB4;
              KEY_RELEASE = 0x34;
              BUTTON = 5;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '6':
              KEY_CMD = 0xB5;
              KEY_RELEASE = 0x35;
              BUTTON = 6;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '7':
              KEY_CMD = 0xBD;
              KEY_RELEASE = 0x3D;
              BUTTON = 7;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '8':
              KEY_CMD = 0xBE;
              KEY_RELEASE = 0x3E;
              BUTTON = 8;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '9':
              KEY_CMD = 0xBF;
              KEY_RELEASE = 0x3F;
              BUTTON = 9;
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case '0':
              KEY_CMD = 0xC1;
              KEY_RELEASE = 0x41;
              BUTTON = "0";
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case 'A': //DIAMOND
              KEY_CMD = 0xC0;
              KEY_RELEASE = 0x40;
              BUTTON = "Diamond";
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case 'B':  // DOUBLE DIAMOND
              KEY_CMD = 0xC2;
              KEY_RELEASE = 0x42;
              BUTTON = "Double_Diamond";
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case 'C':  //VOL+
              KEY_CMD = 0xA9;
              KEY_RELEASE = 0x29;
              BUTTON = "Volume_Up";
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case 'D':  //VOL-
              KEY_CMD = 0xAC;
              KEY_RELEASE = 0x2C;
              BUTTON = "Volume_Down";
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case 'E':  //CH +
              KEY_CMD = 0xAB;
              KEY_RELEASE = 0x2B;
              BUTTON = "Channel_Up";
              needRelease = 1;
              Trigger();
    		  break;
    
    	 case 'F':  //CH -
              KEY_CMD = 0xAE;
              KEY_RELEASE = 0x2E;
              BUTTON = "Channel_Down";
              needRelease = 1;
              Trigger();
    		  break;
    
    	 case 'G':  // RECALL
              KEY_CMD = 0xAA;
              KEY_RELEASE = 0x2A;
              BUTTON = "Recall";
              needRelease = 1;
              Trigger();
    		  break;
                                                                            
    	 case 'H':  // MUTE
              KEY_CMD = 0xAD;
              KEY_RELEASE = 0x2D;
              BUTTON = "Mute";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'I':  // SKIP BACK
              KEY_CMD = 0x9F;
              KEY_RELEASE = 0x1F;
              BUTTON = "Skip_Back";
              needRelease = 1;
              Trigger();
    		  break;
                                                                            
    	 case 'J':  // REW
              KEY_CMD = 0x9F;
              KEY_RELEASE = 0x1F;
              BUTTON = "REW";
              needRelease = 1;
              holdButton = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'K':  // PAUSE / PLAY
              KEY_CMD = 0xA0;
              KEY_RELEASE = 0x20;
              BUTTON = "Play_Pause";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'L':   // SKIP FORWARD
              KEY_CMD = 0xA1;
              KEY_RELEASE = 0x21;
              BUTTON = "Skip_Forward";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'M':  // FFWD
              KEY_CMD = 0xA1;
              KEY_RELEASE = 0x21;
              BUTTON = "FFWD";
              needRelease = 1;
              holdButton = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'N':  // BACK
              KEY_CMD = 0xA2;
              KEY_RELEASE = 0x22;
              BUTTON = "Back";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'O':  // LIVE
              KEY_CMD = 0xA2;
              KEY_RELEASE = 0x22;
              BUTTON = "Live";
              needRelease = 1;
              holdButton = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'P':  // INFO
              KEY_CMD = 0xA4;
              KEY_RELEASE = 0x24;
              BUTTON = "Info";
              needRelease = 1;
              Trigger();
    		  break;
                                                                  
    	 case 'Q':  // HELP
              KEY_CMD = 0xA4;
              KEY_RELEASE = 0x24;
              BUTTON = "Help";
              needRelease = 1;
              holdButton = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'R':  // UP
              KEY_CMD = 0x96;
              KEY_RELEASE = 0x16;
              BUTTON = "Up";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'S':  //DOWN
              KEY_CMD = 0xA3;
              KEY_RELEASE = 0x23;
              BUTTON = "Down";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'T':  // LEFT
              KEY_CMD = 0x98;
              KEY_RELEASE = 0x18;
              BUTTON = "Left";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'U':  // RIGHT
              KEY_CMD = 0x9A;
              KEY_RELEASE = 0x1A;
              BUTTON = "Right";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'V':  // SELECT
              KEY_CMD = 0x99;
              KEY_RELEASE = 0x19;
              BUTTON = "Select";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'W':  // OPTIONS
              KEY_CMD = 0x95;
              KEY_RELEASE = 0x15;
              BUTTON = "Options";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'X':// VOICE  BUTTON
              KEY_CMD = 0x97;
              KEY_RELEASE = 0x17;
              BUTTON = "Voice";
              needRelease = 1;
              longholdButton = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'Y':  // DVR
              KEY_CMD = 0x8B;
              KEY_RELEASE = 0x0B;
              BUTTON = "DVR";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'Z': // HOME
              KEY_CMD = 0x8C;
              KEY_RELEASE = 0x0C;
              BUTTON = "Home";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'a':// guide
              KEY_CMD = 0x83;
              KEY_RELEASE = 0x03;
              BUTTON = "Guide";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'b':  // sat
              KEY_CMD = 0xEF;
              KEY_RELEASE = 0x6F;
              BUTTON = "SAT";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'c':  // tv
              KEY_CMD = 0xF0;
              KEY_RELEASE = 0x70;
              BUTTON = "TV";
              needRelease = 1;
              Trigger();
    		  break;
                                                                  
    	 case 'd': // aux
              KEY_CMD = 0xF1;
              KEY_RELEASE = 0x71;
              BUTTON = "AUX";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'e':  // input
              KEY_CMD = 0xF2;
              KEY_RELEASE = 0x72;
              BUTTON = "Input";
              needRelease = 1;
              Trigger();
    		  break;
                                                                   
    	 case 'f': // power
              KEY_CMD = 0x81;
              KEY_RELEASE = 0x01;
              BUTTON = "Power";
              needRelease = 1;
              Trigger();
    		  break;
          
    	 case 'g':  //UNPAIR REMOTE
              KEY_CMD = 0xEF;  //SAT button
              KEY_RELEASE = 0x6F;
              BUTTON = "SAT";
              needRelease = 1;
              longholdButton = 0;
              Trigger();
              requestEvent();
              delay(6000);    //PRESS AND HOLD SAT BUTTON TO START, THEN WAIT BEFORE PRESSING BOTH KEYS BELOW
              sendrelease();
              delay(4000);
              KEY_CMD = 0x8C;  //HOME button
              BUTTON = "Home";
              needRelease = 0;
              Trigger();
              requestEvent();       
              delay(50);
              KEY_CMD = 0x83;  //GUIDE button
              BUTTON = "Guide";
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
       case 'z': // 
              debug = 1;
              Serial.println("debug ON");
          break;
       case 'x': // 
              debug = 0;
              Serial.println("debug OFF");
                         
          break;
       case 'v': //     
              digitalWrite(STARTUP_OUT, LOW);
              delay(100);  
              digitalWrite(STARTUP_OUT, HIGH);  
              Serial.println("Starup");
                         
          break;
          
    	 case '?':  //HELP - COMMAND LISTING
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
    Serial.print("Key release time: ");
    Serial.println(KEY_RELEASE_TIME);
    delay(KEY_RELEASE_TIME);
    Trigger();
}
/////////////////////////////////////////////////////
void requestEvent(){
  if(readMode == 1) {                  

   
    Wire.write(CFG_REG);
    Serial.write(Wire.read());
    Wire.write(INT_REG);
    Serial.write(Wire.read());
    Wire.write(EVT_REG);
    Serial.write(Wire.read());
    Wire.write(KEY_CMD);
    Serial.write(Wire.read());
    Wire.write(BLANK);    
    Wire.write(BLANK);
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);        
    Wire.write(BLANK);
    Serial.print("COMMAND SENT: "); 
    Serial.println(BUTTON);
    //delay();  //was 100

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
///////////////////////////////////////////////////////////////////
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




 
