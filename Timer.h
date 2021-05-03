/*
    Timer.h
    A generic class to provide callbacks at a specific interval or recurring intervals

    void HandleTimer(TimerInstance *T)
    {
        Serial.printf("HandlerTimer is called with %s\n",T->TimerName);
    }    
    
    Timer *T = new Timer();
    //          TimerName,  mS,   Recurring,  Callback Function
    T->AddTimer("Testers",  1000, true,       HandleTimerFunc)      // After 1 second, calls HandleTimerFunc
    T->AddTimer("Testers2", 2000, false,      HandleTimerFunc)      // After 2 seconds, calls HandleTimerFunc
    T->AddTimer("Testers3", 5000, false,      nullptr)              // After 5 seconds, does nothing.

*/



#ifndef _Timer_H
#define _Timer_H

#define MaxTimerNameSize 15

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <map>
using namespace std;



class TimerInstance
{
    private:
        static int n;

    public:
        char TimerName[MaxTimerNameSize];
        long FutureTimeExpirey = 0;                 // When should this timer Expire?
        bool Retrigger = false;                     // Retrigger after expiring? Ie: Interval Timer
        int Interval = 1000;                        // Milliseconds between triggers (if Retrigger=true)

    bool IsExpired();                               // Is this timer expired?
    void ProcessExpired();                          // Calls Event handlers, resets trigger if required
    TimerInstance();
    void (*ExpiryHandler)(TimerInstance *T) = nullptr;


};

class Timer
{
    protected:
        std::map<string, TimerInstance *> Items = {};
        void ScanForExpired();

    public:
        Timer();
        TimerInstance *AddTimer(char *TimerName, int Interval, bool Repeat, void (*ExpiryHandler)(TimerInstance *Handler));
        void AddTimer(TimerInstance *T);
        void loop();
};


#endif