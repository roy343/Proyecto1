#include <LiquidCrystal.h>

const int A = 2;
const int B = 3;
const int C = 4;
const int TRIG = 5;
const int ECHO = 6;
const int test = 7;

LiquidCrystal lcd_1(13, 12, 11, 10, 9, 8);

void setup() {
  Serial.begin(9600); 
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(test, OUTPUT);

  lcd_1.begin(16, 2);

}

void loop() {

  int y;
  int a;
  int b;
  int c;
  digitalWrite(test, LOW);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW);

  int time = pulseIn(ECHO, HIGH);
  int cm = msToCm(time);
  int range = rangeLimiter(cm);
  //Serial.println("Decimal");
 // Serial.println(range);
 // Serial.println("Hexadecimal");
 // Serial.println(range, HEX);
  //Serial.println("Gray");
  y = grayCode(range);
  //Serial.println(y);
  delay(1000);
  
  a = y/100%10;
  b = y/10%10;
  c = y/1%10;
    
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);

  int inA = analogRead(A0);
  int inB = analogRead(A1);
  int inC = analogRead(A2);

  int boolA = intToBool(inA);
  int boolB = intToBool(inB);
  int boolC = intToBool(inC);

  int decimal = BCD_TO_DEC(0, 0, 0);

  Serial.println(decimal);
  lcd_1.print(decimal);


  delay(1000);
}

int grayCode(int num){
  int x = (num >> 1) ^ num;
  String binary = String(x, BIN);
  return binary.toInt();
}

int msToCm(int ms){
  return ms/29/2 ;
}

int rangeLimiter(int x){
    if(x >= 3 && x <=10){
    return x-3;
  }
}

int intToBool(int num){
  if(num == 0){
    return 0;
  }else{
    return 1;
  }

}

int BCD_TO_DEC(int a, int b, int c){
  if(!a&&b&&c){
    return 0;
   }
  if(a&&!b&&!c){
    return 1;
   }
  if(a&&!b&&c){
    return 2;
   }
  if(a&&b&&!c){
    return 3;
   }
  if(a&&b&&c){
    return 4;
   }
  if(!a&&!b&&!c){
    return 5;
   } 
  if(!a&&!b&&c){
    return 6;
   }
  if(!a&&b&&!c){
    return 7;
   }
  else{
    return "Error";
  }
}
