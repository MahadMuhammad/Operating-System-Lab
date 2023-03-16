/*
Implement an "alarm clock" class. Threads call "Alarm:GoToSleepFor(int howLong)" to
go to sleep for a period of time. The alarm clock can be implemented using the
hardware Timer device (i.e. timer.h). When the timer interrupt goes off, the Timer
interrupt handler checks to see if any thread that had been asleep needs to wake up
now. There is no requirement that threads start running immediately after waking up;
just put them on the ready queue after they have waited for the approximately the right
amount of time. The person will set an alarm and it will display a message after the set
amount of time. Provide the options to snooz alarm for 10 sec or stop the alarm as well.
*/
#include <bits/stdc++.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <threads.h>


using namespace std;



class Timer {
public:
    void start(int howLong) {
        struct itimerval timer;
        timer.it_value.tv_sec = howLong;
        timer.it_value.tv_usec = 0;
        timer.it_interval.tv_sec = 0;
        timer.it_interval.tv_usec = 0;
        setitimer(ITIMER_REAL, &timer, NULL);
    }
};


class AlarmClock {
public:
    void gotoSleepFor(int howLong) {
        Timer timer;
        timer.start(howLong);
        std::this_thread::sleep_for(std::chrono::seconds(howLong));
    }

    void snooze() {
        gotoSleepFor(10);
    }

    void stop() {
        exit(0);
    }

    void setAlarm() {
        int howLong;
        cout << "Enter the time in seconds: ";
        cin >> howLong;
        gotoSleepFor(howLong);
        cout << "Alarm is ringing" << endl;
        cout << "Press 1 to snooze or 2 to stop: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            snooze();
        } else {
            stop();
        }
    }
    

};

int main() {
    AlarmClock alarmClock;
    alarmClock.setAlarm();
    return 0;
}
