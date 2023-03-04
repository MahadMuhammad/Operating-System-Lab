/* Muhammad Mahad 21L-6195

    exec() family of functions

    1) execl() - execute a file. 
        Replace the current process, executing PATH with arguments ARGV and environment ENVP.  ARGV and ENVP are terminated by NULL pointers.  
        prototype: int execl (const char *path, const char *arg0, ..., const char *argn, (char *) 0);
        execl (path, arg0, arg1, arg2, ..., argn, (char *) 0);
        path: path of the file to be executed.
        arg0: name of the file to be executed.
        arg1: first argument to be passed to the file.
        argn: nth argument to be passed to the file.
        (char *) 0: null pointer to indicate the end of the list of arguments


    2) execlp() - execute a file with path.
        prototype: int execlp (const char *file, const char *arg0, ..., const char *argn, (char *) 0);
        execlp (file, arg0, arg1, arg2, ..., argn, (char * n) 0);

    3) execle() - execute a file with environment.
        prototype: int execle (const char * path, const char * arg0, ..., const char * argn, (char *) 0, char * const envp[]);
        execle (path, arg0, arg1, arg2, ..., argn, (char *) 0, envp);
        envp: environment to be passed to the file.

    4) execv(): execute a file with arguments.
        prototype: int execv (const char * path, char * const argv[]);
        execv(path, argv);
        argv: arroy of NULL terminated strings to be passed to the file.

    5) execvp (): execute a file with path and arguments.
        prototype: int execvp (const char * file, char * const argv[]);
        execvp (file, argv);

    6) execve(): Replace the current process, executing PATH with arguments ARGV and environment ENVP.  ARGV and ENVP are terminated by NULL pointers. 
        prototype: int execve (const char * path, char * const argv[], char * const evnp[]);
        execve (path, argv, envp); 
        envp: environment to be passed to the file.

    7) execlpe(): execute a file with path, arguments and environment.
        prototype: int execlpe ( const char * file, const char * arg0, char * arg1, ... , char * argn, (char *) 0, char * const envp[]);
        execlpe (file, arg0, arg1, arg2, ..., argn, (char *) 0, envp );
        envp: environemt to be passed to the file.

    8) execvpe(): Execute FILE, searching in the `PATH' environment variable if it contains no slashes, with arguments ARGV and environment from `environ'. 
        prototype: int execvpe (const char * file, char * const argv[], char * const envp[]);
        execvpe (file, argv, envp);

    9) fexevce(): Execute the file PATH with arguments ARGV and environment.
        prototype: int fexecve (int fd, char * const argv[], char * const envp[]);
        fexecve (fd, argv, envp);

    10) execveat(): Execute the file PATH with arguments ARGV and environment.
        prototype: int execveat (int fd, const char * path, char * const argv[], char * const envp[], int flags);
        execveat (fd, path, argv, envp, flags);

*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
    //int x= execlp("ls", "ls", "-l", (char *) 0);

    // int x = execlp("mkdir","mkdir","mahad", (char *) 0);
    // printf("x = %d \n", x);

    printf("PID of Experimenting.c parent process = %d \n", getpid());
    pid_t pid = fork();

    if (pid < 0){
        printf("Fork Failed");
    }
    else if(pid > 0) {
        wait(NULL);
        printf("\n----- We are in Parent Process -----\n My pid is %d \n", getpid());
        printf("Ending the program\n");
    }
    else if(pid == 0){
        //printf("\n-----We are in the child process-----\nMy pid is %d \n", getpid());
        printf("Calling hello.c from child process\n");

        // int x = exec("hello.c", "hello.c", (char *) 0);

        // paramaters to be passed in function
        char *args[] = {"Hello", "C","Programming", NULL};

        // environment variables
        execv("./hello.out", args);

        exit(EXIT_SUCCESS);
    }
    return 0;
}