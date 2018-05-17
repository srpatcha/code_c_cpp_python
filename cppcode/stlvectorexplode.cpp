#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector <string> explode(const string &delimiter, const string &explodeme);


int main(int argv, char *argc[] )
{
   string str ="I have bunch of cocoa nuts";
   cout <<str<<endl;
   vector < string > v =explode(" ", str);
   for(int i=0;i<v.size();i++ ) 
     cout << i << "[" <<v[i] << "]" <<endl;

}

vector < string > explode( const string &delimiter ,const string &str)
{
   vector <string> arr;

   int strleng = str.length();
   int delleng = delimiter.length();
   if(delleng==0)
    return arr;

  int i=0,k=0;
  while(i<strleng)
  {   
      int j=0;
      while(i+j<strleng && j<delleng && str[i+j]==delimiter[j])
       j++;
      if(j==delleng)
      {
         arr.push_back( str.substr(k,i-k));
         i+=delleng;
         k=i;
      }
      else 
       i++;
  }
  arr.push_back(str.substr(k,i-k)) ;
  return arr;
}

