#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

// vim editor  :%s/<search_string>/<replace_string>/g 

using namespace std;

char *read_mem= new char [20];

int main () {
  char M_BFR[20];
  system("/usr/sbin/flashrom -p internal -r /tmp/bios_backup.bin &> /dev/null");
  //usleep(10000);
  std::ifstream is ("/tmp/bios_backup.bin", std::ifstream::binary);
  //system("hexdump -v /home/srpatcha/read_device_name/bios_backup.bin  -c -n 15 -s 3975 ");
  //system("hexdump -v /tmp/bios_backup.bin -c -n 15 -s 3975 ");
  //std::ifstream is ("/home/srpatcha/read_device_name/bios_backup.bin", std::ifstream::binary);
  if (is) {
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);
    char * buffer = new char [length];
    is.read (buffer,length);
    is.close();
    //buffer contains the entire binary BIOS data
    for(int x=0,i=3975;i<=3990; x++,i++)  // memory offset location-3975 
    { 
       M_BFR[x] = *(buffer+i);
    } 
    read_mem=M_BFR;
    delete[] buffer;
    system("rm -f /tmp/bios_backup.bin &> /dev/null"); 
    cout << "Model Name : " << read_mem <<endl; 
    return true;
  }
  else 
  {
    read_mem=(char*) "MS-NAE.....";
    cout << "Model Name : " << read_mem <<endl; 
    return false; 
  }
  return 0;
}
