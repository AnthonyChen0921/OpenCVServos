#include <Servo.h>

int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;

Servo myservo;  // 定义Servo对象来控制
int pos = 0;    // 角度存储变量

unsigned long previousTimeLed1 = millis();
unsigned long previousTimeServo = millis();
long timeIntervalLed1 = 500;
long timeIntervalServo = 40;
int ledState1 = LOW;

unsigned long previousTimeSerialPrintPotentiometer = millis();
long timeIntervalSerialPrint = 2000;


void setup() {
  myservo.attach(9);  // 控制线连接数字9
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void servoWrite(){
  for (pos = 0; pos <= 160; pos ++) { // 0°到90°
      // in steps of 1 degree
      myservo.write(pos);              // 舵机角度写入
      delay(40);                       // 等待转动到指定角度
  }
    
}
void servoWrite2(){
  for (pos = 160; pos >= 0; pos --) { // 从90°到0°
      myservo.write(pos);              // 舵机角度写入
      delay(40);                       // 等待转动到指定角度
  }

}

void ledOn(){
  digitalWrite(led1, HIGH);
  delay(100);
  digitalWrite(led2, HIGH);
  delay(100);
  digitalWrite(led3, HIGH);
  delay(100);
  digitalWrite(led4, HIGH);
  delay(100);
}

void ledOff(){
  digitalWrite(led1, LOW);
  delay(100);
  digitalWrite(led2, LOW);
  delay(100);
  digitalWrite(led3, LOW);
  delay(100);
  digitalWrite(led4, LOW);
  delay(100);
}

void loop() {
  unsigned long currentTime = millis();
  servoWrite2();
  ledOn();
  delay(500);
  ledOff();
  delay(500);
  ledOn();
  delay(500);
  ledOff();
  delay(500);
  ledOn();
  delay(10000);
  servoWrite();
  ledOff();
  delay(2000);

}
