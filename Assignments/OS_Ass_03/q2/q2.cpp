/*
Implement a queue using a singly linked list. Declare a global variable to hold the value
of an integer. Now create two thread. One will open a file and read integers from the file
one by one in the declared variable. Second thread will be reading the variable and
insert the data into the linked list. After both threads complete their task the main
program will output the contents of the queue to the screen. Your task is to find out if the
queue has same numbers that were there in the file or are there some missing values or
some numbers in access.
*/
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;
struct node{
    int data;
    node *next;

    node(){
        data = 0;
        next = NULL;
    }

    node(int d){
        data = d;
        next = NULL;
    }
};

node *head = NULL;
int global = 0;
bool flag = false;
bool start = false;

void *readFile(void *arg){
    ifstream file;
    file.open("input.txt");
    while(start == false){
        while(file >> global && flag == false) {
            cout << "Reading " << global << "\n";
            flag = true;
            sleep(1);
        }
        // EOF reached 
        if (file.eof()) {
            cout << "EOF reached :)" << "\n   -- End Of File --   \n";
            break;
        }
    }
    flag = false;
    start = true;
    file.close();

    pthread_exit(NULL);
}

void *insert(void *arg){
    while (start == false){
        while(flag == true){
            node *temp = new node(global);
            if(head == NULL){
                cout << "Inserting " << global << "\n   ----   \n";
                head = temp;
                flag = false;
            }
            else{
                cout << "Inserting " << global << "\n   ----   \n";
                node *ptr = head;
                while(ptr->next != NULL){
                    ptr = ptr->next;
                }
                ptr->next = temp;
                flag = false;
            }
        }
    }
    start = true;
    pthread_exit(NULL);
}

int main(){
    pthread_t t1, t2;
    pthread_create(&t1, NULL, readFile, NULL);
    pthread_create(&t2, NULL, insert, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    node *ptr = head;

    cout << "\nPrinting in main Queue: ";
    while(ptr != NULL){
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
    return 0;
}