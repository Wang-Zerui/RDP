#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("unroll-loops")
#define int long
#define string String
#define MAXN 205
#define SEND_MAX 10010
#define dl 100
#define stdout A1
#define high 199
#define low 500
#include <avr/io.h>
#include <avr/interrupt.h>
const int prescale  = 8;
const int ocr2aval  = (16000000/(16000000/(3000*255)))/3000-1;
// const int ocr2aval = 254;
const float iinterval = prescale * (ocr2aval+1) / (F_CPU / 1.0e6);
const float period    = 2.0 * iinterval;
const float freq      = 1.0e6 / period;
void setup() {
  // Serial.begin(115200);
  pinMode(A0,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8,1);
  cli();
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS21)|(1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 82; //define upper limit of counter before it resets.
  sei();
  //am i suppose to uncomment the above?
  // Serial.print("Interrupt interval = ");
  // Serial.print(iinterval);
  // Serial.println(" microseconds");
  // Serial.print("Period             = ");
  // Serial.print(period); 
  // Serial.println(" microseconds");
  // Serial.print("Frequency          = ");
  // Serial.print(freq); 
  // Serial.println(" Hz");
}
short arr[MAXN][10];
int id=0;
inline string to_string(int x){
  string str="";
  while(x){
    str+=(x%10);
    x/=10;
  }
  return str;
}
inline int to_int(char x){
  return x-'0';
}
inline void to_bin(int x){
  id++;
  int bin=0;
  int r=8;
  int sum=0;
  while(x){
    bin=(bin<<3)+(bin<<1)+x%2;
    arr[id][r]=x%2;
    r--;
    sum+=(x%2);
    x>>=1;
  }
  arr[id][8]=sum%2;
}
inline int which(int x){
  if(x==1){
    return high;
  }
  return low;
}
inline void send_num(){
  for(int i=7;i>=0;i--){
    analogWrite(stdout,which(id&(1<<i)));//not using
  }
  // delay(dl);
}
unsigned short cnt=0;
bool flag; // if it is high flag is true, else low frequency flag=false;
inline void sendh(){
  cli();
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS21)|(1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 124; //define upper limit of counter before it resets.
  sei();
}
inline void send_chars(){
  send_num();
  send_num();
  send_num();
  register int aa;
  for(int i=1;i<=id;i++){
    for(int j=1;j<=8;j++){
      flag=arr[i][j];
      sendh();
    }
  }
}
void loop() {
  // register char ch;
  // while(Serial.available()){
  //   delay(3);
  //   if(Serial.available()>0){
  //     // ch=Serial.read();
  //     // to_bin(ch);
  //   }
  //   send_chars();
  //   send_sums();
  // }
  // tone(A1,3000,100);
  // flag=true;
  sendh();
}
volatile unsigned char value = 0;
ISR(TIMER2_COMPA_vect){
  // flag?PORTC^=2:(cnt&1?PORTC^=2:NULL);
  flag=PIND&0x01;
  // Serial.println(flag);
  if(flag){
    PORTC^=2;
  }else{
    if(cnt&1){
      PORTC^=2;
      // Serial.println(cnt);
    }
  }
  cnt^=1;
}
