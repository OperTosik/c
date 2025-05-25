#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>

using namespace std;

mutex m;
string line;
bool lineReady = false;
bool readyToReceiveLine = true;
bool finish = false;
condition_variable cv_lineReady;
condition_variable cv_readyToReceive;

void producerThreadFunction();
void consumerThreadFunction();

int main() {
    thread producerThread(producerThreadFunction);
    thread consumerThread(consumerThreadFunction);

    producerThread.join();
    consumerThread.join();

    return 0;
}

void producerThreadFunction() {
    while (true) {
        unique_lock<mutex> lock(m);
        while (!readyToReceiveLine) {
            cv_readyToReceive.wait(lock);
        }

        cout << "Producer -- enter a string (empty for quit):" << endl;
        getline(cin, line);
        if (line.size() == 0) {
            cout << "Producer thread is finishing" << endl;
            finish = true;
        } else {
            lineReady = true;
        }

        assert(lineReady || finish);
        readyToReceiveLine = false; // Wait for consumer to process the line

        lock.unlock();
        cv_lineReady.notify_one();
        // cout << "Consumer is notified" << endl;

        if (finish)
            break;
    }
}

void consumerThreadFunction() {
    while (true)
    {
        unique_lock<mutex> lock(m);
        while (!lineReady && !finish) {
            cv_lineReady.wait(lock);
        }

        /*
        cout << "Consumer, wait finished" << endl;
        cout << "lineReady = " << lineReady
             << " finish = " << finish << endl;
        */

        if (finish) {
            cout << "Consumer thread finished" << endl;
            break;
        }
        assert(lineReady);

        // Invert the line
        int len = int(line.size());
        int i = 0; int j = len - 1;
        while (i < j) {
            char tmp = line[i];
            line[i] = line[j];
            line[j] = tmp;
            ++i; --j;
        }
        cout << "Consumer -- line Inverted:" << endl
             << line << endl << endl;

        lineReady = false; // Wait for producer to enter the next line
        readyToReceiveLine = true;

        lock.unlock();
        cv_readyToReceive.notify_one();
    }
}
