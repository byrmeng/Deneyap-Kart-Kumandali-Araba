#include "WiFi.h"
#include "esp_now.h"
#define MotorA1 D12
#define MotorA2 D13
#define MotorB1 D14
#define MotorB2 D15
int ileriHiz;
typedef struct struct_message{
  int x;
  int y;
  int c;
} struct_message;
struct_message myData;
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&myData, incomingData, sizeof(myData));
  //Serial.print("Buton Durumu: ");
  Serial.print("Y Eksen Verisi: ");
  if(myData.y>=515){
      myData.y=map(myData.y,505,755,0,250);
      if(myData.y>=20){ileri();}else{dur();}
      ileriHiz=myData.y;}else if(myData.y<=490){
      myData.y=map(myData.y,505,250,0,250);
      if(myData.y>=20){geri();}else{dur();}
      ileriHiz=myData.y;}
  else if(myData.x>=525){
      myData.x=map(myData.x,511,765,0,250);
      if(myData.x>=20){sol();}else{dur();}
      }else if(myData.x<=485){
      myData.x=map(myData.x,511,250,0,250);
      if(myData.x>=20){sag();}else{dur();}
      }else{
        dur();
      }
      Serial.println(myData.x);
}
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
void loop(){
}
void ileri(){
    analogWrite(MotorA1,ileriHiz);
    analogWrite(MotorA2,0);
    analogWrite(MotorB1,ileriHiz);
    analogWrite(MotorB2,0);
}
void geri(){
    analogWrite(MotorA1,0);
    analogWrite(MotorA2,ileriHiz);
    analogWrite(MotorB1,0);
    analogWrite(MotorB2,ileriHiz);
}
void sol(){
    analogWrite(MotorA1,0);
    analogWrite(MotorA2,0);
    analogWrite(MotorB1,125);
    analogWrite(MotorB2,125);
}
void sag(){
    analogWrite(MotorA1,125);
    analogWrite(MotorA2,125);
    analogWrite(MotorB1,0);
    analogWrite(MotorB2,0);
}
void dur(){
    analogWrite(MotorA1,0);
    analogWrite(MotorA2,0);
    analogWrite(MotorB1,0);
    analogWrite(MotorB2,0);
}
