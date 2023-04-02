/*
    Muhammad Mahad 21L-6195

Write only algoritm  to implement the given sorting Algorithms. The main program
thread first generates 1,000,000 Random Integers (or array range can be inserted
dynamically) at runtime and stores these integers in four files (Unsorted_00.txt,
Unsorted_01.txt, Unsorted_02.txt, Unsorted_03.txt) each containing 250,000 integers.
The main thread will then create 4 different threads each one implementing one of
the below given sorting algorithm and parent will wait for these threads to complete
their execution
1) Each chunk is to be treated as an individual sorting task and implemented by a
separate thread running one of the algorithms given below
2) Finally when all the threads complete their tasks, they will exit by saving the results
in their respective files, merge.txt, selection.txt, insertion.txt and quick.txt.
3) When a thread starts it will print its algorithm name, start time and thread id
4) When the thread ends it will print its exit time
5)The main program then uses these results further and merges the four sorted lists
together to make one big sorted list
 Final sorted list should be stored in a text file named as (Sorted.txt).
The sorting algorithms that you are supposed to implement are:
Merge Sort in first file.
Selection Sort in 2nd file.
Insertion Sort
Quick Sort
*/
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <pthread.h>
#include <chrono>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

# define MAX 1000000
# define MAX_FILE 4
# define MAX_CHUNK  MAX / MAX_FILE
int COUNT =0;

int file[MAX_FILE][MAX_CHUNK];
int arr[MAX];
bool ctw = true; // check to write

// defining functions prototypes
void *mergesort(void *arg);
void *selectionsort(void *arg);
void *insertionsort(void *arg);
void *quicksort(void *arg);

// sorting functions
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
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

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

void QuickSort(int arr[], int low, int high)
{
    int i = low, j = high;
    int tmp;
    int pivot = arr[(low + high) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    };

    /* recursion */
    if (low < j)
        QuickSort(arr, low, j);
    if (i < high)
        QuickSort(arr, i, high);
}

// Inline function to print the start time
inline void printStartTime() {
    std::cout << "  Start time: " << std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() << " ms" << std::endl;
}

// Inline function to print the end time
inline void printEndTime() {
    std::cout << "  End time: " << std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() << " ms" << std::endl;
}

// Inline function to print the time difference in milliseconds
inline void printTimeDifference() {
    auto start = std::chrono::high_resolution_clock::now();
    // Do some work here...
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "  Time difference: " << duration.count() << " ms" << std::endl;
}

// Inline function to print the thread id pthread_self()
inline void printThreadId() {
    std::cout << "  Thread id: " << std::this_thread::get_id() << std::endl;
}

inline void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}




// iterative merge sort
void mergeSortIterative(int arr[], int n)
{
    int curr_size;  // For current size of subarrays to be merged
                    // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
                    // to be merged

    // Merge subarrays in bottom up manner.  First merge subarrays of
    // size 1 to create sorted subarrays of size 2, then merge subarrays
    // of size 2 to create sorted subarrays of size 4, and so on.
    for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
    {
        // Pick starting point of different subarrays of current size
        for (left_start=0; left_start<n-1; left_start += 2*curr_size)
        {
            // Find ending point of left subarray. mid+1 is starting
            // point of right
            int mid = min(left_start + curr_size - 1, n-1);

            int right_end = min(left_start + 2*curr_size - 1, n-1);

            // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
            merge(arr, left_start, mid, right_end);
        }
    }
}

bool mergefiles(const std::string& file1, const std::string& file2, const std::string& file3, 
                const std::string& file4)
{
    std::ifstream in1(file1);
    std::ifstream in2(file2);
    std::ifstream in3(file3);
    std::ifstream in4(file4);
    std::ofstream out("Sorted.txt");

    std::vector<int> v;
    int x;
    while (in1 >> x) v.push_back(x);
    while (in2 >> x) v.push_back(x);
    while (in3 >> x) v.push_back(x);
    while (in4 >> x) v.push_back(x);

    std::sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); ++i)
        out << v[i] << " ";

    return true;
}

