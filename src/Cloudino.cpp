/*
  Cloudino.cpp - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, July 8, 2015
  Released into the public domain.
*/
#include "Cloudino.h"

#define SERIAL_SPEED 57600

Cloudino::Cloudino()
{
}

void Cloudino::begin()
{
    Serial.begin(SERIAL_SPEED);
    //Serial.flush();     
}

size_t Cloudino::write(uint8_t b)
{
}

size_t Cloudino::write(const uint8_t *buffer, size_t size)
{
  return proc.write(buffer,size);
} 

void Cloudino::on(String topic, MessageProc::THandlerFunction fn)
{
  proc.on(topic,fn);
}

void Cloudino::post(String topic, String data)
{
  proc.post(topic,data);
}

// call function f every d milliseconds
int Cloudino::setInterval(unsigned long d, Timer::timer_callback f)
{
  return timer.setInterval(d,f);
}

// call function f once after d milliseconds
int Cloudino::setTimeout(unsigned long d, Timer::timer_callback f)
{
  return timer.setTimeout(d,f);
}

// call function f every d milliseconds for n times
int Cloudino::setTimer(unsigned long d, Timer::timer_callback f, int n)
{
  return timer.setTimer(d,f,n);
}

// call function f every d milliseconds for n times
int Cloudino::setTimer(unsigned long d, Timer::timer_callback f, int n, Timer::timer_callback f2)
{
  return timer.setTimer(d,f,n,f2);
}

// destroy the specified timer
void Cloudino::deleteTimer(int numTimer)
{
  timer.deleteTimer(numTimer);
}

void Cloudino::loop()
{
  timer.loop();
  proc.loop();
}
