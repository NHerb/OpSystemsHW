#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/time.h>

const unsigned long int ITERATIONS = 10000;

int main(){

   int pipe_1[2];    // [0] is read side, [1] is write side
   int pipe_2[2];
   pid_t process_id;
   void * buffer = NULL;
   struct timeval time1;
   struct timeval time2;
   unsigned long long int time_start = -1;
   unsigned long long int time_end = -1;
   double runtime = -1;
   double average_runtime = -1;

   cpu_set_t mask;      // I dont understand what is happening here very well
   CPU_ZERO(&mask);
   CPU_SET(0, &mask);
   sched_setaffinity(0, sizeof(cpu_set_t), &mask);


   if (pipe(pipe_1) == -1 || pipe(pipe_2) == -1){
      printf("Pipe failed.\n");
      return 1;
   }

   process_id = fork();
   if (process_id < 0){
      printf("Fork failed.\n");
      return 1;
   }



   // Have just the child do the time measurement
   if (process_id == 0){
      gettimeofday(&time1,NULL);
      time_start = time1.tv_sec * 1000000 + time1.tv_usec;
   
      printf("Start: %lld\n", time_start);
   }

   int i = 0;
   for (i = 0; i < ITERATIONS; i++){
      if (process_id == 0){
         write(pipe_1[1], " ", 1);
         read(pipe_2[0], buffer, 1);
      } else {
         read(pipe_1[0], buffer, 1);
         write(pipe_2[1], " ", 1);
         read(pipe_1[0], buffer, 1);
      }

   }


   if (process_id == 0){
      gettimeofday(&time2,NULL);
      time_end = time2.tv_sec * 1000000 + time2.tv_usec;
      runtime = (double)(time_end - time_start);
      average_runtime = runtime / ITERATIONS;

      printf("End: %lld\n", time_end);
      printf("Runtime: %f microseconds, %f seconds\n", runtime, runtime / 1000000);
      printf("Avg Time: %f microseconds, %f nanoseconds.\n", average_runtime, average_runtime * 1000);
   }
   return 0;
}
