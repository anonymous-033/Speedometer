#include<SoftwareSerial.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 4, 5, 6, 7);

float timer1=0.0;
float timer2=0.0;

float Time=0.0;

int flag1 = 0;
int flag2 = 0;

float distance = 5.0;
float speed=0;

int sensor1 = 2;
int sensor2 = 3;

int buzzer = 13;

float speedLimit = 0.0;
String s;

void setup(){
  Serial.begin(9600);
  
  Serial.println("Enter Speed Limit: ");
  
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(4,0);
  lcd.print("DIGITAL");
  lcd.setCursor(2,1);
  lcd.print("SPEEDOMETER..");
  delay(500);
  
  while(Serial.available()>0)
  {
      s=Serial.readString();
      
//      Serial.println(s);
       
  }
  speedLimit=s.toFloat();
  Serial.println(".00 km/hr");
  //Serial.println(speedLimit);
  delay(500);
  lcd.clear();     
}

void loop() {
  

//  if(mySerial.available()>0)
//  {
//     s = mySerial.readString();
//     speedLimit = s.toInt();
//  }
//  Serial.println(s);
//  Serial.println(speedLimit);
if(digitalRead (sensor1) == HIGH && flag1==0){timer1 = millis(); flag1=1;}

if(digitalRead (sensor2) == HIGH && flag2==0){timer2 = millis(); flag2=1;}

if (flag1==1 && flag2==1){
     if(timer1 > timer2){Time = timer1 - timer2;}
else if(timer2 > timer1){Time = timer2 - timer1;}
 Time=Time/1000;
 speed=(distance/Time);
 speed=speed*3600;
 speed=speed/1000;
}

if(speed==0){ 
lcd.setCursor(0, 1); 
if(flag1==0 && flag2==0){lcd.print("NO CAR DETECTED ");}
                    else{lcd.print("  WAITING...    ");} 
}
else{
    lcd.clear(); 
    lcd.setCursor(0, 0); 
    lcd.print("SPEED:");
    lcd.print(speed,1);
    lcd.print("Km/Hr  ");
    lcd.setCursor(0, 1); 
    if(speed > speedLimit){lcd.print("  Over Speeding  "); digitalWrite(buzzer, HIGH);}
            else{lcd.print("  Normal Speed   "); }    
    delay(300);
    digitalWrite(buzzer, LOW);
    lcd.clear();
    speed = 0;
    flag1 = 0;
    flag2 = 0;    
 }
}
