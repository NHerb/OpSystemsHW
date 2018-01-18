#include <stdio.h>
#include <sys/time.h>

int main(){
   struct timeval mytime;
   gettimeofday(&mytime, NULL);
   printf("%ld\n", mytime.tv_sec);


   return 0;
}
