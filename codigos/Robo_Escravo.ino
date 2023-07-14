
#include <esp_now.h>
#include <WiFi.h>

#include<PWMOutESP32.h> // Bibliotteca para controle pwm com esp32

PWMOutESP32 pwm;

int  vel = 150; // Varialvel do valor PWM

//variaveis de mensagens enviadas via MAC
typedef struct struct_message {
  //char a[32];
  int x;
  int y;
  int comando;
} struct_message;

//estrutura de mensagens
struct_message myData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("Comando: ");
  //  Serial.println(myData.a);
  //  Serial.println();

//12, 13-f
//14- f,27
  
   if(myData.comando == 1) { //frente
    pwm.analogWrite(13, vel);
    pwm.analogWrite(12, 0);
    pwm.analogWrite(14, vel);
    pwm.analogWrite(27, 0);
    Serial.println("FRENTE");
  }
  if (myData.comando == 2) { //fundo

    pwm.analogWrite(12, vel);
    pwm.analogWrite(13, 0);
    pwm.analogWrite(27, vel);
    pwm.analogWrite(14, 0);
    Serial.println("FUNDO");

  }
  if (myData.comando == 3) { //Direita
    pwm.analogWrite(12, 0);
    pwm.analogWrite(13, vel);
    pwm.analogWrite(27, vel);
    pwm.analogWrite(14, 0);
    Serial.println("DIREITA");

  }
  if (myData.comando == 4) { //Esquerda

    pwm.analogWrite(12, vel);
    pwm.analogWrite(13, 0);
    pwm.analogWrite(14, vel);
    pwm.analogWrite(27, 0);
    Serial.println("ESQUERDA");

  }
   if (myData.comando == 5) { //Esquerda

    pwm.analogWrite(12, 0);
    pwm.analogWrite(13, 0);
    pwm.analogWrite(14, 0);
    pwm.analogWrite(27, 0);
    Serial.println("ESQUERDA");

  }
//  else{
//    pwm.analogWrite(12, 0);
//    pwm.analogWrite(13, 0);
//    pwm.analogWrite(14, 0);
//    pwm.analogWrite(27, 0);
//    Serial.println("PARA");
//  }
}
void setup() {
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  //  pwm.analogWrite(2,vel);//5
  //  pwm.analogWrite(4,vel);//6
  //  pwm.analogWrite(16,vel);//10
  //  pwm.analogWrite(17,vel); //9

  Serial.begin(115200);


  WiFi.mode(WIFI_STA);


  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {


}
