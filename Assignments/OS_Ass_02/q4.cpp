/*  
    Muhammad Mahad 21L-6195

    Write a C++ program in which
        1)  a parent process creates a child process using fork () system call.
        2) The child takes a number as input and print its factorial while the parent waits for the child to
            terminate using wait (). 
        3) After the child exit () the parent displays the exit status returned by the
            child and call exit ().

    Resources:
        1) https://www.gnu.org/software/libc/manual/html_node/Process-Completion-Status.html
        2) https://www.ibm.com/docs/en/ztpf/1.1.0.15?topic=apis-waitpidobtain-status-information-from-child-process
        3) https://stackoverflow.com/questions/27306764/capturing-exit-status-code-of-child-process
        4) https://www.ibm.com/docs/en/ztpf/2022?topic=services-ztpf-cc-apis

*/
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t pid = fork(); /*created child process*/

    if (pid > 0) /*parent process*/
    {
        int status;
        wait(&status); /*parent waits for child to terminate*/
        cout<<"\n       --- Child Terminated --- \n";

        if (WIFEXITED(status))/*if child terminated normally*/
        {
            cout << "\n (I am Parent)The child terminated with status : " << WEXITSTATUS(status) ;
            
            // cout << "\n The exit status (factorial of no.) of the child is : " << WEXITSTATUS(status) << "\n";
        }
        if(WEXITSTATUS(status) == 0)
            cout << " (success)\n";
        else
            cout << " (failure)\n";

    }
    else if (pid == 0)  /* Child Process*/
    {
        int num ;
        unsigned fact = 1;  /* unsigned for increasing the range of fact*/
        
        cout << "\n (I am child) Enter a number : ";
        cin >> num;

        if (num < 0)
        {
            cout << "\n Factorial of negative no. is not defined, "
                 << "for refrence you can see https://springerplus.springeropen.com/articles/10.1186/2193-1801-3-658 \n";
            
            // child terminates unsuccessfully
            exit(1);
        }

        for(int i = 1 ; i <= num ; i++ )
            fact *= i;


        cout << "\n The Factorial of the '" << num << "' is : " << fact << "\n";
        
        exit(0); // Child process terminates
        //exit(fact); /* child exit with fact*/
    }
    else if(pid < 0)
        cout << "\n Error ! Child doesn't created";

    return 0;
}

/*
    For factorial of negative no. 
    1) https://springerplus.springeropen.com/articles/10.1186/2193-1801-3-658
    3) https://www.quora.com/What-is-the-factorial-of-negative-numbers
    4) https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1212/assignments/3-recursion/warmup
*/