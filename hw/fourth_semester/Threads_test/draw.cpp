#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>

std::mutex consoleMutex;

void printWord(const char* word);

int main() {
    std::thread t0(printWord, "Heads");
    std::thread t1(printWord, "Tails");
    t0.join();
    t1.join();
    return 0;
}

void printWord(const char* word) {
    std::random_device rd;      // Seed source for the random generator
    std::mt19937 gen(rd());     // Create random generator
    std::uniform_int_distribution<int> dtRange(1, 500);

    for (int i = 0; i < 10; ++i) {
        // Sleep for a random time up to 0.5 second
        int dt = dtRange(gen);
        std::this_thread::sleep_for(std::chrono::milliseconds(dt));

        {
            std::unique_lock<std::mutex> bufferLock(consoleMutex);
            std::cout << word << std::endl;
        }
    }
}
