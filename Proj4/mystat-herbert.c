#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

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
   
   printf("Filesize: %ld\n", data_block.st_size);
   printf("Block count: %ld\n", data_block.st_blocks);
   printf("Hard Links: %ld\n", data_block.st_nlink);


   printf("File Permissions: ");
   if (data_block.st_mode & S_IFDIR)
      printf("d");
   else
      printf("-");

   if (data_block.st_mode & S_IRWXU)
      printf("rwx");
   else {
      if (data_block.st_mode & S_IRUSR)
         printf("r");
      else 
         printf("-");
      if (data_block.st_mode & S_IWUSR) 
         printf("w");
      else
         printf("-");
      if (data_block.st_mode & S_IXUSR) 
         printf("x");
      else
         printf("-");
   }

   if (data_block.st_mode & S_IRWXG)
      printf("rwx");
   else {
      if (data_block.st_mode & S_IRGRP)
         printf("r");
      else 
         printf("-");
      if (data_block.st_mode & S_IWGRP) 
         printf("w");
      else
         printf("-");
      if (data_block.st_mode & S_IXGRP) 
         printf("x");
      else
         printf("-");
   }

   if (data_block.st_mode & S_IRWXO)
      printf("rwx\n");
   else {
      if (data_block.st_mode & S_IROTH)
         printf("r");
      else 
         printf("-");
      if (data_block.st_mode & S_IWOTH) 
         printf("w");
      else
         printf("-");
      if (data_block.st_mode & S_IXOTH) 
         printf("x\n");
      else
         printf("-\n");
   }


   printf("Inode Number: %ld\n", data_block.st_ino);
   
   
   return 0;
}
