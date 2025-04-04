//
// This is a simple example of using semaphores
// for thread synchronization.
//
// The first thread reads a line from stdin and
// passes it to the second thread.
//
// The second thread inverts a line and prints it to stdout.
//
// The first line uses the semaphore "inputReady"
//     to inform the second thread that a line is ready.
//
// The second thread uses the semaphore "invertReady"
//     to inform the first thread that it is ready to process
//     a next line.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

// Thread body functions
void* runInput(void* arg);  // First thread (input a line)
void* runInvert(void* arg); // Second thread (invert a line)

static char line[256];
static bool finished = false;
static sem_t inputReady;
static sem_t invertReady;

int main() {
    pthread_t inputThread, invertThread;

    // Initialize semaphores
    int res = sem_init(
        &inputReady,    // semaphore
        0,              // shared between processes: No
        0               // initial value: input is not ready
    );
    if (res != 0) {
        perror("Could not initialize the first semaphore");
        return -1;
    }
    res = sem_init(
        &invertReady,   // semaphore
        0,              // shared between processes: No
        1               // initial value: invert server is ready
    );
    if (res != 0) {
        perror("Could not initialize the second semaphore");
        return -1;
    }

    // Create the first thread
    res = pthread_create(
        &inputThread,   // Thread identifier
        NULL,           // Thread attributes: using defaults
        &runInput,      // Thread start function
        NULL            // Parameter to be passed to thread function
    );
    if (res != 0) {
        perror("Cannot create the first thread");
        exit(1);
    }

    // Create the second thread
    res = pthread_create(&invertThread, NULL, &runInvert, NULL);
    if (res != 0) {
        perror("Cannot create the second thread");
        exit(1);
    }

    // Wait until threads terminate
    pthread_join(
        inputThread,    // Thread ID
        NULL    // Location to store the return value of thread: not used
    );
    pthread_join(invertThread, NULL);

    sem_destroy(&inputReady);
    sem_destroy(&invertReady);

    return 0;
}

void* runInput(void*) {
    int l;
    while (true) {
        // Wait until second thread is ready
        sem_wait(&invertReady);

        // Read a line from input stream
        printf("Thread 1: Input a line (empty for exit):\n");
        fgets(line, 255, stdin);

        // Remove "\r\n" at the end of line
        l = strlen(line);
        if (l > 0 && line[l-1] == '\n') {
            line[l-1] = 0; --l;
        }
        if (l > 0 && line[l-1] == '\r') {
            line[l-1] = 0; --l;
        }

        if (l == 0)             // Finish on empty line
            finished = true;

        // Pass a line to second thread
        sem_post(&inputReady);
        if (finished)
            break;
    }
    return NULL;
}

void* runInvert(void*) {
    int i, l;
    while (true) {
        // Wait until an input line is ready
        sem_wait(&inputReady);

        // Invert a line
        l = strlen(line);
        for (i = 0; i < l/2; ++i) {
            char tmp = line[i];
            line[i] = line[l-i-1];
            line[l-i-1] = tmp;
        }

        // Print an inverted line
        printf("Thread 2: inverted line:\n%s\n", line);

        // Inform the first thread that the second thread is
        // ready to process a next line
        sem_post(&invertReady);

        if (finished)
            break;
    }
    return NULL;
}
