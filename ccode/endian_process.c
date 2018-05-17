#include <stdio.h>
#include <string.h>
int main(int argc, char **agrv) 
{
   unsigned int i = 1;
   char *c = (char*)&i;
   if (*c)    
       printf("Little endian\n");
   else
       printf("Big endian\n");

// different test 
   unsigned int x=0x76543210;
   char *a = (char*) &x; 

   printf("*a is : 0x%x", *a);
   if(*a==0x10)
      printf("Underlaying arch is little endian. \n");
   else
     printf("Underlying architecture is big endain\n ");

// one more stage
   int z=5;
   char b[] ="ABCDEFG";

   FILE* fp;
 
    /* Our example data structure */
   struct {
        char one[4];
        int  two;
        char three[4];
   } data;
 
   /* Fill our structure with data */
   strcpy (data.one, "foo");
   data.two = 0x01234567;
   strcpy (data.three, "bar");
 
   /* Write it to a file */
   fp = fopen ("output", "wb");
   if (fp) {
        fwrite (&data, sizeof (data), 1, fp);
        fclose (fp);
   }

  return 0;
}


