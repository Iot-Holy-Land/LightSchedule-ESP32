#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

#define BUZZER_PIN 17

Servo myservo;  // Servo 객체 생성


const char* ssid = "bssm_free";
const char* password = "bssm_free";

WebServer server(80);

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(16);  // Servo 모듈의 신호선을 ESP32의 4번 핀에 연결합니다.
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected");
  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/BE/send", []() {
    String param1 = server.arg("param1");
    Serial.println(param1);
    // 요청 처리 코드 작성
    server.send(200, "text/plain", "OK");
    if(param1 == "SUCCESS"){
      tone(BUZZER_PIN, 100); // 1kHz 주파수로 소리 출력
      myservo.write(90);  // 서보 모터를 90도로 회전합니다.
      delay(1000);       // 1초 대기
      myservo.write(0);   // 서보 모터를 0도로 회전합니다.
      
      int Light = analogRead(A0);
      Serial.println(Light);
      if(Light >= 1500){
        int a = 1;
      }
      delay(100);       // 1초 대기
    }
    if(param1 == "OFF"){
      noTone(BUZZER_PIN); // 소리 중지
      Serial.println("OFFOFFOFF");
      delay(1000); // 1초 동안 대기
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}