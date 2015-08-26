/*
  Timer.h - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, July 8, 2015
  Released into the public domain.
*/

#ifndef TIMER_H
#define TIMER_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class Timer {
public:
    // constructor
    Timer();

    typedef void (*timer_callback)(void);

    struct TimerInstance{
      TimerInstance(unsigned long time, timer_callback fn, int n, timer_callback fn2): time(time), fn(fn), n(n), fn2(fn2)
      {
        ltime=millis();
      }
      int id;
      unsigned long ltime;
      unsigned long time;
      int n;
      timer_callback fn=NULL;
      timer_callback fn2=NULL;
      TimerInstance *next=NULL;;
    };    

    // this function must be called inside loop()
    void loop();

    // call function f every d milliseconds
    int setInterval(unsigned long d, timer_callback f);

    // call function f once after d milliseconds
    int setTimeout(unsigned long d, timer_callback f);

    // call function f every d milliseconds for n times
    int setTimer(unsigned long d, timer_callback f, int n);

    // call function f every d milliseconds for n times and the end call function f2
    int setTimer(unsigned long d, timer_callback f, int n, timer_callback f2);

    // destroy the specified timer
    void deleteTimer(int id);

protected:
    int _idc=0;  //contadore de IDs
    TimerInstance *_ini=NULL;
    TimerInstance *_end=NULL;

    /**
    * Regresa el siguiente elemento en la lista
    */
    TimerInstance *_deleteTimer(int id)
    {
        TimerInstance *prev=NULL;
        TimerInstance *aux=_ini;
        while(aux!=NULL)
        {
            if(aux->id==id){
                TimerInstance *next=aux->next;
                if(prev==NULL)
                {
                    _ini=next;
                }else
                {
                    prev->next=next;
                }
                if(next==NULL)
                {
                    _end=prev;
                }
                delete aux;
                return next;
            }
            prev=aux;
            aux=aux->next;
        }
        return NULL;
    }    
};

#endif
