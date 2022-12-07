/*
This code sends the signal.
The signal sent is in the following format:
The number of characters, 8 bits each, send 3 times
Then, all the characters, each of them being 8 bits
Lastly, all the row sums(16 bits each), all the column sums(8 column sums), 16 bits each, and that whole thing is send 3 times.
**/
#pragma comment(linker,"/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("unroll-loops")
#define int long
#define string String
#define MAXN 205
#define dl 100
#define stdout A1
#define high 2800
#define low 500
void setup() {
  Serial.begin(115200);
  pinMode(A0,INPUT);
  pinMode(A1,OUTPUT);
  pinMode(8,OUTPUT);
  digitalWrite(8, 1);
}
short arr[MAXN][10];
int rowsum[MAXN];
int colsum[10];
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
    analogWrite(stdout,which(id&(1<<i)));
  }
  // delay(dl);
}
inline void send_chars(){
  send_num();
  send_num();
  send_num();
  for(int i=1;i<=id;i++){
    for(int j=1;j<=8;j++){
      // analogWrite(stdout,which(arr[i][j]));
      tone(stdout,which(arr[i][j]),300);
      // delay(dl);
    }
  }
}
inline void send_int(int x){
  for(int i=15;i>=0;i--){
    analogWrite(stdout,which(x&(1<<i)));
  }
  delay(dl);
}
inline void send_sums(){
  for(int i=1;i<=id;i++){
    send_int(arr[9][i]);
  } 
  for(int j=1;j<=8;j++){
    send_int(arr[j][id+1]);
  }
}
inline void send_end(){
  send_sums();
  send_sums();
  send_sums();
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
  // to_bin(2);
  // send_chars();
  // id=0;
  // tone(A1,300,1000);
  // delay(dl);
  // tone(A1,1000,1000);
  // delay(dl);
  for(int i=500;i<=2500;i++){
    tone(A1,i,300);
    delay(dl);
  }
}