int main()
{
    // fast input output
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

   int fd;

    // generating random numbers and storing in arr and Unsorted.txt
    srand(time(NULL));

    fd = open("Unsorted.txt", O_CREAT | O_WRONLY, 0777);
    for(int i=0; i<MAX; i++){
        arr[i] = rand()%MAX;
        string s = to_string(arr[i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);

    // creating 4 files and storing MAX/4 random numbers in each file
    for(int i=0; i<MAX_FILE; i++){
        string filename = "Unsorted_0" + to_string(i) + ".txt";
        fd = open(filename.c_str(), O_CREAT | O_WRONLY, 0777);
        for(int j=0; j<MAX_CHUNK; j++){
            file[i][j] = arr[i*MAX_CHUNK + j];
            string s = to_string(file[i][j]) + " ";
            write(fd, s.c_str(), s.length());
        }
        close(fd);
    }

    // creating 4 threads for each file
    pthread_t threads[MAX_FILE];

    // creating threads
    // for(int i=0; i<MAX_FILE; i++){
    //     string filename = "Unsorted_0" + to_string(i) + ".txt";
    //     pthread_create(&threads[i], NULL, mergesort, (void *)filename.c_str());
    // }

    pthread_create(&threads[0], NULL, mergesort, NULL);
    pthread_create(&threads[1], NULL, selectionsort, NULL);
    pthread_create(&threads[2], NULL, insertionsort, NULL);
    pthread_create(&threads[3], NULL, quicksort, NULL);

    // joining threads
    for(int i=0; i< MAX_FILE; i++)
        pthread_join(threads[i], NULL);

    // merging and sorting insertion.txt, selection.txt, quick.txt and merge.txt
    int fd1 = open("insertion.txt", O_RDONLY);
    int fd2 = open("selection.txt", O_RDONLY);
    int fd3 = open("quick.txt", O_RDONLY);
    int fd4 = open("merge.txt", O_RDONLY);


    //using bool mergefiles(const std::string& file1, const std::string& file2, const std::string& file3, 
                // const std::string& file4) function
    if(mergefiles("insertion.txt", "selection.txt", "quick.txt", "merge.txt"))
        cout << "Sorted.txt created successfully" << "\n";
    else
        cout << "Error in creating Sorted.txt" << "\n";




    

    cout << "\nMain Thread: " << pthread_self() << " ended" << "\n";
    // cout << COUNT;
    return 0;
}

// defining functions
void *mergesort(void *arg)
{
    if(ctw == true){
        ctw = false;
        cout << "Merge Sort:  "; printThreadId();cout<<"\n";
        cout << "Merge Sort:  ";printStartTime();cout<<"\n";
        ctw = true;
    }
    // cout << "Merge Sort:  "; printThreadId();cout<<"\n";
    // cout << "Merge Sort:  ";printStartTime();cout<<"\n";


    // reading from Unsorted_00.txt
    int fd = open("Unsorted_00.txt", O_RDONLY);
    int arr[MAX_CHUNK];

    // reading from file and storing in arr
    for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = "";
        char c;
        while(read(fd, &c, 1) && c != ' ')
            s += c;
        arr[i] = stoi(s);
        // cout << arr[i] << " ";
    }
    close(fd);

    // using merge sort
    mergeSort(arr, 0, MAX_CHUNK-1);

    // writing to Sorted_00.txt
    fd = open("merge.txt", O_CREAT | O_WRONLY, 0777);
    for(int i=0; i<MAX_CHUNK; i++){
        string s = to_string(arr[i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    // cout << "Sorted_00.txt created" << endl;

    // COUNT++;     // for debugging
    // cout <<"  ";
    if(ctw == true){
        ctw = false;
        cout << "Merge Sort:  ";printEndTime();cout<<"\n";
        // cout << "Merge Sort:  ";printTimeDifference();cout<<"\n";
        ctw = true;
    }
    // cout << "Merge Sort:  ";printEndTime();cout<<"\n";
    // cout << "Merge Sort:  ";printTimeDifference();cout<<"\n";
    pthread_exit(NULL);
}

void *selectionsort(void *arg)
{
    if (ctw == true){
        ctw = false;
        cout << "Selection Sort:  "; printThreadId();cout<<"\n";
        cout << "Selection Sort:  ";printStartTime();cout<<"\n";
        ctw = true;
    }

    // reading from Unsorted_01.txt
    int fd = open("Unsorted_01.txt", O_RDONLY);
    int arr[MAX_CHUNK];

    // reading from file and storing in arr
    for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = "";
        char c;
        while(read(fd, &c, 1) && c != ' ')
            s += c;
        arr[i] = stoi(s);
    }
    close(fd);

    // using selection sort
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < MAX_CHUNK-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < MAX_CHUNK; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }

    // writing to Sorted_01.txt
    fd = open("selection.txt", O_CREAT | O_WRONLY, 0777);
    for(int i=0; i<MAX_CHUNK; i++){
        string s = to_string(arr[i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    // cout << "Sorted_01.txt created" << endl;

    // COUNT++;     // for debugging
    if (ctw == true){
        ctw = false;
        cout << "Selection Sort:  ";printEndTime();cout<<"\n";
        // cout << "Selection Sort:  ";printTimeDifference();cout<<"\n";
        ctw = true;
    }
    // cout << "Selection Sort:  ";printEndTime();cout<<"\n";
    // cout << "Selection Sort:  ";printTimeDifference();cout<<"\n";
    
    
    pthread_exit(NULL);
}

void *insertionsort(void *arg)
{
    if (ctw == true){
        ctw = false;
        cout << "Insertion Sort:  "; printThreadId();cout<<"\n";
        cout << "Insertion Sort:  ";printStartTime();cout<<"\n";
        ctw = true;
    }
    // cout << "Insertion Sort:  ";printThreadId();cout<<"\n";
    // cout << "Insertion Sort:  ";printStartTime();cout<<"\n";
    

    // reading from Unsorted_02.txt
    int fd = open("Unsorted_02.txt", O_RDONLY);
    int arr[MAX_CHUNK];

    // reading from file and storing in arr
    for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = "";
        char c;
        while(read(fd, &c, 1) && c != ' ')
            s += c;
        arr[i] = stoi(s);
    }
    close(fd);

    // using insertion sort
    int i, key, j;
    for (i = 1; i < MAX_CHUNK; i++)
    {
        key = arr[i];
        j = i-1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }

    // writing to Sorted_02.txt
    fd = open("insertion.txt", O_CREAT | O_WRONLY, 0777);
    for(int i=0; i<MAX_CHUNK; i++){
        string s = to_string(arr[i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    // cout << "Sorted_02.txt created" << endl;

    // COUNT++;     // for debugging
    if(ctw == true){
        ctw = false;
        cout << "Insertion Sort:  ";printEndTime();cout<<"\n";
        // cout << "Insertion Sort:  ";printTimeDifference();cout<<"\n";
        ctw = true;
    }
    // cout << "Insertion Sort:  ";printEndTime();cout<<"\n";
    // cout << "Insertion Sort:  ";printTimeDifference();cout<<"\n";
    
    
    pthread_exit(NULL);
}

void *quicksort(void *arg)
{
    if (ctw == true){
        ctw = false;
        cout << "Quick Sort:  "; printThreadId();cout<<"\n";
        cout << "Quick Sort:  ";printStartTime();cout<<"\n";
        ctw = true;
    }
    // cout << "Quick Sort:  ";printThreadId();cout<<"\n";
    // cout << "Quick Sort:  ";printStartTime();cout<<"\n";
    

    // reading from Unsorted_03.txt
    int fd = open("Unsorted_03.txt", O_RDONLY);
    int arr[MAX_CHUNK];

    // reading from file and storing in arr
    for(int i=0; i<MAX_CHUNK; i++)
    {
        string s = "";
        char c;
        while(read(fd, &c, 1) && c != ' ')
            s += c;
        arr[i] = stoi(s);
    }
    close(fd);

    // using quick sort
    QuickSort(arr, 0, MAX_CHUNK-1);

    // writing to Sorted_03.txt
    fd = open("quick.txt", O_CREAT | O_WRONLY, 0777);
    for(int i=0; i<MAX_CHUNK; i++){
        string s = to_string(arr[i]) + " ";
        write(fd, s.c_str(), s.length());
    }
    close(fd);
    // cout << "Sorted_03.txt created" << endl;

    // COUNT++;     // for debugging
    if(ctw == true){
        ctw = false;
        cout << "Quick Sort:  ";printEndTime();cout<<"\n";
        // cout << "Quick Sort:  ";printTimeDifference();cout<<"\n";
        ctw = true;
    }
    // cout << "Quick Sort:  ";printEndTime();cout<<"\n";
    // cout << "Quick Sort:  ";printTimeDifference();cout<<"\n";
    
    
    pthread_exit(NULL);
}

