#include <Wire.h>
#include <math.h>

uint8_t MUX_ADR = 0x70;  // Replace with your actual I2C address
uint8_t MUX_BUS = 0x01;  // Replace with your actual bus number

#define MUX_1 0x70
#define MUX_2 0x72
#define MUX_3 0x74
#define MUX_4 0x76
#define ARDUINO_SLAVE_ADDR 0x34
#define TRIGGER_PIN 4
#define mux_reset 13
#define rf4ce_reset 2
uint8_t activePort = 0;
int remote;
/////////////////////////////////////
const int remoteTiming = 5;  //  1 FOR 54.1 REMOTES / 5 FOR 54.3 REMOTES
volatile int KEY_RELEASE_TIME = 30;
volatile byte readMode = 0;
volatile int receivedValue = 0;
String BUTTON;
String command;
byte KEY_CMD;
byte remoteSelect;
byte KEY_RELEASE;
boolean needRelease;
boolean holdButton = 0;
boolean longholdButton = 0;
int debug = 1;     //debug mode
boolean initFlag = 1;  // Flag triggers update to CFG_REG initalization string on powerup / reset
byte location;
byte CFG_REG;


int small_delay = 500;  //for between functions
int big_delay = 1000;



// REGISTER VALUES
byte BLANK = 0x00;
byte INT_REG = 0x00;
byte EVT_REG = 0x00;
/////////////////////////////////////
bool remoteCommandEntered = false;
void setup() {


  Wire.begin(ARDUINO_SLAVE_ADDR);  // Initialize I2C communication
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(mux_reset, OUTPUT);
  pinMode(rf4ce_reset, OUTPUT);
  digitalWrite(TRIGGER_PIN, HIGH);  // Set the trigger pin HIGH initially
  delay(600);
  digitalWrite(TRIGGER_PIN, LOW);  //// grab the init
  delay(15);
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(500);


  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("I2C Slave Initialized");
  reset_mux();
  //delay(100);
  reset_rf4ce();

  INT_REG = 0x01;
  EVT_REG = 0x01;
  selectPort(MUX_1, 0);  // Select default bus on startup
}
void loop() {
  if (needRelease == 1) {
    //delay(small_delay);
    sendrelease();
  }
  // Check if there is any input available
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');  // read the incoming string
    inputString.trim();                                 // remove any leading/trailing white space
    inputString.toLowerCase();                          // convert the input to lowercase

    if (inputString.startsWith("remote")) {
      remoteCommandEntered = true;
      unsigned int spaceIndex = inputString.indexOf(" ");  // find the index of the space
      if (spaceIndex != 0 && spaceIndex < inputString.length() - 1) {
        String remoteNumber = inputString.substring(spaceIndex + 1);  // extract the substring after the space
        remote = remoteNumber.toInt();                                // convert the substring to an integer
        Serial.print("remote: ");
        Serial.println(remote);
        //remoteSelect(remote); // call remoteSelect function with the remote number
      }
    } else if (inputString == "1") {
      KEY_CMD = 0xB6;
      KEY_RELEASE = 0x36;
      BUTTON = "1";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "2") {
      KEY_CMD = 0xB7;
      KEY_RELEASE = 0x37;
      BUTTON = "2";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "3") {
      KEY_CMD = 0xB8;
      KEY_RELEASE = 0x38;
      BUTTON = "3";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "4") {
      KEY_CMD = 0xB3;
      KEY_RELEASE = 0x33;
      BUTTON = "4";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "5") {
      KEY_CMD = 0xB4;
      KEY_RELEASE = 0x34;
      BUTTON = "5";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "6") {
      KEY_CMD = 0xB5;
      KEY_RELEASE = 0x35;
      BUTTON = "6";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "7") {
      KEY_CMD = 0xBD;
      KEY_RELEASE = 0x3D;
      BUTTON = "7";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "8") {
      KEY_CMD = 0xBE;
      KEY_RELEASE = 0x3E;
      BUTTON = "8";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "9") {
      KEY_CMD = 0xBF;
      KEY_RELEASE = 0x3F;
      BUTTON = "9";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "0") {
      KEY_CMD = 0xC1;
      KEY_RELEASE = 0x41;
      BUTTON = "0";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "diamond") {  //DIAMOND
      KEY_CMD = 0xC0;
      KEY_RELEASE = 0x40;
      BUTTON = "Diamond";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "double_diamond") {  // DOUBLE DIAMOND
      KEY_CMD = 0xC2;
      KEY_RELEASE = 0x42;
      BUTTON = "Double_Diamond";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "volume_up") {  //VOL+
      KEY_CMD = 0xA9;
      KEY_RELEASE = 0x29;
      BUTTON = "Volume_Up";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "volume_down") {  //VOL-
      KEY_CMD = 0xAC;
      KEY_RELEASE = 0x2C;
      BUTTON = "Volume_Down";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "channel_up") {  //CH +
      KEY_CMD = 0xAB;
      KEY_RELEASE = 0x2B;
      BUTTON = "channel_up";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "channel_down") {  //CH -
      KEY_CMD = 0xAE;
      KEY_RELEASE = 0x2E;
      BUTTON = "Channel_Down";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "recall") {  // RECALL
      KEY_CMD = 0xAA;
      KEY_RELEASE = 0x2A;
      BUTTON = "Recall";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "mute") {  // MUTE
      KEY_CMD = 0xAD;
      KEY_RELEASE = 0x2D;
      BUTTON = "Mute";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "skip_back") {  // SKIP BACK
      KEY_CMD = 0x9F;
      KEY_RELEASE = 0x1F;
      BUTTON = "Skip_Back";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "rew") {  // REW
      KEY_CMD = 0x9F;
      KEY_RELEASE = 0x1F;
      BUTTON = "REW";
      needRelease = 1;
      holdButton = 1;
      triggerMaster();
    } else if (inputString == "play_pause") {  // PAUSE / PLAY
      KEY_CMD = 0xA0;
      KEY_RELEASE = 0x20;
      BUTTON = "Play_Pause";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "skip_forward") {  // SKIP FORWARD
      KEY_CMD = 0xA1;
      KEY_RELEASE = 0x21;
      BUTTON = "Skip_Forward";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "ffwd") {  // FFWD
      KEY_CMD = 0xA1;
      KEY_RELEASE = 0x21;
      BUTTON = "FFWD";
      needRelease = 1;
      holdButton = 1;
      triggerMaster();
    } else if (inputString == "back") {  // BACK
      KEY_CMD = 0xA2;
      KEY_RELEASE = 0x22;
      BUTTON = "Back";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "live") {  // LIVE
      KEY_CMD = 0xA2;
      KEY_RELEASE = 0x22;
      BUTTON = "Live";
      needRelease = 1;
      holdButton = 1;
      triggerMaster();
    } else if (inputString == "info") {  // INFO
      KEY_CMD = 0xA4;
      KEY_RELEASE = 0x24;
      BUTTON = "Info";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "help") {  // HELP
      KEY_CMD = 0xA4;
      KEY_RELEASE = 0x24;
      BUTTON = "Help";
      needRelease = 1;
      holdButton = 1;
      triggerMaster();
    } else if (inputString == "up" || inputString == "R") {  // UP
      KEY_CMD = 0x96;
      KEY_RELEASE = 0x16;
      BUTTON = "Up";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "down" || inputString == "s") {  //DOWN
      KEY_CMD = 0xA3;
      KEY_RELEASE = 0x23;
      BUTTON = "Down";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "left" || inputString == "t") {  // LEFT
      KEY_CMD = 0x98;
      KEY_RELEASE = 0x18;
      BUTTON = "Left";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "right" || inputString == "u") {  // RIGHT
      KEY_CMD = 0x9A;
      KEY_RELEASE = 0x1A;
      BUTTON = "Right";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "select" || inputString == "v") {  // SELECT
      KEY_CMD = 0x99;
      KEY_RELEASE = 0x19;
      BUTTON = "Select";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "options" || inputString == "w") {  // OPTIONS
      KEY_CMD = 0x95;
      KEY_RELEASE = 0x15;
      BUTTON = "Options";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "voice") {  // VOICE BUTTON
      KEY_CMD = 0x97;
      KEY_RELEASE = 0x17;
      BUTTON = "Voice";
      needRelease = 1;
      longholdButton = 1;
      triggerMaster();
    } else if (inputString == "dvr") {  // DVR
      KEY_CMD = 0x8B;
      KEY_RELEASE = 0x0B;
      BUTTON = "DVR";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "home" || inputString == "z") {  // HOME
      KEY_CMD = 0x8C;
      KEY_RELEASE = 0x0C;
      BUTTON = "Home";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "guide" || inputString == "a") {  // guide
      KEY_CMD = 0x83;
      KEY_RELEASE = 0x03;
      BUTTON = "Guide";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "sat" || inputString == "b") {
      KEY_CMD = 0xEF;
      KEY_RELEASE = 0x6F;
      BUTTON = "SAT";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "tv") {
      KEY_CMD = 0xF0;
      KEY_RELEASE = 0x70;
      BUTTON = "TV";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "aux") {
      KEY_CMD = 0xF1;
      KEY_RELEASE = 0x71;
      BUTTON = "AUX";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "input") {
      KEY_CMD = 0xF2;
      KEY_RELEASE = 0x72;
      BUTTON = "Input";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "power") {
      KEY_CMD = 0x81;
      KEY_RELEASE = 0x01;
      BUTTON = "Power";
      needRelease = 1;
      triggerMaster();
    } else if (inputString == "unpair" || inputString == "v") {  //UNPAIR REMOTE
      KEY_CMD = 0xEF;                      //SAT button
      KEY_RELEASE = 0x6F;
      BUTTON = "SAT";
      needRelease = 1;
      longholdButton = 0;
      triggerMaster();
      requestEvent();
      delay(6000);  //PRESS AND HOLD SAT BUTTON TO START, THEN WAIT BEFORE PRESSING BOTH KEYS BELOW
      sendrelease();
      delay(4000);
      KEY_CMD = 0x8C;  //HOME button
      BUTTON = "Home";
      needRelease = 0;
      triggerMaster();
      requestEvent();
      delay(50);
      KEY_CMD = 0x83;  //GUIDE button
      BUTTON = "Guide";
      needRelease = 0;
      longholdButton = 0;
      triggerMaster();
      requestEvent();
      delay(8000);     // BOTH GUIDE AND HOME BUTTONS ARE PRESSED AND HELD, THEN RELEASED BELOW
      KEY_CMD = 0x0C;  //HOME release CMD
      needRelease = 0;
      triggerMaster();
      requestEvent();
      delay(5);
      KEY_CMD = 0x03;  //GUIDE release CMD
      needRelease = 0;
      triggerMaster();
      requestEvent();
    } else if (inputString == "debug") {
      debug = 1;
      Serial.println("debug ON");
    } else if (inputString == "debug off") {  //
      debug = 0;
      Serial.println("debug OFF");
    }
     else if (inputString == "debug hard") {  //
      debug = 2;
      Serial.println("debug hard");
    }
  }
  if (remoteCommandEntered) {
        //Wire.begin();
    // Determine the appropriate remote address based on the remote number
    uint8_t pcaAddress = MUX_1;  // intitialize default mux
    uint8_t port = 0;            // Initialize port to 0
    switch (remote) {
      case 1:
        remote = 1;
        pcaAddress = MUX_1;
        port = 0;
        selectPort(pcaAddress, port);
        break;
      case 2:
        remote = 2;
        pcaAddress = MUX_1;
        port = 1;
        selectPort(pcaAddress, port);
        break;
      case 3:
        remote = 3;
        pcaAddress = MUX_1;
        port = 2;
        selectPort(pcaAddress, port);
        break;
      case 4:
        remote = 4;
        pcaAddress = MUX_1;
        port = 3;
        selectPort(pcaAddress, port);
        break;
      case 5:
        remote = 5;
        pcaAddress = MUX_2;
        port = 0;
        selectPort(pcaAddress, port);
        break;
      case 6:
        remote = 6;
        pcaAddress = MUX_2;
        port = 1;
        selectPort(pcaAddress, port);
        break;
      case 7:
        remote = 7;
        pcaAddress = MUX_2;
        port = 2;
        selectPort(pcaAddress, port);
        break;
      case 8:
        remote = 8;
        pcaAddress = MUX_2;
        port = 3;
        selectPort(pcaAddress, port);
        break;
      case 9:
        remote = 9;
        pcaAddress = MUX_3;
        port = 0;
        selectPort(pcaAddress, port);
        break;
      case 10:
        remote = 10;
        pcaAddress = MUX_3;
        port = 1;
        selectPort(pcaAddress, port);
        break;
      case 11:
        remote = 11;
        pcaAddress = MUX_3;
        port = 2;
        selectPort(pcaAddress, port);
        break;
      case 12:
        remote = 12;
        pcaAddress = MUX_3;
        port = 3;
        selectPort(pcaAddress, port);
        break;
      case 13:
        remote = 13;
        pcaAddress = MUX_4;
        port = 0;
        selectPort(pcaAddress, port);
        break;
      case 14:
        remote = 14;
        pcaAddress = MUX_4;
        port = 1;
        selectPort(pcaAddress, port);
        break;
      case 15:
        remote = 15;
        pcaAddress = MUX_4;
        port = 2;
        selectPort(pcaAddress, port);
        break;
      case 16:
        remote = 16;
        pcaAddress = MUX_4;
        port = 3;
        selectPort(pcaAddress, port);
        break;
      default:
        Serial.println("Invalid remote number");
        break;
    }
    selectPort(pcaAddress, port);
    delay(10);
    //Wire.end();
    remoteCommandEntered = false;
  }
}
void triggerMaster() {
  //Wire.begin(ARDUINO_SLAVE_ADDR);
  if (debug == 1) { Serial.println("Triggering com with remote");}
  digitalWrite(TRIGGER_PIN, LOW);
  delay(remoteTiming);  // Trigger duration: 5ms
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(small_delay);
}
void reset_mux() {
  Serial.println("resetting MUX");
  digitalWrite(mux_reset, LOW);
  delay(5);
  digitalWrite(mux_reset, HIGH);
  delay(small_delay);
}
void reset_rf4ce() {
  Serial.println("Resetting all remotes");
  digitalWrite(rf4ce_reset, LOW);
  delay(small_delay);
  digitalWrite(rf4ce_reset, HIGH);
  //delay(small_delay);
}

