#include <SPI.h>
#include <mcp2515.h>

struct can_frame canSend;
struct can_frame canRecieve;
int buttonPin =4;  
int ledPin = 1; 
MCP2515 mcp2515(10);
static int check=0;


void setup() {
  canSend.can_id  = 0x103;
  canSend.can_dlc = 1;
  canSend.data[0] = 50;
    
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  while (!Serial);
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
}

void loop() {
   
   // if (mcp2515.readMessage(&canRecieve) == MCP2515::ERROR_OK) 
    //{
     // for (int i = 0; i<canRecieve.can_dlc; i++) 
      // {  // print the data
      //Serial.print(canRecieve.data[i],DEC);
    //}   
 //Serial.println();  
   // }
 //buttonState = digitalRead(buttonPin);

  digitalWrite(ledPin, HIGH);
 if(mcp2515.sendMessage(&canSend)==MCP2515::ERROR_FAILTX)
 {
  Serial.print("error due to bus arbitration");
 }
 
 delay(1000);
 Serial.println("send data");
     
}

