#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledPin =  LED_BUILTIN;
const int ledPin2 = 13;
const long interval = 1000;

unsigned long previousMillis = 0;   
     
int ledState = LOW;   
int intToggle=0;  
int incomingByte;     

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  lcd.begin(16, 2); 
  pinMode(7,OUTPUT); 
  digitalWrite(7,HIGH); 
  
  lcd.print("Iniciando processos"); 
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    int sensorValue = analogRead(A0);
    float voltage = sensorValue * (5.0 / 1023.0);
    
    lcd.setCursor(0,0);
    lcd.print("");
    if(intToggle==0){
      lcd.print("Sensor1. ");
    }else if(intToggle==1){
      lcd.print("Sensor2. ");
    }else if(intToggle==2){
      lcd.print("Sensor3. ");
    }else if(intToggle==3){
      lcd.print("Sensor4. ");
    }else if(intToggle==4){
      lcd.print("Sensor5. ");
    }else{
      lcd.print("Envio de dados. ");
      intToggle=-1;
    }
    intToggle++;
    
    lcd.setCursor(0,1); 
    lcd.print("");
    lcd.print(voltage);
    lcd.print("v - ");
    lcd.print(millis()/1000);
    lcd.print("seg.");
    
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    if (Serial.available() > 0) {
      incomingByte = Serial.read();
      if (incomingByte == 'H') {
        digitalWrite(ledPin2, HIGH);
      }
      if (incomingByte == 'L') {
        digitalWrite(ledPin2, LOW);
      }
    }
  
    digitalWrite(ledPin, ledState);
    Serial.println(voltage);
  }

}