void selectPort(uint8_t pcaAddress, uint8_t port) {
  if (debug == 1) { Serial.print("MUX address: ");
  Serial.print(pcaAddress, HEX);
  Serial.print("   port: ");
  Serial.println(port);}
  Wire.end();
  initFlag = 1;
  reset_mux();
  reset_rf4ce();
  delay(10);
  Wire.begin();
  Wire.beginTransmission(pcaAddress);
  Wire.write(1 << port);  // Set the bit for the desired port
  Wire.endTransmission();
  Wire.end();
  activePort = port;  // Update the active port
  if (debug == 1) { Serial.print("active port: ");
  Serial.println(activePort);}
  // Delay to allow the PCA9546A to switch to the selected port
  delay(10);
  //triggerMaster();
  Wire.begin(ARDUINO_SLAVE_ADDR);
  delay(10);

}
void sendrelease() {
  if (holdButton == 1) {
    delay(1500);
    holdButton = 0;
  } else if (longholdButton == 1) {
    delay(4000);
    longholdButton = 0;
  }
  //delay(small_delay);
  needRelease = 0;
  if (debug == 1) { Serial.println("Sending release"); }
  KEY_CMD = KEY_RELEASE;
  if (debug == 1) { Serial.print("Key release time: ");
  Serial.println(KEY_RELEASE_TIME);}
  delay(KEY_RELEASE_TIME);
  triggerMaster();
}

