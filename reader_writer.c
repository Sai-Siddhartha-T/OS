#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;       // to protect read_count
pthread_mutex_t write_lock;  // for writer mutual exclusion
int read_count = 0;          // number of active readers

void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&mutex);          // lock to change read_count
        read_count++;
        if (read_count == 1)
            pthread_mutex_lock(&write_lock); // first reader locks writers out
        pthread_mutex_unlock(&mutex);

        // Reading section
        printf("Reader %d is READING (active readers = %d)\n", id, read_count);
        usleep(200000); // simulate reading
        printf("Reader %d finished READING\n", id);

        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0)
            pthread_mutex_unlock(&write_lock); // last reader allows writers
        pthread_mutex_unlock(&mutex);

        usleep(200000); // simulate delay before next read
    }
}

void *writer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&write_lock);     // only one writer or readers
        printf("Writer %d is WRITING...\n", id);
        usleep(300000); // simulate writing
        printf("Writer %d finished WRITING\n", id);
        pthread_mutex_unlock(&write_lock);
        usleep(400000); // simulate delay before next write
    }
}

int main() {
    pthread_t r[3], w[2];
    int r_id[3] = {1, 2, 3};
    int w_id[2] = {1, 2};

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&write_lock, NULL);

    // Create reader and writer threads
    for (int i = 0; i < 3; i++)
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &w_id[i]);

    // Join threads (infinite loop, so this never ends)
    for (int i = 0; i < 3; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_lock);
    return 0;
}
