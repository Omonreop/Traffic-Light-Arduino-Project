#define BLYNK_TEMPLATE_ID "<blynk_template_id>"
#define BLYNK_TEMPLATE_NAME "Trafic Light"
#define BLYNK_AUTH_TOKEN "<auth_token_blynk>"

#define BLYNK_PRINT Serial

#include <LiquidCrystal_I2C.h>


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <ErriezRobotDyn4DigitDisplay.h>
BlynkTimer timer;
char ssid[] = "username";
char pass[] = "password";

#define EspSerial Serial2

#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);


#define BLYNK_GREEN     "#23C48E"
#define BLYNK_YELLOW    "#ED9D00"
#define BLYNK_RED       "#D3435C"

int lcdColumns = 20;
int lcdRows = 4;

#define TM1637_CLK_PIN      2
#define TM1637_DIO_PIN      3

#define EXTRA 3
#define Delay 5

RobotDyn4DigitDisplay display(TM1637_CLK_PIN, TM1637_DIO_PIN);
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

WidgetLED ledr1(V1);
WidgetLED ledy1(V2);
WidgetLED ledg1(V3);
WidgetLED ledr2(V4);
WidgetLED ledy2(V5);
WidgetLED ledg2(V6);
WidgetLED ledr3(V7);
WidgetLED ledy3(V8);
WidgetLED ledg3(V9);
WidgetLED ledr4(V10);
WidgetLED ledy4(V11);
WidgetLED ledg4(V12);

int timer1_counter;

const int green1Pin = 24;
const int yellow1Pin = 23; 
const int red1Pin = 22;

const int green2Pin = 27;
const int yellow2Pin = 26;
const int red2Pin = 25;

const int green3Pin = 30; 
const int yellow3Pin = 29;
const int red3Pin = 28;

const int green4Pin = 33;
const int yellow4Pin = 32;
const int red4Pin = 31;

const int pinSensor1=4;
const int pinSensor2=5;
const int pinSensor3=6;
const int pinSensor4=7;


int baca1;
int baca2;
int baca3;
int baca4;

static int minute = 0;
static int second = 0;
ISR(TIMER1_OVF_vect) 
{
  TCNT1 = timer1_counter; 


    baca1=digitalRead(pinSensor1);
    baca2=digitalRead(pinSensor2);
    baca3=digitalRead(pinSensor3);
    baca4=digitalRead(pinSensor4);

    if(second){
    display.time(minute, second, true, false);
    second--;
    }else{
      minute = 0;
      second = 0;
     display.time(minute, second, true, false);
     
    }


}

void setup() {

  Serial.begin(115200);

  pinMode(green1Pin, OUTPUT);
  pinMode(yellow1Pin, OUTPUT);
  pinMode(red1Pin, OUTPUT);

  pinMode(green2Pin, OUTPUT);
  pinMode(yellow2Pin, OUTPUT);
  pinMode(red2Pin, OUTPUT);

  pinMode(green3Pin, OUTPUT);
  pinMode(yellow3Pin, OUTPUT);
  pinMode(red3Pin, OUTPUT);

  pinMode(green4Pin, OUTPUT);
  pinMode(yellow4Pin, OUTPUT);
  pinMode(red4Pin, OUTPUT);


  lcd.init();
  lcd.backlight();

  display.begin();
  display.clear();
  display.setBrightness(4);

  lcd.setCursor(0, 0);
  lcd.print("Connect WIfi ...");
      
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, wifi, ssid, pass);

  ledr1.off();
  ledr2.off();
  ledr3.off();
  ledr4.off();
  delay(500);
  ledy1.off();
  ledy2.off();
  ledy3.off();
  ledy4.off();
  delay(500);
  ledg1.off();
  ledg2.off();
  ledg3.off();
  ledg4.off();
  delay(500);

    
  digitalWrite(red1Pin, HIGH);
  digitalWrite(red2Pin, HIGH);
  digitalWrite(red3Pin, HIGH);
  digitalWrite(red4Pin, HIGH);

  ledr1.on();
  ledr2.on();
  ledr3.on();
  ledr4.on();
   
  delay(500);

  pinMode(pinSensor1,INPUT_PULLUP);
  pinMode(pinSensor2,INPUT_PULLUP);
  pinMode(pinSensor3,INPUT_PULLUP);
  pinMode(pinSensor4,INPUT_PULLUP);

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;


  timer1_counter =3036;                          
  TCNT1 = timer1_counter; 
  TCCR1B |= (1 << CS12); 
  TIMSK1 |= (1 << TOIE1); 
  interrupts();
  lcd.clear();
}