void requestEvent() {
  if (readMode == 1) {

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
    if (debug == 1) { Serial.print("COMMAND SENT  ");}
    if (debug == 1) { Serial.println(BUTTON); }
    //delay(100);  //was 100
  } else if (readMode == 128) {
    if (debug==2) { Serial.println("GOT 0x80");}
  } else {
    if (debug==2) { Serial.print("GOT DIFFERENT READ MODE  "); }
    if (debug==2) { Serial.println(readMode); }
    
    Serial.flush();
  }
  return;
  //delay(100);
}

void receiveEvent(int howMany) {
  if (debug==2) { Serial.println("receive event"); }
  byte byteCount = 0;
  byte byteCursor = 0;
  byte receivedValues[45];
  byte receivedByte = 0;
  byte command = 0;
  byte byteRead = 0;
  receivedValue = 0;
  while (0 < Wire.available())  // loop through all but the last
  {
    byteRead = Wire.read();

    if (byteCount == 0) {
      readMode = byteRead;
      command = byteRead;
      if (debug==2) { Serial.print("COMMAND I GOT: "); }
      if (debug==2) { Serial.println(command); }
    } else {
      receivedByte = byteRead;
      if (debug==2) { Serial.print("got more than a command: "); }
      receivedValues[byteCursor] = receivedByte;
      if (debug==2) { Serial.println(receivedByte); }
      byteCursor++;
    }
    byteCount++;
  }
  for (byte otherByteCursor = byteCursor; otherByteCursor > 0; otherByteCursor--) {
    receivedValue = receivedValue + receivedValues[otherByteCursor - 1] * pow(256, byteCursor - 1);
    //Serial.println("qoot: ");
    if (debug==2) { Serial.print(byteCursor - 1); }
    if (debug==2) { Serial.print(":"); }
    if (debug==2) { Serial.println(receivedValue); }
  }


  if (command == 1) {
    if (debug==2) { Serial.println("COMMAND 1 RECEIVED"); }
    if (initFlag) {  // allows setting of initFlag once during remote boot
      CFG_REG = receivedByte;
      initFlag = 0;
    }
    return;
  }


  if (command == 2) {  //command from microcontroller to clear keypress interrupt
    if (debug==2) { Serial.println("COMMAND 2 RECEIVED"); }
    if (debug==2) { Serial.println("clear interrupt"); }
    //delay(200);
    byteRead = Wire.read();  //read one byte  / 0xFF for 54.3 / 0x00 for 54.1
    if (debug==2) { Serial.print(" //read one byte  / 0xFF for 54.3 / 0x00 for 54.1   ");
    Serial.println(byteRead);}
    Wire.write(0x00);  //  0x00 for response back to microcontroller
        Wire.write(INT_REG);

                       //Serial.flush();
    return;

  } else {
    return;
  }
}
