#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "pperm.h"

int main(int argc, char** argv){
   
   struct stat data_block;
   
   if (argc != 2){
      printf("Invalid Input.\n");
      return 1;
   }
   
   if (stat(argv[1], &data_block) != 0){
      printf ("Failure\n");
      return 1;
   }
   
   printf("  File: '%s'\n", argv[1]);
   printf("  Size: %ld\t\t", data_block.st_size);
   printf("Blocks: %ld\n", data_block.st_blocks);
   printf("\t\t\tInode Number: %ld\t", data_block.st_ino);
   printf("Links: %ld\n", data_block.st_nlink);
   print_permissions(data_block.st_mode);
   
   
   return 0;
}
