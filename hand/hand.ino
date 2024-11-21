#include <Servo.h>
Servo frst;
Servo frst2;
Servo frst3;
Servo frst4;
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
        
        }
        }
      }
    