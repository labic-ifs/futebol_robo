
#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

bool btn1,btn2;
String ler;

Adafruit_MPU6050 mpu;

//endereço MAC
uint8_t broadcastAddress[] = {0xF0, 0x08, 0xD1, 0xD2, 0x7B, 0x04}; //F0:08:D1:D2:55:BC //Ed2 = F0:08:D1:D2:7B:04
//F0:08:D1:D2:F5:CC

typedef struct struct_message {
  int x;
  int y;
 int comando;
} 
struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {

  Serial.begin(115200);
   while (!Serial)
    delay(10); 
 
  WiFi.mode(WIFI_STA);

  pinMode(16,INPUT);
   pinMode(17,INPUT);  
 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  
  esp_now_register_send_cb(OnDataSent);
  
 
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() {

 

  char ler = Serial.read(); //VARIÁVEL RESPONSÁVEL POR RECEBER O COMANDO DIGITADO NA ENTRADA DE DADOS DO MONITOR SERIAL

    if (ler == 'F'){ 
      myData.comando = 1;
      Serial.println("Frente"); //IMPRIME O TEXTO NO MONITOR SERIAL
    }
    if (ler == 'T'){ 
      myData.comando = 2;
      Serial.println("Traz"); //IMPRIME O TEXTO NO MONITOR SERIAL
    }
    if (ler == 'D'){ 
      myData.comando = 3;
      Serial.println("Direita"); //IMPRIME O TEXTO NO MONITOR SERIAL
    }
    if (ler == 'E'){ 
      myData.comando = 4;
      Serial.println("Esquerda"); //IMPRIME O TEXTO NO MONITOR SERIAL
    }
     if (ler == 'P'){ 
      myData.comando = 5;
      Serial.println("Para"); //IMPRIME O TEXTO NO MONITOR SERIAL
    }
  

//  btn1 = digitalRead(16);
//  btn2 = digitalRead(17);
//  
//  if(btn1){
//    myData.x = 1;
//    Serial.println("FRENTE");
//    Serial.println(myData.x);
//  }
//  else if(btn2){
//    myData.x = 2;
//    Serial.println("FUNDO");
//    Serial.println(myData.x);
//  }
//  else{
//    myData.x = 0;
//    Serial.println("PARA");
//    Serial.println(myData.x);
//  }
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(200);
}
