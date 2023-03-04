/*
    Muhammad Mahad 21L-6195
Task 2: execlp ( ) and execvp ( )

• With execlp create a directory named demo_folder using mkdir command.
• With execvp create 2 new files file1.txt and file2.txt in the demo_folder you have
created using touch command. Syntax of touch command:
• You can pass multiple filenames as arguments to touch command to create multiple
files.
• List the files in the directory demo_folder using ls command, and call ls command using
execvp.
• Now you have to remove the demo_folder using rm command. This will be called using
execvp. Note: Your will have to pass extra arguments to rm command i.e. -rf to remove
a directory.

*/

#include <stdio.h>
#include <stdlib.h> // For EXIT_SUCCESS
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    // First creating child for each task because
    // exec commands don't return to parent executable.

    // For creating directory
    pid_t f1,f2,f3,f4;
    f1 = fork();
    
    if(f1 < 0) {
        printf("\nError in creating F1\n");
        exit(EXIT_FAILURE);
    }
    else if (f1 == 0)
    {
        // We are in child process

        // creating demo_folder
        execlp("mkdir", "-v", "demo_folder",(char *) 0);

        // execlp doesn't return, So
        printf("\nError in creating demo_folder using execlp\n");

        exit(EXIT_FAILURE);
    }
    // No need to write else statement
    wait(NULL);
    printf("\nSuccessfully created demo_directory\n");


    // Now creating files with execvp
    f2 = fork();
    if(f2 < 0) {
        printf("\nError in creating F2\n");
        exit(EXIT_FAILURE);
    }
    else if (f2 == 0)
    {
        // We are in child process

        // creating 2 files using execvp in demo_folder
        char *args[] = {"touch", "demo_folder/file1.txt", "demo_folder/file2.txt", (char *) 0};

        execvp("touch", args);

        // execvp doesn't return, So
        printf("\nError in creating files using execvp\n");

        exit(EXIT_FAILURE);
    }
    // No need to write else statement
    wait(NULL);
    printf("\nSuccessfully created files\n");
    printf("\nListing files in demo_folder:\n");

    f3 = fork();
    if (f3 <0){
        printf("\nError in creating F3\n");
        exit(EXIT_FAILURE);
    }
    else if(f3 == 0){
        
        char *args[] = {"ls", "demo_folder/", (char *) 0};
        execvp("ls",args);

        printf("\nError in listing files using execvp\n");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    f4 = fork();
    if(f4 < 0){
        printf("\nError in creating F4\n");
        exit(EXIT_FAILURE);
    }
    else if(f4 == 0){
        char *args[] = {"rm", "-rf", "demo_folder/", (char *) 0};
        execvp("rm", args);

        printf("\nError in removing directory using execvp\n");
        exit(EXIT_FAILURE);
    }
    wait(NULL);
    printf("\nSuccessfully removed directory\n");


    
    
    return 0;
}