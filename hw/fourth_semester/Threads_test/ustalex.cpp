#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/times.h>

// Thread body function
void* runUstas(void*);
void* runAlex(void*);

static pthread_mutex_t ustasMutex = PTHREAD_MUTEX_INITIALIZER;
        // PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
static pthread_mutex_t alexMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lineMutex = PTHREAD_MUTEX_INITIALIZER;

static char line[128];
volatile static bool lineProduced = false;
volatile static bool lineConsumed = true;

int main() {
    pthread_t ustas, alex;
    line[0] = 0;

    srand(times(NULL)); // Set the random generator

    // Create the first thread
    int res = pthread_create(
        &ustas,     // Thread identifier
        NULL,       // Thread attributes: using defaults
        &runUstas,  // Thread start function
        NULL        // Parameter to be passed to thread function
    );
    if (res != 0) {
        perror("Cannot create thread 1");
        exit(1);
    }

    // Create the second thread
    res = pthread_create(&alex, NULL, &runAlex, NULL);
    if (res != 0) {
        perror("Cannot create thread 2");
        exit(1);
    }

    // Wait until threads terminate
    pthread_join(
        ustas,  // Thread ID
        NULL    // Location to store the return value of thread: not used
    );
    pthread_join(alex, NULL);

    pthread_mutex_destroy(&ustasMutex);
    pthread_mutex_destroy(&alexMutex);

    return 0;
}

void* runUstas(void*) {
    int i;
    char txt[128];
    bool consumed;
    bool locked = false;

    printf("Ustas thread started.\n");

    i = 0;
    while (i < 11) {
        pthread_mutex_lock(&lineMutex);
        consumed = lineConsumed;
        pthread_mutex_unlock(&lineMutex);

        if (consumed && !locked) {
            pthread_mutex_lock(&ustasMutex);
            locked = true;
            printf("Ustas: mutex locked.\n");
        } else {
            printf("Ustas: line not consumed yet.\n");
        }

        if (consumed) {
            int r = rand();
            r %= 100;
            if (i < 10)
                sprintf(txt, "line %d (%d)", r, i);
            else
                txt[0] = 0;

            pthread_mutex_lock(&lineMutex);
            strcpy(line, txt);
            lineProduced = true;
            lineConsumed = false;
            pthread_mutex_unlock(&lineMutex);

            printf("Ustas: line generated: %s\n", line);

            pthread_mutex_unlock(&ustasMutex);
            locked = false;
            printf("Ustas: mutex unlocked.\n");

            // Wait for Alex to consume a line
            printf("Ustas: Waiting for alex mutex.\n");
            pthread_mutex_lock(&alexMutex);
            pthread_mutex_unlock(&alexMutex);

            ++i;
        }
        sched_yield();
    }

    return NULL;
}

void* runAlex(void*) {
    int i;
    char txt[128];
    bool produced = false;
    bool ended = false;
    bool alexLocked = false;

    printf("Alex thread started.\n");

    while (!ended) {
        // Wait for Ustas to produce a line
        printf("Alex: Waiting for ustas mutex.\n");
        pthread_mutex_lock(&ustasMutex);
        pthread_mutex_unlock(&ustasMutex);

        printf("Alex: Waiting finished.\n");

        printf("Alex: Waiting for line mutex.\n");
        pthread_mutex_lock(&lineMutex);
        produced = lineProduced;
        if (produced) {
            if (!alexLocked) {
                pthread_mutex_lock(&alexMutex);
                alexLocked = true;
            }

            printf("Alex: line produced.\n");
            strcpy(txt, line);
            lineProduced = false;
            ended = (line[0] == 0);
            printf("Alex: line consumed: %s\n", txt);
            lineConsumed = true;
            pthread_mutex_unlock(&lineMutex);

            pthread_mutex_unlock(&alexMutex);
            alexLocked = false;
        } else {
            pthread_mutex_unlock(&lineMutex);
            printf("Alex: line not produced.\n");
        }
        sched_yield();
    }

    return NULL;
}
