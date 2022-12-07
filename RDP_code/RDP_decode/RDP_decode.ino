/*
This code receives the signal.
The signal received is in the following format:
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
#define dl 50
#define stdout A1
#define high 700
#define low 100
void setup() {
  Serial.begin(115200);
  pinMode(A0,INPUT);
}
int arr[MAXN][10];
int rowsum[MAXN];
int colsum[10];
int ourrowsum[MAXN];
int ourcolsum[10];
int buff[MAXN<<5];
int num;
inline void read_8bits(int x){
  for(int i=1;i<=8;i++){
    arr[x][i]=analogRead(A0);
  }
}
inline int read_16bits(){
  int ans=0;
  
}
inline void get_num(){
  int a=0;
  int b=0;
  int c=0;
  int temp;
  
  for(int i=1;i<=8;i++){
    temp=analogRead(A0);
    a=(a<<1)+temp;
  }
}
inline void read(){
  for(int i=1;i<MAXN;i++){
    for(int j=1;j<=8;j++){
        arr[i][j]=analogRead(A0);
    }
  }
}
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
inline void summed(){

}
inline bool check(int id){
  int sum=0;
  for(int j=1;j<=7;j++){
    sum+=arr[id][j];
  }
  return (sum%2)==arr[id][8];
}
inline char decode(int id){
  if(check(id)){
    int ans=0;
    for(int j=1;j<=8;j++){
      ans<<=1;
      ans+=arr[id][j];
    }
    return char(ans);
  }

}
void loop() {
  // for(int i=1;i<(MAXN<<5);i++){
  //   buff[i]=1;
  // }
  Serial.println((int)analogRead(A0));
}
