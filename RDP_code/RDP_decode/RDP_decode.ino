// #pragma comment(linker,"/stack:200000000")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("inline")
// #pragma GCC optimize("unroll-loops")
#define string String
#define MAXN 205
#define dl 50
#define stdout A2
#define stdin A0
#define high 700
#define low 100
short r=0;
int buff[10];
long vals[4];
uint8_t history=0;
//in order is sin 1000,sin 2000,cos 1000,cos 2000
void setup() {
  // Serial.begin(115200);
  pinMode(A0,INPUT);
  pinMode(A2,OUTPUT);
  pinMode(A3,OUTPUT);
  // Serial.println("hi3");
  // cli();
  TCCR2A = (1 << WGM21);
  TCCR2B = (1 << CS21)|(1 << CS20);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 61; //define upper limit of counter before it resets.
  ADMUX=0x40;
  ADCSRA=B11000111;
  // ADCSRA |= B00000100; // set ADIE bit in ADCSRA register
  // ADCSRA |= B01000000; // set ADSC bit in ADCSRA register
  // Serial.println("HI");
  // sei();
}
// int arr[MAXN][10];
// int buff[MAXN<<5];
// int num;
void loop() {
  // Serial.println("ahh");
  // cli();
  // Serial.println("hi2");
  // TCCR2A = (1 << WGM21);
  // TCCR2B = (1 << CS21)|(1 << CS20);
  // TIMSK2 = (1 << OCIE2A);
  // OCR2A = 20; //define upper limit of counter before it resets.
  // sei();
  // digitalWrite(8,1);
  // PORTB^=0x01;
}
ISR(TIMER2_COMPA_vect){
  PORTC^=0x08;
  // Serial.println("hi");// for testing
  // PORTC^=0x04;
  r++;
  // Serial.println("h2");
  r&=(7);
  // Serial.println("h3");
  buff[r]=ADC;
  ADCSRA|=0x40;
  // if(buff[r]>512){//this line works have signal in blue
  //   PORTC|=0x04;
  // }else{
  //   PORTC&=~0x04;
  // }
  // ADCSRA|=0x40;
  // Serial.println("h4");
  // for(int i=0;i<=7;i++){
  //   // Serial.println("h5");
  //   Serial.println(buff[i]);
  // }
  // vals[0]=buff[(2)&7]+(buff[(3)&7]<<1)+buff[(4)&7]-buff[(6)&7]-(buff[(7)]<<1)-buff[0];
  // vals[1]=(buff[(2)&7]<<1)-(buff[(4)&7]<<1)+(buff[(6)]<<1)-(buff[0]<<1);
  // vals[2]=(buff[(1)&7]<<1)+(buff[(2)&7])-buff[(4)]-(buff[(5)]<<1)-(buff[(6)])+buff[0];
  // vals[3]=-(buff[(2)&7]<<1)+(buff[(4)&7]<<1)-(buff[(6)]<<1)+(buff[0]<<1);
  //in order is sin 1000,sin 2000,cos 1000,cos 2000
  vals[0]=buff[0]+buff[1]-buff[4]-buff[5];
  vals[2]=buff[2]+buff[3]-buff[6]-buff[7];
  vals[1]=buff[0]-buff[2]+buff[4]-buff[6];
  vals[3]=buff[1]-buff[3]+buff[5]-buff[7];
  long freq_1000=vals[0]*vals[0]+vals[2]*vals[2];//is this correct?
  long freq_2000=vals[1]*vals[1]+vals[3]*vals[3];
  short cnt=0;
  bool this_bit;
  if(freq_1000<=freq_2000){
    cnt>=5?this_bit=1:this_bit=0;// if number of 1s(including the current bit) is more than 5 then this bit is 1
    //else this bit is 0
    //since this bit is originally a 0 bit, cnt doesn't change
    // this_bit?PORTC|=0x04:PORTC&=~0x04;
    if(!this_bit){
      PORTC|=0x04;
    }else{
      PORTC&=~0x04;
    }
    cnt+=(this_bit);//then update the count of number of 1s(if this bit is 1 then cnt++)
    cnt-=(((history&(1<<7)))>>7);//remove the highest bit(since it is out of the window of past 8 values)
    //the left and right shifts extract the highest bit and decrement cnt accordingly
    history=(history<<1);//ok now it is unfiltered bit(since this bit is 0)
    // PORTC|=0x04;
    // not every sure why this doesn't work
    // it should enter either if or else
    //then it is 1000 Hz
    // Serial.println("1000 Hz"); //for testing
    // prev[1]=prev[2];
    // prev[2]=prev[3];
    // prev[3]=0;
    // if(!prev[1]||!prev[2]){
    //   // PORTC^=0x04;
    //   PORTC&=0x04;
    //   // sends low signal
    // }else{
    //   PORTC&=~0x04;
    //   prev[3]=1;
    // }
  }else{
    cnt++;
    cnt>=5?this_bit=1:this_bit=0;
    // this_bit?PORTC&=~0x04:PORTC|=0x04;
    if(!this_bit){
      PORTC&=~0x04;
    }else{
      PORTC|=0x04;
    }
    cnt-=(!this_bit);
    cnt-=(((history&(1<<7)))>>7);
    history=(history<<1)|1;//this is unfiltered bit(current bit is 1)
    // PORTC&=~0x04;
    // prev[1]=prev[2];
    // prev[2]=prev[3];
    // prev[3]=1;
    // if(prev[1]||prev[2]){
    //   PORTC&=~0x04;
    // }else{
    //   PORTC&0x04;
    //   prev[3]=0;
    // }
    //it is 2000Hz
    // Serial.println("2000 Hz");//for testing
  }
}