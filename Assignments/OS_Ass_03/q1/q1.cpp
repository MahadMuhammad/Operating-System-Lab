#include <iostream>
#include <chrono>
#include <pthread.h>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

int stop = false;


class AlarmClock {
public:
    void gotoSleepFor(int howLong) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait_for(lock, std::chrono::seconds(howLong));
    }

    void snooze() {
        gotoSleepFor(10);
    }

    void stop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_stop = true;
        m_cv.notify_all();
    }

    void setAlarm() {
        std::unique_lock<std::mutex> lock(m_mutex); // lock the mutex
        int howLong;
        std::cout << "\nTHREAD["<<pthread_self() <<"] Enter the time in seconds: "<< endl;
        // using mutex for synchronization
        
        // unlock mutex
        lock.unlock();
        // wait for user input
        std::cin >> howLong;
        gotoSleepFor(howLong);
        wakeUp();
    }

    // ready queue
    void wakeUp() {
        std::cout << "Wake up!\n";
    }

    void timerInterrupt() {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.notify_all();
    }

    // get mutex
    std::mutex& getMutex() {
        return m_mutex;
    }
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    bool m_stop = false;
};

// Wrapper function for calling the setAlarm() method
void* alarmThread(void* arg) {
    AlarmClock* clock = static_cast<AlarmClock*>(arg);
    clock->setAlarm();
    return nullptr;
}

int main()
{
    std::cout << "\nWelcome to Alarm Clock Class\n";
    queue<pthread_t> readyQueue;

    AlarmClock clock;
    clock.setAlarm();
    
    cout<<"\nEnter no. of threads, to be created: ";
    int n;
    cin>>n;
    // using getMutex() to synchronize the threads
    // std::lock_guard<std::mutex> lock(clock.getMutex());
    // unlonking the mutex
    clock.getMutex().unlock();
    cout << "\nCreating " << n << " threads\n";
    pthread_t t1[n];
    for(int i=0;i<n;i++)
    {
        clock.getMutex().lock();
        
        pthread_create(&t1[i], NULL, alarmThread, &clock);
        // locking the mutex
        clock.getMutex().unlock();
    }
    for(int i=0;i<n;i++)
    {  
        // pushing the thread id to the ready queue
        readyQueue.push(t1[i]);
        pthread_join(t1[i], NULL);
        clock.getMutex().unlock();
    }
    // printing the ready queue
    cout<<"\nReady Queue: ";
    while(!readyQueue.empty())
    {
        cout<<readyQueue.front()<<" \n";
        readyQueue.pop();
    }

    return 0;
}
