

#include <ESP8266WiFi.h>
#include <espnow.h>


uint8_t Rec_Data=0;

/*MAC address of another esp*/
uint8_t broadcastAddress[] = {0x48, 0x55, 0x19, 0x16, 0x17,0x23};  

/*Callback function that will be executed when data is received*/
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) 
{
  memcpy(&Rec_Data, incomingData, sizeof(Rec_Data));
 
  /*send via USART*/
   Serial.write(Rec_Data);
}
 
void setup() {
  /* Initialize Serial Monitor*/
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  /* Init ESP-NOW*/
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
 /*to be Tx or Rx in same time*/ 
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO); 
  esp_now_register_recv_cb(OnDataRecv);
  delay(500);

  /*to add onther esp (also can be Tx or Rx in same time)*/
   esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0); 
}

void loop() {
  /*its just an additional feature but w.r.t STM--> Unidirectional communication */
    uint8_t Transmitted_Data=0;
  
   /*recieving data from UART*/
   
   if(Serial.available()>0)
   {
 Transmitted_Data=Serial.read();
    /*send to 2nd ESP via ESP NOW protocol*/
    esp_now_send(broadcastAddress, (uint8_t*) &Transmitted_Data, sizeof(Transmitted_Data));
      Serial.println("done");
    /*to maintain speed of STM32*/
    delay(30);
   }
   Transmitted_Data=0;
}

