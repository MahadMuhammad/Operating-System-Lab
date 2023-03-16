/*
Write a C++/C code to implement the given sorting Algorithms. The main program
thread first generates 1,000,000 Random Integers (or array range can be inserted
dynamically) at runtime and stores these integers in four files (Unsorted_00.txt,
Unsorted_01.txt, Unsorted_02.txt, Unsorted_03.txt) each containing 250,000 integers.

The main thread will then create different threads each one implementing one of
the below given sorting algorithm and parent will wait for these threads to complete
their execution

Each chunk is to be treated as an individual sorting task and implemented by a
separate thread running one of the algorithms given below

Finally when all the threads complete their tasks, they will exit by saving the results
in their respective files, merge.txt, selection.txt, insertion.txt and quick.txt.

When a thread starts it will print its algorithm name, start time and thread id

When the thread ends it will print its exit time

The main program then uses these results further and merges the four sorted lists
together to make one big sorted list

Final sorted list should be stored in a text file named as (Sorted.txt).

The sorting algorithms that you are supposed to implement are:
I. Merge Sort
II. Selection Sort
III. Insertion Sort
IV. Quick Sort

*/

#include <bits/stdc++.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>

using namespace std;

#define MAX 1000000
#define MAX_THREAD 4
#define MAX_FILE 4
#define MAX_CHUNK 250000


int arr[MAX];
int chunk[MAX_THREAD][MAX_CHUNK];
int chunk_size;
int chunk_count;
int file_count;
int file_size;
int file[MAX_FILE][MAX_CHUNK];


void *merge_sort(void *arg);
void *selection_sort(void *arg);
void *insertion_sort(void *arg);
void *quick_sort(void *arg);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);

int main()
{
    // generating random numbers
    srand(time(NULL));
    for(int i=0; i<MAX; i++)
        arr[i] = rand()%MAX;

    // creating 4 files and storing 250000 random numbers in each file
    int fd;
    for(int i=0; i<MAX_FILE; i++)
    {
        string filename = "Unsorted_0" + to_string(i) + ".txt";
        fd = open(filename.c_str(), O_CREAT | O_WRONLY, 0777);
        for(int j=0; j<MAX_CHUNK; j++)
        {
            file[i][j] = arr[i*MAX_CHUNK + j];
            string s = to_string(file[i][j]) + " ";
            write(fd, s.c_str(), s.length());
        }
        close(fd);
    }

    // creating 4 threads
    pthread_t tid[MAX_THREAD];
    pthread_create(&tid[0], NULL, merge_sort, NULL);
    pthread_create(&tid[1], NULL, selection_sort, NULL);
    pthread_create(&tid[2], NULL, insertion_sort, NULL);
    pthread_create(&tid[3], NULL, quick_sort, NULL);

    // waiting for all threads to complete
    for(int i=0; i<MAX_THREAD; i++)
        pthread_join(tid[i], NULL);

    // merging the 4 sorted files into one file named Sorted.txt
    int fd1 = open("Sorted.txt", O_CREAT | O_WRONLY, 0777);

    // reading from 4 files and storing in 4 arrays
    int file1[MAX_CHUNK], file2[MAX_CHUNK], file3[MAX_CHUNK], file4[MAX_CHUNK];
    fd = open("merge.txt", O_RDONLY);
    for(int i=0; i<MAX_CHUNK; i++)
        read(fd, &file1[i], sizeof(int));
    close(fd);
    
    fd = open("selection.txt", O_RDONLY);
    for(int i=0; i<MAX_CHUNK; i++)
        read(fd, &file2[i], sizeof(int));
    close(fd);

    fd = open("insertion.txt", O_RDONLY);
    for(int i=0; i<MAX_CHUNK; i++)
        read(fd, &file3[i], sizeof(int));
    close(fd);

    fd = open("quick.txt", O_RDONLY);
    for(int i=0; i<MAX_CHUNK; i++)
        read(fd, &file4[i], sizeof(int));
    close(fd);

    // merging the 4 arrays into one array and writing to Sorted.txt
    int i=0, j=0, k=0, l=0;

    mergeSort(file1, 0, MAX_CHUNK-1);
    mergeSort(file2, 0, MAX_CHUNK-1);
    mergeSort(file3, 0, MAX_CHUNK-1);
    mergeSort(file4, 0, MAX_CHUNK-1);

    // comparing file1, file2, file3 and file4 and writing the smallest element to Sorted.txt
    fd = open("Sorted.txt", O_CREAT | O_WRONLY, 0777);

    merge (file1, 0, MAX_CHUNK/2 - 1, MAX_CHUNK - 1);
    merge (file2, 0, MAX_CHUNK/2 - 1, MAX_CHUNK - 1);
    merge (file3, 0, MAX_CHUNK/2 - 1, MAX_CHUNK - 1);
    merge (file4, 0, MAX_CHUNK/2 - 1, MAX_CHUNK - 1);

    


    return 0;
}

// merge sort
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    int L[n1], R[n2];
 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// selection sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    for (i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        swap(arr[min_idx], arr[i]);
    }
}

// insertion sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i-1;
 
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }
}

// quick sort
int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// thread functions
void *merge_sort(void *arg)
{
    int fd = open("merge.txt", O_CREAT | O_WRONLY, 0777);
    mergeSort(file[0], 0, MAX_CHUNK-1);
    for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = to_string(file[0][i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    pthread_exit(NULL);
}

void * selection_sort(void *arg)
{
    // selection sort
    int fd = open("selection.txt", O_CREAT | O_WRONLY, 0777);
    selectionSort(file[1], MAX_CHUNK);
    
    // writing to file
    for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = to_string(file[1][i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    pthread_exit(NULL);
}

void * insertion_sort(void *arg)
{
    //insertion sort
    int fd = open("insertion.txt", O_CREAT | O_WRONLY, 0777);
    insertionSort(file[2], MAX_CHUNK);

        // writing to file
    for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = to_string(file[2][i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    pthread_exit(NULL);
}

void *quick_sort(void *arg)
{
    // quick sort
    int fd = open("quick.txt", O_CREAT | O_WRONLY, 0777);
    quickSort(file[3], 0, MAX_CHUNK-1);

    // writing to file
       for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = to_string(file[3][i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    pthread_exit(NULL);
}
    


