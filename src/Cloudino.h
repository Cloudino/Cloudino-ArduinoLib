/*
  Cloudino.h - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, July 8, 2015
  Released into the public domain.
*/
#ifndef Cloudino_h
#define Cloudino_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "Print.h"
#include "Timer.h"
#include "MessageProc.h"

class Cloudino : public Print
{
  public:

    Cloudino();
    
    void begin();
    size_t write(const uint8_t *buffer, size_t size);
    
    void on(String topic, MessageProc::THandlerFunction fn);
    void post(String topic, String data);
    void loop();
    
    // call function f every d milliseconds
    int setInterval(unsigned long d, Timer::timer_callback f);

    // call function f once after d milliseconds
    int setTimeout(unsigned long d, Timer::timer_callback f);

    // call function f every d milliseconds for n times
    int setTimer(unsigned long d, Timer::timer_callback f, int n);

    // call function f every d milliseconds for n times
    int setTimer(unsigned long d, Timer::timer_callback f, int n, Timer::timer_callback f2);

    // destroy the specified timer
    void deleteTimer(int numTimer);

  protected:
    size_t write(uint8_t);  
  private:
    Timer timer;
    MessageProc proc;
    //void initMessage();
    //void initTimer();
};

#endif
