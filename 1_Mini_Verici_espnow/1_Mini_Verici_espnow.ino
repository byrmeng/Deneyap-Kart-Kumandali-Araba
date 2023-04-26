#include "WiFi.h"
#include "esp_now.h"
#include <Deneyap_KumandaKolu.h>
Joystick KumandaKolu1;
Joystick KumandaKolu2;
uint8_t broadcastAddress[] ={0x94, 0x3C, 0xC6, 0xDA, 0xF2, 0xA4};
//uint8_t broadcastAddress[] ={0x44, 0x17, 0x93, 0x4C, 0xC7, 0x4C};
//uint8_t broadcastAddress[] ={0x44, 0x17, 0x93, 0x52, 0x8B, 0x84};
typedef struct struct_message {
  int x;
  int y;
  int c;
} struct_message;
struct_message myData;
esp_now_peer_info_t peerInfo;
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Veri gönderme başarılı" : "Veri gönderme başarısız");
}

void setup() {
  Serial.begin(115200);
  KumandaKolu2.begin(0x1A);
  KumandaKolu1.begin(0x1B);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return; 
  }
  esp_now_register_send_cb(OnDataSent);
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Eşleşme başarısız");
    return;
  }
}
void loop() {
  bool swState1 = KumandaKolu1.swRead();
  uint16_t xValue = KumandaKolu2.xRead();
  uint16_t yValue = KumandaKolu1.yRead();
  myData.x=xValue;
  myData.y=yValue;
  myData.c=swState1;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  delay(200);
}
