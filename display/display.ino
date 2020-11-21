#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledPin =  LED_BUILTIN;
const int ledPin2 = 13;
const long interval = 1000;

unsigned long previousMillis = 0;   
     
int ledState = LOW;   
int intToggle=0;  
int incomingByte;     

/////
int tempValue=0; 
int lumiValue=0; 
int proxValue=0; 
int umidValue=0; 
/////

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  lcd.begin(16, 2); 
  pinMode(7,OUTPUT); 
  digitalWrite(7,HIGH); 
  
  lcd.print("Iniciando processos.    "); 
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
      lcd.print("System                ");
      lcd.setCursor(0,1); 
      lcd.print("");
      lcd.print(voltage);
      lcd.print("v|");
      lcd.print(millis()/1000);
      lcd.print("s|");
    }else if(intToggle==1){
      lcd.print("Temperatura.          ");
      lcd.setCursor(0,1); 
      lcd.print("");
      lcd.print(tempValue);
      lcd.print(" Celsios .            ");
    }else if(intToggle==2){
      lcd.print("Fotoresistor LDR      ");
      lcd.setCursor(0,1); 
      lcd.print("");
      lcd.print(lumiValue);
      lcd.print(" ohms .               ");
    }else if(intToggle==3){
      lcd.print("Infravermelho.        ");
      lcd.setCursor(0,1); 
      lcd.print("");
      lcd.print(proxValue);
      lcd.print(" cm .                 ");
    }else if(intToggle==4){
      lcd.print("Higrômetro            ");
      lcd.setCursor(0,1); 
      lcd.print("");
      lcd.print(umidValue);
      lcd.print(" umidade .            ");
    }else{
      lcd.print("Envio de dados.       ");
      intToggle=-1;
    }
    intToggle++;
    
    
    
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
