
#include<FirebaseESP8266.h>
#include<ESP8266WiFi.h>
#include<Servo.h>
#include<Wire.h>
#include<LiquidCrystal.h>
#include<ArduinoJson.h>


#define FIREBASE_HOST ""

#define FIREBASE_AUTH ""

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

FirebaseData firebaseData;

String Available= "";
String fireAvailable="";

LiquidCrystal lcd(16,5,4,0,2,14);

Servo myservo;
Servo myservos;


int Empty;
int allSpace=50;
int countYes=0;
int carEntered=D0;
int carExited=D4;
int TRIG=D7;
int ECHO=D8;
int led=D3;

int pos;
int pos1;
long duration, distance;


void setup() {
  // put your setup code here, to run once:

  delay(1000);
  Serial.begin(9600);
  Wire.begin(D2,D1);


  myservo.attach(D6);
  myservos.attach(D5);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(led, OUTPUT);
  pinMode(carExited, INPUT);
  pinMode(carEntered, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to...");
  Serial.print(WIFI_SSID);

  while(WiFi.status()!= WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to");
  Serial.print("IP Address is:");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  lcd.begin(16,2);
  lcd.home();

  lcd.setCursor(0,0);
  lcd.print("Smart Parking");

}

void loop() {
   //put your main code here, to run repeatedly:
//  take distance from ultrasonic sensor
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  //Calculate duration
  duration= pulseIn(ECHO, HIGH);

  //Calculate distance
  distance= (duration/2)/29.1;

  Serial.print("Centimeter:");
  Serial.print(distance);
  Firebase.pushString(firebaseData,"ParkingStatus/available/",fireAvailable);

//car enters at the gate
  int carEntry= digitalRead(carEntered);

  if(carEntry==LOW){
    countYes++;
  

  if(countYes>50){
    Serial.print("Parking is full");
    lcd.setCursor(0,1);
    lcd.print("Parking Full");
    Serial.print(countYes);
    delay(3000);
    lcd.clear();
  }
  
  else{
    Serial.print("Car entered");
    Serial.println(countYes);
    lcd.setCursor(0,1);
    lcd.print("Car entered");

    //open gate
    for(pos=45;pos<=140;pos+=1){
      myservos.write(pos);
      delay(5);
    }
//    Firebase.pushString(firebaseData,"ParkingStatus/available/",fireAvailable);
      Firebase.setString(firebaseData,"ParkingStatus/available",fireAvailable);
    lcd.clear();
  }
  }

  int carExited= digitalRead(carExited);
  if(carExited==LOW){
    countYes--;
  

  if(countYes<0){
      Serial.print("Parking Empty");
      Serial.print(countYes);
      lcd.setCursor(0,1);
      lcd.print("Parking Empty");
      countYes=0;
      delay(3000);
      lcd.clear();
    }

    else{
      Serial.print("Car Exited");
      Serial.print(countYes);
      lcd.setCursor(0,1);
      lcd.print("Car Exited");

      for(pos1=140; pos1>=45; pos1-=1){
        myservo.write(pos1);
        delay(5);
      }
      delay(3000);
      for(pos1=45; pos1<=140; pos1+=1){
        myservo.write(pos1);
        delay(5);
      }
     // Firebase.pushString(firebaseData,"ParkingStatus/available/",fireAvailable);

      Firebase.setString(firebaseData,"ParkingStatus/available",fireAvailable);
      lcd.clear();
    }
}


if(distance<6){
  Serial.println("Occupied");
  Firebase.setString(firebaseData,"Parking Space/p1", "1");
  digitalWrite(led, HIGH);
}

if(distance>6){
  Serial.println("Available");
  Firebase.setString(firebaseData,"Parking Space/p1", "0");
  digitalWrite(led, LOW);
}



Empty= allSpace-countYes;
Available= String("Available=") + String(Empty) + String("/") + String(allSpace);
fireAvailable= String("Available=") + String(Empty) + String("/") + String(allSpace);
lcd.setCursor(0,0);
lcd.print(Available);
}
