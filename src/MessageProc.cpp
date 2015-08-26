/*
  MessageProc.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, July 8, 2015
  Released into the public domain.
*/
#include "MessageProc.h"

MessageProc::MessageProc()
{

}

struct MessageProc::RequestHandler {
  RequestHandler(MessageProc::THandlerFunction fn, String topic): fn(fn), topic(topic), next(NULL)
  {
  }
  THandlerFunction fn;
  String topic;
  RequestHandler* next;
};

void MessageProc::waitSerial()
{
  unsigned long time=millis();
  while(!Serial.available() && millis()-time<1000){delay(1);}
}

void MessageProc::loop()
{
  if(Serial && Serial.available())
  {
    uint8_t d=Serial.read();
    //Serial.println("D:"+String(d));
    if(d==SEP)                                    //|
    {
      waitSerial();
      {
        d=Serial.read();
        if(d==MSEP)                               //M
        {
          uint8_t x=Serial.parseInt();            //size topic
          waitSerial();
          if(x>0 && Serial.read()==SEP)           //|
          {
            char topic[x+1];
            Serial.readBytes(topic, x);           //topic
            topic[x]=0;   //cerrar el string
            //Serial.println(topic);
            waitSerial();
            if(Serial.read()==SSEP)               //S
            {
              uint8_t y=Serial.parseInt();        //size mesage
              waitSerial();
              if(Serial.read()==SEP)              //|
              {
                char msg[y+1];
                Serial.readBytes(msg, y);         //message
                msg[y]=0;  //cerrar el string   
                //Serial.println("["+String(topic)+":"+String(msg)+"]");
                processMessage(topic,msg);
              }
            }
          }
        }
      }   
    }
  }      
}

void MessageProc::processMessage(String topic, String msg)
{
    //Serial.println("processMessage:"+topic);
    RequestHandler *aux=_ini;
    while(aux!=NULL)
    {
        //Serial.println("checking:"+aux->topic);
        if(aux->topic==topic)
        {
            //Serial.println("calling:"+aux->topic);
            aux->fn(msg);
            return;
        }else
        {
            aux=aux->next;
        }   
    }  
}


void MessageProc::on(String topic, MessageProc::THandlerFunction fn)
{
  RequestHandler* handler = new RequestHandler(fn, topic);
  if (!_end) {
    _ini = handler;
    _end = handler;
  }
  else {
    _end->next = handler;
    _end = handler;
  }
}    

void MessageProc::post(String topic, String data)
{
  if(Serial)
  {
    Serial.print(SEP);              //|
    Serial.print(MSEP);             //M  -> post
    Serial.print(topic.length());   //size topic
    Serial.print(SEP);              //|
    Serial.print(topic);            //topic
    Serial.print(SSEP);             //S  -> String
    Serial.print(data.length());    //size message
    Serial.print(SEP);              //|
    Serial.print(data);             //mesage
  }
}  

size_t MessageProc::write(const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  if(Serial)
  {
    Serial.print(SEP);              //|
    Serial.print(LSEP);             //L -> Log
    Serial.print(size);             //size log
    Serial.print(SEP);              //|
    while (size--) {        
      n += Serial.write(*buffer++); //mesage
    }    
  }
  return n;
} 