void loop() {

  Blynk.run();
  
  // 1
  digitalWrite(red2Pin, HIGH);
  digitalWrite(red3Pin, HIGH);
  digitalWrite(red4Pin, HIGH);
  digitalWrite(red1Pin, LOW);
  digitalWrite(green1Pin, HIGH);

  ledr1.off();
  ledr2.on();
  ledr3.on();
  ledr4.on();
   BacaSensor();

  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);
  
  if(!baca1){
  second=Delay + EXTRA;
  }else{
   second=Delay;
  }
  display.time(minute, second, true, false); 
  ledg1.on();


  Blynk.run();
  delay(second*1000);
  
  digitalWrite(green1Pin, LOW);

  digitalWrite(red2Pin, HIGH);
  digitalWrite(yellow1Pin, HIGH);

  ledg1.off();
  ledr2.on();
  ledy1.on();
  BacaSensor();    
  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);
  delay(2000);
  digitalWrite(yellow1Pin, LOW);
  ledy1.off();




  // 2
  digitalWrite(red1Pin, HIGH);
  digitalWrite(red3Pin, HIGH);
  digitalWrite(red4Pin, HIGH);

  ledr1.on();
  ledr3.on();
  ledr4.on();

  delay(100);
  digitalWrite(red2Pin, LOW);
  digitalWrite(green2Pin, HIGH);
  BacaSensor(); 
  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);  
  if(!baca2){
  second=Delay + EXTRA;
  }else{
   second=Delay;
  }
  display.time(minute, second, true, false);
  ledr2.off();
  ledg2.on();

  Blynk.run();
  delay(second*1000);  

  digitalWrite(green2Pin, LOW);
  ledg2.off();
  
  delay(100);
  
  digitalWrite(red1Pin, HIGH);
  digitalWrite(yellow2Pin, HIGH);

  ledr1.on();
  ledy2.on();
  BacaSensor(); 
  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);   
  delay(2000);
  digitalWrite(yellow2Pin, LOW);
  digitalWrite(red1Pin, LOW);
  ledy2.off();
  ledr1.off();


  // 3
  digitalWrite(red1Pin, HIGH);
  digitalWrite(red2Pin, HIGH);
  digitalWrite(red4Pin, HIGH);

  ledr1.on();
  ledr2.on();
  ledr4.on();
  delay(100);
  digitalWrite(red3Pin, LOW);
  digitalWrite(green3Pin, HIGH);
  BacaSensor();
  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);  
 
  if(!baca3){
  second=Delay + EXTRA;
  }else{
   second=Delay;
  }
  display.time(minute, second, true, false);
  ledr3.off();
  ledg3.on();

  Blynk.run();
  delay(second*1000);

  digitalWrite(green3Pin, LOW);
  ledg3.off();
  delay(100);
  digitalWrite(red1Pin, HIGH);
  digitalWrite(yellow3Pin, HIGH);
  ledr1.on();
  ledy3.on();
  BacaSensor();
  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);
  delay(2000);
  digitalWrite(yellow3Pin, LOW);
  digitalWrite(red1Pin, LOW);



  // 4
  digitalWrite(red1Pin, HIGH);
  digitalWrite(red2Pin, HIGH);
  digitalWrite(red3Pin, HIGH);

  ledy3.off();
  ledr1.off();

  ledr1.on();
  ledr2.on();
  ledr3.on();
  
  delay(100);
  digitalWrite(red4Pin, LOW);
  digitalWrite(green4Pin, HIGH);
  BacaSensor();  
  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);  
  if(!baca4){
  second=Delay + EXTRA;
  }else{
   second=Delay;
  }
  display.time(minute, second, true, false);
  
  ledr4.off();
  ledg4.on();

  Blynk.run();
  delay(second*1000);

  digitalWrite(green4Pin, LOW);
  ledg4.off();

  delay(100);
  digitalWrite(red1Pin, HIGH);
  digitalWrite(yellow4Pin, HIGH);

  ledr1.on();
  ledy4.on();
  BacaSensor();
  DispLcd(digitalRead(green1Pin),digitalRead(yellow1Pin),digitalRead(red1Pin),digitalRead(green2Pin),digitalRead(yellow2Pin),digitalRead(red2Pin),digitalRead(green3Pin),digitalRead(yellow3Pin),digitalRead(red3Pin),digitalRead(green4Pin),digitalRead(yellow4Pin),digitalRead(red4Pin),baca1,baca2,baca3,baca4);  
  delay(2000);
  digitalWrite(yellow4Pin, LOW);
  digitalWrite(red1Pin, LOW);
  ledy4.off();
  ledr1.off();


}

void BacaSensor(){
Blynk.virtualWrite(V13, !baca1);
Blynk.virtualWrite(V14, !baca2);
Blynk.virtualWrite(V15, !baca3);
Blynk.virtualWrite(V16, !baca4);
}
    
void DispLcd(boolean R1,boolean Y1,boolean G1,boolean R2,boolean Y2,boolean G2,boolean R3,boolean Y3,boolean G3,boolean R4,boolean Y4,boolean G4,boolean S1,boolean S2,boolean S3,boolean S4){
lcd.setCursor(0, 0);
lcd.print("R1=");
lcd.print(!R1);
lcd.print(" ");
lcd.print("Y1=");
lcd.print(Y1);
lcd.print(" ");
lcd.print("G1=");
lcd.print(!G1);
lcd.print(" ");
lcd.print("S1=");
lcd.print(!S1);

lcd.setCursor(0, 1);
lcd.print("R2=");
lcd.print(!R2);
lcd.print(" ");
lcd.print("Y2=");
lcd.print(Y2);
lcd.print(" ");
lcd.print("G2=");
lcd.print(!G2);
lcd.print(" ");
lcd.print("S2=");
lcd.print(!S2);


lcd.setCursor(0, 2);
lcd.print("R3=");
lcd.print(!R3);
lcd.print(" ");
lcd.print("Y3=");
lcd.print(Y3);
lcd.print(" ");
lcd.print("G3=");
lcd.print(!G3);
lcd.print(" ");
lcd.print("S3=");
lcd.print(!S3);


lcd.setCursor(0, 3);
lcd.print("R4=");
lcd.print(!R4);
lcd.print(" ");
lcd.print("Y4=");
lcd.print(Y4);
lcd.print(" ");
lcd.print("G4=");
lcd.print(!G4);
lcd.print(" ");
lcd.print("S4=");
lcd.print(!S4);
}
