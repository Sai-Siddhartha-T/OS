 #include <iostream>
#include <thread>
#include <vector>
#include <semaphore.h>   // POSIX semaphores
#include <unistd.h>      // sleep function

using namespace std;

#define N 5

sem_t chopstick[N];   // One semaphore per chopstick
sem_t room;           // Semaphore to prevent deadlock (max N-1 philosophers)

void philosopher(int id) {
    while (true) {
        cout << "Philosopher " << id << " is thinking...\n";
        sleep(1);  // Thinking for 1 second

        sem_wait(&room);           // Enter room (limit to N-1 philosophers)
        sem_wait(&chopstick[id]);  // Pick up left chopstick
        sem_wait(&chopstick[(id + 1) % N]); // Pick up right chopstick

        cout << "Philosopher " << id << " is eating...\n";
        sleep(2);  // Eating for 2 seconds

        sem_post(&chopstick[id]);          // Put down left chopstick
        sem_post(&chopstick[(id + 1) % N]); // Put down right chopstick
        sem_post(&room);                    // Leave room

        cout << "Philosopher " << id << " finished eating.\n";
    }
}

int main() {
    vector<thread> threads;

    // Initialize chopstick semaphores to 1
    for (int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    // Initialize room semaphore to N-1
    sem_init(&room, 0, N-1);

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        threads.push_back(thread(philosopher, i));
    }

    // Join threads
    for (auto& th : threads) {
        th.join();
    }

    // Destroy semaphores (optional, not reached here)
    for (int i = 0; i < N; i++) {
        sem_destroy(&chopstick[i]);
    }
    sem_destroy(&room);

    return 0;
}
