/*
        
        Timer.cpp and Timer.h
        By Andrew Shirley
        AndrewShirley26@gmail.com
        AndrewShirley.tech

        Free for personal use.  For commercial use, please contact me.

           
        void HandleTimer(TimerInstance *T)
        {
            Serial.printf("HandlerTimer is called with %s\n",T->TimerName);
        }

        Timer *T;
        
        void TestTimer() {
            T = new Timer();
            T->AddTimer("Timer1",1000,true,HandleTimer);
        }







*/


#include "Timer.h"

int TimerInstance::n = 0;

// Constructor for the Timer Class
TimerInstance::TimerInstance()
{
    snprintf(this->TimerName, MaxTimerNameSize, "Timer_%d", n++);
}



// Determinse if if this timer has expired
bool TimerInstance::IsExpired()
{
    return (this->FutureTimeExpirey && millis() >= FutureTimeExpirey);
}

// Perform duties for when the timer has expired.  Calls handlers and retriggers if required
void TimerInstance::ProcessExpired()
{
    if(this->ExpiryHandler != nullptr)
    {
        ExpiryHandler(this);
    }
    if(this->Retrigger)
        this->FutureTimeExpirey += this->Interval;              // Ridgid timing. Loose timing: this->FutureTimeExpirey +=  ( millis() + this->Interval );
    else
        this->FutureTimeExpirey = 0;
}

// Makes a new TimerInstance, adds it to the Items array and returns a pointer to the newly created TimerInstance
TimerInstance *Timer::AddTimer(char *TimerName, int Interval, bool Repeat, void (*ExpiryHandler)(TimerInstance *Handler))
{
    TimerInstance *T = new TimerInstance();
    strncpy((char *)T->TimerName, TimerName, MaxTimerNameSize);
    T->FutureTimeExpirey = millis() + Interval;
    T->Retrigger = Repeat;
    T->Interval = Interval;
    T->ExpiryHandler = ExpiryHandler;

    AddTimer(T);
    return T;
}



// Add a new timer to the Items array
void Timer::AddTimer(TimerInstance *T)
{
    Items[T->TimerName] = T;
}


// Check for expired TimerInstance objects
void Timer::ScanForExpired()
{
    for (auto const &I : this->Items)
        if (I.second->IsExpired())
            I.second->ProcessExpired();

    return;

}

// Call this from your main's loop.
void Timer::loop()
{
    ScanForExpired();
}


Timer::Timer()
{

}



