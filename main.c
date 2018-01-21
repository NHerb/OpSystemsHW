#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

const long int iterations = 1000000000;

int main(){
   struct timeval time1;
   struct timeval time2;

   gettimeofday(&time1, NULL);
   unsigned long long int time_start = time1.tv_sec * 1000000 + time1.tv_usec;
   printf("Start: \t%lld\n", time_start);

   for (int i = 0; i < iterations; i++){
      getpid();
   }

   gettimeofday(&time2, NULL);
   unsigned long long int time_end = time2.tv_sec * 1000000 + time2.tv_usec;
   double runtime = (double)(time_end - time_start);

   printf("End: \t%lld\n", time_end);
   printf("Runtime: %f\n", runtime);
   printf("Avg time: %f microseconds.  %f nanoseconds.\n", runtime / iterations, (runtime / iterations * 1000));

   return 0;
}
