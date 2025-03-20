//
// Simple Thread Example: Perform a Draw (Heads or Tails)
//
// The program create 2 threads.
// The first threads prints 10 times the word "Heads",
// the second thread prints the word "Tails".
// Between printing each thread sleeps a random time
// from 0.5 to 1 second (measured in microseconds).
// The last printed word Heads/Tails is the result of draw.
//
// The mutex is used to exclude the using of monitor
// by both threads at the same time.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// Thread body function
void* run(void* arg);

static pthread_mutex_t mutex = // PTHREAD_MUTEX_INITIALIZER;
    PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

int main() {
    pthread_t thread1, thread2;
    time_t t;
    int num1 = 1;
    int num2 = 2;

    srand((unsigned int) time(&t)); // Set the random generator,
                                    // using the current time
    // Create the first thread
    int res = pthread_create(
        &thread1,   // Thread identifier
        NULL,       // Thread attributes: using defaults
        &run,       // Thread start function
        &num1       // Parameter to be passed to thread function
    );
    if (res != 0) {
        perror("Cannot create thread 1");
        exit(1);
    }
    pthread_mutex_lock(&mutex);
    printf("Thread 1 is created.\n");
    pthread_mutex_unlock(&mutex);

    // Create the second thread
    res = pthread_create(&thread2, NULL, &run, &num2);
    if (res != 0) {
        perror("Cannot create thread 2");
        exit(1);
    }
    pthread_mutex_lock(&mutex);
    printf("Thread 2 is created.\n");
    pthread_mutex_unlock(&mutex);

    // Wait until threads terminate
    pthread_join(
        thread1, // Thread ID
        NULL     // Location to store the return value of thread: not used
    );
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

static const char* HEADS_TAILS[2] = {
    "Heads",
    "Tails"
};

void* run(void* arg) {
    int i;
    int num = *((int *) arg);

    for (i = 0; i < 10; i++) {
        unsigned int r = rand();
        r = r%500000 + 500000; // Sleeping time: from 0.5 to 1 sec,
                               // == from 500000 to 999999 microseconds

        pthread_mutex_lock(&mutex);
        // printf("Thread %d.\n", num);
        printf("%s\n", HEADS_TAILS[num - 1]);
        pthread_mutex_unlock(&mutex);

        sched_yield();  // Give time to other threads
        usleep(r);      // Sleep does the same...
    }
    return NULL;
}
