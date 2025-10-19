
#include <ESP8266WiFi.h>
#include <espnow.h>

// RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xAC, 0x0B, 0xFB, 0xF4, 0x33, 0xF0}; //AC:0B:FB:F4:33:F0


void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}
 
void loop() {
   
   uint8_t Data=0;
  
    /*recieving data from UART*/
   if(Serial.available()>0)
   {
 Data=Serial.read();
    /*send to 2nd ESP*/
   // delay(5);
    esp_now_send(broadcastAddress, (uint8_t*) &Data, sizeof(Data));
   }
   
    //Data++;
    //esp_now_send(broadcastAddress, (uint8_t*) &Data, sizeof(Data));
   // delay(5);
    
    
 Data=0;
  }
 
  
