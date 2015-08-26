#include<Cloudino.h>

Cloudino cdino;

#define SIR 10
#define ELE 11
#define PULSE 80       //micro seg
#define INTERV 1160    //milli seg


bolean eleon=false;
unsugned long ltime=0;

void sir(string msg)
{
  if(msg=="on")
  {
    digitalWrite(SIR, LOW);
  }else
  {
    digitalWrite(SIR, HIGH);
  }
}

void ele(string msg)
{
  if(msg=="on")
  {
    eleon=true;
  }else
  {
    eleon=false;
  }
}

void setup() {
  pinMode(SIR, OUTPUT); //sirena
  digitalWrite(SIR, HIGH);
  pinMode(ELE, OUTPUT); //eletrica
  digitalWrite(ELE, LOW);
  cdino.on("sir",sir);
  cdino.on("ele",ele);
  cdino.begin();
  ltime=millis();
}

void loop() {
  cdino.loop();

  if(eleon)
  {
    if((millis()-ltime)>INTERV)
    {
      ltime=millis();
      digitalWrite(ELE, HIGH);
      delayMicroseconds(PULSE);
      digitalWrite(ELE, LOW);
    }
  }
}
