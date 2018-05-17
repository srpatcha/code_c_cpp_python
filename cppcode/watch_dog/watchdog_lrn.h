#pragma once

#include <thread>
#include <atomic>

class Watchdog
{
 public:
     Watchdog();
     Watchdog(unsigned int milliseconds, std::function<void()>callback );
     ~Watchdog();
    
     void Start(unsigned int millisecondsa, std::function<void()>callback);
     void stop();
     void pet();

 private:
     unsigned int _interval;
     std::atomic<unsigned int> _timer;
     std::atomic<bool> _running;
     std::thread _thread;
     std::function<void()> _callback;
     
     void Loop();
};
