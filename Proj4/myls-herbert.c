#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include "printpermissions.h"
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LENGTH 100

int main(int argc, char** argv){
   int long_mode = 0;
   int use_cwd = 1;
   int i = 0;
   char dir_name[MAX_NAME_LENGTH+1];
   DIR* directory;
   struct dirent* dir_data;
   struct stat file_data;


   if (argc > 3){
      printf("Usage: myls [options] [file].\n");
      return 1;
   }

   // options and filename can be in any order, just scan for matches
   for (i = 1; i < argc; i++){
      if (strcmp(argv[i],"-l") == 0)
         long_mode = 1;
      else {
         strcpy(dir_name, argv[i]);
         use_cwd = 0;
      }
   }

   if (use_cwd)
      getcwd(dir_name, MAX_NAME_LENGTH);

   directory = opendir(dir_name);
   if (directory == NULL){
      printf("Failed to open directory.\n");
      return 1;
   }

   // Read through every entry in the directory & list off appropriate data given user-desired mode
   while (1){
      dir_data = readdir(directory);
      if (dir_data == NULL)
         break;
      if (long_mode){
         int result = 0;
         if (!use_cwd){
            char temp_name[MAX_NAME_LENGTH+1];
            sprintf(temp_name, "%s/%s", dir_name, dir_data->d_name);
            result = stat(temp_name, &file_data);
         } else
            result = stat(dir_data->d_name, &file_data);
         if (result == 0){
            struct group* grp;
            struct passwd* usr;
            grp = getgrgid(file_data.st_gid);
            usr = getpwuid(file_data.st_uid);
            print_permissions(file_data.st_mode);
            printf(" %ld  ", file_data.st_nlink);
            if (usr != NULL)
               printf("%s  ", usr->pw_name);
            else 
               printf("UID: %d  ", file_data.st_uid);
            if (grp != NULL)
               printf("%s  ", grp->gr_name);
            else 
               printf("GID: %d  ", file_data.st_gid);
            printf("%ld  ", file_data.st_size);
         } else 
            printf("Failed to stat file: Error code %d.  ", errno);
      }
      printf("%s  ", dir_data->d_name);
      if (argc == 2);printf("\n");
   }

   printf("\n");
   return 0;
}
