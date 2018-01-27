#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

const unsigned long int ITERATIONS = 100000000;

int main(){
   struct timeval time1;
   struct timeval time2;
   unsigned long long int time_start;
   unsigned long long int time_end;
   double runtime;

   gettimeofday(&time1, NULL);
   time_start = time1.tv_sec * 1000000 + time1.tv_usec;
   printf("Start: \t%lld\n", time_start);

   int i = 0;
   for (i = 0; i < ITERATIONS; i++){
      getpid();
   }

   gettimeofday(&time2, NULL);
   time_end = time2.tv_sec * 1000000 + time2.tv_usec;
   runtime = (double)(time_end - time_start);

   printf("End: \t%lld\n", time_end);
   printf("Runtime: %f\n", runtime);
   printf("Avg time of getpid(): %f microseconds.  %f nanoseconds.\n\n\n", runtime / ITERATIONS, (runtime / ITERATIONS * 1000));


   gettimeofday(&time1, NULL);
   time_start = time1.tv_sec * 1000000 + time1.tv_usec;
   printf("Start: \t%lld\n", time_start);

   i = 0;
   for (i = 0; i < ITERATIONS; i++){
      getppid();
   }

   gettimeofday(&time2, NULL);
   time_end = time2.tv_sec * 1000000 + time2.tv_usec;
   runtime = (double)(time_end - time_start);

   printf("End: \t%lld\n", time_end);
   printf("Runtime: %f\n", runtime);
   printf("Avg time of getppid(): %f microseconds.  %f nanoseconds.\n\n\n", runtime / ITERATIONS, (runtime / ITERATIONS * 1000));



   return 0;
}
