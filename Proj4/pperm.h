void print_permissions(int mode){
   printf("File Permissions: ");
      
   // print filetype
   if (mode & S_IFDIR)
      printf("d");
   else
      printf("-");

   // print user permissions
//   if (mode & S_IRWXU)
//      printf("rwx");
//   else {
      if (mode & S_IRUSR)
         printf("r");
      else 
         printf("-");
      if (mode & S_IWUSR) 
         printf("w");
      else
         printf("-");
      if (mode & S_IXUSR) 
         printf("x");
      else
         printf("-");
//   }

   // print group permissions
//   if (mode & S_IRWXG)
//      printf("rwx");
//   else {
      if (mode & S_IRGRP)
         printf("r");
      else 
         printf("-");
      if (mode & S_IWGRP) 
         printf("w");
      else
         printf("-");
      if (mode & S_IXGRP) 
         printf("x");
      else
         printf("-");
//   }

   // print other permissions
//   if (mode & S_IRWXO)
//      printf("rwx\n");
//   else {
      if (mode & S_IROTH)
         printf("r");
      else 
         printf("-");
      if (mode & S_IWOTH) 
         printf("w");
      else
         printf("-");
      printf("\n");
//   }
}
