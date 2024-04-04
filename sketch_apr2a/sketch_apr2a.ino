const int A = 2;
const int B = 3;
const int C = 4;

#define TRIG 5
#define ECHO 6

void setup() {
  Serial.begin(9600); 
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {

  int y;
  int a;
  int b;
  int c;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG, LOW);

  int time = pulseIn(ECHO, HIGH);
  int cm = msToCm(time);
  int range = rangeLimiter(cm);
  Serial.println("Decimal");
  Serial.println(range);
  Serial.println("Hexadecimal");
  Serial.println(range, HEX);
  Serial.println("Gray");
  y = grayCode(range);
  Serial.println(y);
  delay(1000);
  
  a = y/100%10;
  b = y/10%10;
  c = y/1%10;
    
  digitalWrite(A, a);
  digitalWrite(B, b);
  digitalWrite(C, c);

  delay(100);
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
    if(x >= 3 & x <=10){
    return x-3;
  }
}