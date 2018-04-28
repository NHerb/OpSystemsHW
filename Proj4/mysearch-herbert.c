#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>


#define MAX_NAME_LENGTH 200

void print_directory(int is_root, char* current);

int main(int argc, char** argv){
   char current[MAX_NAME_LENGTH+1];
   char cwd[MAX_NAME_LENGTH+1];

   if (argc > 2){
      printf("Usage: mysearch directory\n");
      return 1;
   }

   getcwd(cwd, MAX_NAME_LENGTH);
   if (argc == 2){
      sprintf(current, "%s/%s", cwd, argv[1]);
      print_directory(0, current);
   } else
      print_directory(1, cwd);

   printf("\n");
   return 0;
}

void print_directory(int is_root, char* current){
   struct dirent* dir_data;
   struct stat file_data;
   DIR* directory;

   directory = opendir(current);
   if (directory == NULL){
      printf("Failed to open directory (%s).\n", current);
      return;
   }


   while (1){
      dir_data = readdir(directory);
      if (dir_data == NULL){
         closedir(directory);
         return;
      }

      // Ignore this and parent directories to prevent madness
      if (strcmp(dir_data->d_name, ".") == 0)
         continue;
      else if (strcmp(dir_data->d_name, "..") == 0)
         continue;
      
      // Build pathname on any non-root calls
      char temp_file_name[MAX_NAME_LENGTH];
      strcpy(temp_file_name, dir_data->d_name);
      if (!is_root)
         sprintf(temp_file_name, "%s/%s", current, dir_data->d_name);
      
      if (stat(temp_file_name, &file_data) == -1){
         int err = errno;
         printf("Failed to stat file (%s) Err%d.\n", temp_file_name, err);
         return;
      }

      // File is a directory - build pathname and call recursively
      if (file_data.st_mode & S_IFDIR){
         char next_dir[MAX_NAME_LENGTH];
         sprintf(next_dir, "%s/%s", current, dir_data->d_name);
         printf("D: %s\n", dir_data->d_name);
         print_directory(0, next_dir);
      } else
         // Normal file, just print & move on
         printf("%s  \n", dir_data->d_name);
   }

}
