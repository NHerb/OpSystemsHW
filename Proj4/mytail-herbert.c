#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX 50

int main(int argc, char** argv){
   if (argc != 3){
      printf("Usage: mytail -n file\n");
   }
   int n = atoi(argv[1]);
   n = abs(n); // Not sure whether the integer is input as n or -n, but needs to be positive anyway.

   char filename[MAX+1];
   strcpy(filename, argv[2]);
   struct stat filedata;
   int filesize = 0;

   if (stat(filename, &filedata) != 0){
      int err = errno;
      printf("Failed to stat file.  Error %d.\n", err);
      return 1;
   } 
   filesize = filedata.st_size;
   
   int fd = open(filename, O_RDONLY);
   if (fd == -1){
      int err = errno;
      printf("Failed to open file.  Error %d.\n", err);
   }

   int offset = lseek(fd, filesize-1, SEEK_SET);
   if (offset == -1){
      int err = errno;
      printf("Failed to set offset.  Error %d.\n", err);
   }


   // Start at file end and read each character 'til we find n+1 endline characters
   char current[1];
   int count = 0;
   int i = 0;
   for (i = 0; i < filesize - 1; i++){
      if (read(fd, current, 1) == 0)
         printf("EOF\n");
      if (*current == '\n'){
         count++;
      }
      if (count == n + 1)
         break;
       
      offset = lseek(fd, -2, SEEK_CUR);
      if (offset == -1){
         int err = errno;
         printf("Failed to set offset.  Error %d.\n", err);
      }
   }


   // Found the spot, now print out everthing hereafter, excepting the characters on this n+1'th line
   int found_first = 0;
   while (read(fd, current, 1) != 0){
      if (!found_first){
         if (*current == '\n')
            found_first = 1;
      }
      printf("%c", *current);
   
   }



   if (close(fd) == -1){
      int err = errno;
      printf("Failed to properly close file.  Error %d", err);
   }
   return 0;
}
