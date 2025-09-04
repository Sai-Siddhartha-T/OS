#include <iostream>     
#include <thread>       
#include <vector>       
#include <semaphore>    
#include <chrono>       

using namespace std;   // So we don’t need to write std:: everywhere

#define N 5   // Number of philosophers (and chopsticks)

// One semaphore for each chopstick
counting_semaphore<1> chopstick[N] { 1, 1, 1, 1, 1 };

// Extra semaphore to limit philosophers inside "room"
counting_semaphore<N-1> room(N-1);   // Only 4 philosophers allowed at once

// Function for each philosopher
void philosopher(int id) {
    while (true) {
        cout << "Philosopher " << id << " is thinking...\n";
        this_thread::sleep_for(chrono::seconds(1));  // Thinking

        room.acquire();  // Enter room (limit to 4 philosophers)

        // Pick up left chopstick
        chopstick[id].acquire();

        // Pick up right chopstick
        chopstick[(id + 1) % N].acquire();

        // Eating
        cout << "Philosopher " << id << " is eating...\n";
        this_thread::sleep_for(chrono::seconds(2));

        // Put down left chopstick
        chopstick[id].release();

        // Put down right chopstick
        chopstick[(id + 1) % N].release();

        room.release();  // Leave room

        cout << "Philosopher " << id << " finished eating.\n";
    }
}

int main() {
    vector<thread> threads;

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        threads.push_back(thread(philosopher, i));
    }

    // Join threads (never ends in this program)
    for (auto& th : threads) {
        th.join();
    }

    return 0;
}
