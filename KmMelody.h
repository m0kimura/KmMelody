//*******1*********2*********3*********4*********4*********5*********6*********7*********8
#include "Arduino.h"
/* ir.h */
#ifndef KMMELODY_H
#define KMMELODY_H

#define DATA_SIZE 500
#define DEBUG 1

class KmMelody{
  public:
    KmMelody(int pout);
    void begin(int tempo);
    void play(String req);
    void cont(bool cont);
    void tempo(String txt);
    byte Freq[DATA_SIZE];
    unsigned int Secs[DATA_SIZE];
    byte Duty[DATA_SIZE];
    int Max;
    int Base;
    int Index;
    int Last;
    long Save;
    int PinOut;

  private:
    void clear();
    unsigned int S[36];
};

#endif
