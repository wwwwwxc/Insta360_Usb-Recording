#include <Ticker.h>
#include <stdlib.h>
uint8_t S1 = D1;
Ticker Flipper;
bool timmer_active;


char signal[] = "012345";
int num_flip = 0;
char num_flip_c[3];
char zero[2] = "0";
char tmp_c[3];


void Flipf()//中断处理函数
{
  timmer_active = true;
  num_flip += 1;
  if(num_flip > 60)
  {
    num_flip = 1;
  }
}


void setup() {
  pinMode(S1, OUTPUT);
  //Serial.begin(115200); //初始化串口
  timmer_active = false;
  Flipper.attach(1,Flipf);
}

int Play_High(int t_d){
  digitalWrite(S1, HIGH);
  delay(t_d);//ms
  digitalWrite(S1, LOW);
  delay(t_d);//ms
  digitalWrite(S1, HIGH);
  delay(t_d);//ms
}

int Play_Low(int t_d){
  digitalWrite(S1, LOW);
  delay(t_d);//ms
  digitalWrite(S1, HIGH);
  delay(t_d);//ms
  digitalWrite(S1, LOW);
  delay(t_d);//ms
}

void Play_Note(int num){

  Play_High(2); //start
  delay(5);
  char s[8];
  int len;
  itoa(num,s,2);
  //Serial.printf("%s \n",s);
  
  if(num == 1)
  {
    char tmp[8];
    sprintf(tmp,"%s%s%s%s%s%s%s%s",zero,zero,zero,zero,zero,zero,zero,s);
    strncpy(s,tmp,8); 
  }
  else if(num <= 3)
  {
    char tmp[8];
    sprintf(tmp,"%s%s%s%s%s%s%s",zero,zero,zero,zero,zero,zero,s);
    strncpy(s,tmp,8);
  }
  else if(num <= 7)
  {
    char tmp[8];
    sprintf(tmp,"%s%s%s%s%s%s",zero,zero,zero,zero,zero,s);
    strncpy(s,tmp,8);
  }
  else if(num <= 15)
  {
    char tmp[8];
    sprintf(tmp,"%s%s%s%s%s",zero,zero,zero,zero,s);
    strncpy(s,tmp,8);
  }
  else if(num <= 31)
  {
    char tmp[8];
    sprintf(tmp,"%s%s%s%s",zero,zero,zero,s);
    strncpy(s,tmp,8);
  }
  else
  {
    char tmp[8];
    sprintf(tmp,"%s%s%s",zero,zero,s);
    strncpy(s,tmp,8);
  }
  for(int i=0;i<8;i++)
  { 
    if (s[i] == '1')
    {
      Play_High(5);
      //Serial.printf("1 ");
    }
    else{
      Play_Low(5);
      //Serial.printf("0 ");
    }
  }
}

void loop() { 
  digitalWrite(S1, LOW);
  if(timmer_active == true)
  {    
    //Serial.printf("%d  \n", num_flip);
    Play_Note(num_flip);
    timmer_active = false;
  }
}
