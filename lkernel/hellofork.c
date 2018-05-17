#include <stdio.h>
#include <unistd.h>

void main()
{
   int i;
   pid_t getpid();
   printf("current process PID:%d\n",getpid());
   i = fork();
   if (i==0)
   {
    printf("am in child process\n");
    printf("child process ID:%d\n",getpid());    
   }

   printf("Did a fork. it return=%d getpid=%d, getppd=%d\n",i,getpid(),getppid());

}
