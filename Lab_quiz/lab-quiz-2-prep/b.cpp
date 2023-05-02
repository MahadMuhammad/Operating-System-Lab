/*
    Muhammad Mahad 21L-6195
 */
#include<bits/stdc++.h>
#include<pthread.h>
using namespace std;

// void* thread_func(void* arg)
// {
//     int* arr=(int*)arg;
    
//     int count[10]={0};
//     for(int i=0;i<10;i++)
//     {
//         count[arr[i]]++;
//     }
//     for(int i=0;i<10;i++)
//     {
//         if(count[i]==2)
//         {
//             cout<<"The number "<<i<<" is repeated twice."<<endl;
//         }
//     }
//     return NULL;
// }

void* thread_func(void* arg)
{
    int* arr=(int*)arg;

    // counting frequency without using if using maps
    int sum = 0;
    for(int i=0;i<10;i++)
    {
        sum+=arr[i];
    }
    cout<<"The number "<<sum-45<<" is repeated twice."<<endl;

    return NULL;
}
int main()
{
    int arr[10];
    cout<<"Enter 10 numbers between 1 to 9: ";
    for(int i=0;i<10;i++)
    {
        cout << "\nEnter : ";
        cin>>arr[i];
        while(arr[i] <1 || arr[i] >9){
            cout <<"\nEnter Again : ";
            cin >> arr[i];
            cout << "\n";
        }
        for(int j = i-1; j >= 0 ; j--){
            if(arr[i] == arr[j]){
                arr[9] = arr[i];
            }
        }
    }
    pthread_t tid;
    pthread_create(&tid,NULL,thread_func,(void*)arr);
    pthread_join(tid,NULL);
    return 0;
}
