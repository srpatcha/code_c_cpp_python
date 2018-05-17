#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>

uint16_t volatile *pWatchdog = (uint16_t volatile*) 0xFF0000;

void watchdog(int sig) 
{
  printf("Pet the dog\r\n");
  alarm(5);
}

int main(void) 
{ 
        hwinit(); 
        for (;;) 
        { 
           *pWatchdog = 100; 
           read_sensors(); 
           control_motor(); 
           display_status(); 
        } 
  /* start the timer - we want to wake up in 5 seconds */
  signal(SIGALRM, watchdog);
  alarm(5);
  while ( true )
   ; 
  /* set up our signal handler to catch SIGALRM */
 return 0;
}
