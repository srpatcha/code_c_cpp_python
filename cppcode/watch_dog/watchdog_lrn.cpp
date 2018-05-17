#include <iostream>
#include "watchdog_lrn.h"

using namespace std;

Watchdog::Watchdog() :
  _interval(0),
  _timer(0),
  _running(false)
{
}

Watchdog::Watchdog(unsigned int milliseconds, std::function<void()>callback )
{
   Watchdog::Start(milliseconds, callback);
}

void Watchdog::Start(unsigned int milliseconds,std::function<void()> callback)
{
  _interval = milliseconds;
  _timer = 0 ;
  _callback = callback;
  _running = true;
  _thread = std::thread(&Watchdog::Loop, this);
}

 Watchdog::~Watchdog()
{

}

void Watchdog::Start(unsigned int milliseconds, std::function<void()>callback )
{
   _interval= milliseconds;
   _timer = 0 ;   
   _callback = callback;
   _running = true;
  _thread = std::thread(&Watchdog::Loop, this);
}

void Watchdog::Stop()
{
 _runing = false;
 _thread.join();
}
void Watchdog::Pet()
{
  _timer = 0 ;
}

void Watchdog::Loop()
{
  while(_running)
  {
     _timer++;
     
     if( _timer >= _interval )
     {
         _running = false;
         _callback();
     }
     std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }  
 
}
