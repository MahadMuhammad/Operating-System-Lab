/* Muhammad Mahad 21L-6195

    exec() family of functions

    1) execl() - execute a file.
        prototype: int execl (const char *path, const char *arg0, ..., const char *argn, (char *) 0);
        execl (path, arg0, arg1, arg2, ..., argn, (char *) 0);
        path: path of the file to be executed.
        arg0: name of the file to be executed.
        arg1: first argument to be passed to the file.
        argn: nth argument to be passed to the file.
        (char *) 0: null pointer to indicate the end of the list of arguments


    2) execlp() - execute a file with path.
        prototype: int 
    3) 
*/
#include <unistd.h>