/*
  MessageProc.h - Library for Cloudino Platform.
  Created by Javier Solis, javier.solis@infotec.mx, July 8, 2015
  Released into the public domain.
*/
#ifndef MessageProc_h
#define MessageProc_h

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

const char SEP='|';
const char MSEP='M';
const char SSEP='S';
const char LSEP='L';

class MessageProc
{
  public:
    struct RequestHandler;

    MessageProc();

    typedef void (*THandlerFunction)(String);    

    void loop();

    void on(String topic, THandlerFunction fn);

    void post(String topic, String data);

    size_t write(const uint8_t *buffer, size_t size);

    void processMessage(String topic, String msg);
  protected:

  private:
    RequestHandler *_ini=NULL;
    RequestHandler *_end=NULL;
    void waitSerial();
};

#endif
