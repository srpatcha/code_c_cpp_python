/*
  GNU hello world practicing for basic class 
  Practice the basic coding    
*/

#include<iostream>

using namespace std;

class ramgopal{
   private:
    int bit;
   public:
    int a=11;
    ramgopal();
    ~ramgopal(){
     }
   
};

ramgopal::ramgopal()
 {
  ++a;
  cout<<"Hello World"<<endl;
 }

int main( )
{
    ramgopal siva; // creating object
    cout <<siva.a<<endl;
    ramgopal ravi;
    cout<<ravi.a<<endl;
    ramgopal raman;
    cout<<raman.a<<endl;

   return 0;
}
