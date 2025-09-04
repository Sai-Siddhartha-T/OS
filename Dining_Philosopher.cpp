#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;

sem_t chop[5];   // 5 chopsticks
sem_t room;      // semaphore to avoid deadlock

void eat(int i) {
    sem_wait(&room);                 // enter dining room (only 4 allowed)
    sem_wait(&chop[i]);              // pick left chopstick
    sem_wait(&chop[(i+1)%5]);        // pick right chopstick

    cout << "\n Philosopher " << i << " is eating" ;

    sem_post(&chop[(i+1)%5]);        // put down right chopstick
    sem_post(&chop[i]);              // put down left chopstick
    sem_post(&room);                 // leave room
}

int main() {
    thread philosophers[5];          // array of 5 threads

    sem_init(&room, 0, 4);           // allow 4 philosophers at once
    for (int i = 0; i < 5; i++) {
        sem_init(&chop[i], 0, 1);    // each chopstick available
    }

    // create philosopher threads
    for (int i = 0; i < 5; i++) {
        philosophers[i] = thread(eat, i);
    }

    // wait for all philosophers to finish
    for (int i = 0; i < 5; i++) {
        philosophers[i].join();
    }

    // cleanup semaphores
    sem_destroy(&room);
    for (int i = 0; i < 5; i++) {
        sem_destroy(&chop[i]);
    }

    return 0;
}
