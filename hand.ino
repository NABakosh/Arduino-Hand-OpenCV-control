#include <Servo.h>
Servo frst;
Servo frst2;
Servo frst3;
Servo frst4;
bool close = 0;
bool first = 0;
bool first2 = 0;
bool first3 = 0;
bool first4 = 0;
bool first5 = 0;
bool first6 = 0;
bool first7 = 0;
bool first8 = 0;
bool middle = 0;
bool middle2 = 0;
bool middle3 = 0;
bool middle4 = 0;
bool nn = 0;
bool nn2 = 0;
bool lst = 0;
byte parseStart = 0; 
String msg;
void setup() {
  Serial.begin(9600);
  frst.attach(3);
  frst2.attach(4);
  frst3.attach(5);
  frst4.attach(6);
}

void loop() {
if (Serial.available())               
  {
    char in = Serial.read();              
    if (!(in == '\n' || in == '\r'))     
    {
        switch (in)   
        {
            case ';': parseStart = 1; break; 
            case '@': parseStart = 2;  close = 1; break;
            case '!': parseStart = 2;  first = 1; break;
            case '#': parseStart = 2;  first2 = 1; break;
            case '%': parseStart = 2;  first3 = 1; break;
            case ':': parseStart = 2;  first4 = 1; break;
            case '?': parseStart = 2;  first5 = 1; break;
            case '*': parseStart = 2;  first6 = 1; break;
            case '(': parseStart = 2;  first7 = 1; break;
            case ')': parseStart = 2;  first8 = 1; break;
            case 'q': parseStart = 2;  middle = 1; break;
            case 'w': parseStart = 2;  middle2 = 1; break;
            case 'e': parseStart = 2;  middle3 = 1; break;
            case 'r': parseStart = 2;  middle4 = 1; break;
            case 't': parseStart = 2;  nn = 1; break;
            case 'y': parseStart = 2;  nn2 = 1; break;
            case 'u': parseStart = 2;  lst = 1; break;
        }

        if ((parseStart == 2) && (in != '!') && (in != '#') && (in != '%') && 
        (in != ':') && (in != '?') && (in != '*') && (in != '(') && 
        (in != ')') && (in != 'q') && (in != 'w') && (in != 'e') && 
        (in != 'r') && (in != 't') && (in != 'y') && (in != 'u') && (in != '@')) 
        {  
          msg += in;    
        }
     }
  }
  
  if(parseStart == 1)   
  {
      int message = msg.toInt();                          
      if (message < 200) message = 200;                   
      if (message > 800) message = 800;                   
      message = map(message, 200, 800, 0, 255);           
      { 
        if(close){
          frst.write(0);
          frst2.write(0);
          frst3.write(0);
          frst4.write(0);
        }
        if(first){
          frst.write(180);
          frst2.write(0);
          frst3.write(0);
          frst4.write(0);
        }
        if(first2){
          frst.write(180);
          frst2.write(180);
          frst3.write(0);
          frst4.write(0);
        }
        if(first3){
          frst.write(180);
          frst2.write(180);
          frst3.write(180);
          frst4.write(0);
        }
        if(first4){
          frst.write(180);
          frst2.write(180);
          frst3.write(180);
          frst4.write(180);
        }
        if(first5){
          frst.write(180);
          frst2.write(0);
          frst3.write(180);
          frst4.write(180);
        }
        if(first6){
          frst.write(180);
          frst2.write(180);
          frst3.write(0);
          frst4.write(180);
        }
        if(first7){
          frst.write(180);
          frst2.write(0);
          frst3.write(0);
          frst4.write(180);
        }
        if(first8){
          frst.write(180);
          frst2.write(0);
          frst3.write(180);
          frst4.write(0);
        }
        if(middle){
          frst.write(0);
          frst2.write(180);
          frst3.write(0);
          frst4.write(0);
        }
        if(middle2){
          frst.write(0);
          frst2.write(180);
          frst3.write(180);
          frst4.write(0);
        }
        if(middle3){
          frst.write(0);
          frst2.write(180);
          frst3.write(0);
          frst4.write(180);
        }
        if(middle4){
          frst.write(0);
          frst2.write(180);
          frst3.write(180);
          frst4.write(180);
        }
        if(nn){
          frst.write(0);
          frst2.write(0);
          frst3.write(180);
          frst4.write(0);
        }
        if(nn2){
          frst.write(0);
          frst2.write(0);
          frst3.write(180);
          frst4.write(180);
        }
        if(lst){
          frst.write(0);
          frst2.write(0);
          frst3.write(0);
          frst4.write(180);
        }
      close = 0;
      first = 0;
      first4 = 0;
      first3 = 0;
      first2 = 0;
      first5 = 0;
      first6 = 0;
      first7 = 0;
      first8 = 0;
      middle = 0;
      middle2 = 0;
      middle3 = 0;
      middle4 = 0;
      nn = 0;
      nn2 = 0;
      lst = 0;
      parseStart = 0;
      msg = ""; 
        }
        }
      }
    