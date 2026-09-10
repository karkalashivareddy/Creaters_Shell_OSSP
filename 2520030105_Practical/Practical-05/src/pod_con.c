/*
 * Practical-05
 * Producer Consumer Problem
 *
 * Student Name : Karkala Shiva Reddy
 * Roll Number  : 2520030105
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

void sem_wait_op(int semid, int sem_num)
{
    struct sembuf op = {sem_num, -1, 0};
    semop(semid, &op, 1);
}

void sem_signal_op(int semid, int sem_num)
{
    struct sembuf op = {sem_num, 1, 0};
    semop(semid, &op, 1);
}

int main(void)
{
    key_t shm_key, sem_key;
    int shmid, semid;
    int *buffer;
    int in = 0, out = 0;
    union semun arg;
    pid_t pid;
    int i;

    setbuf(stdout, NULL);

    printf("=== Producer Consumer Problem ===\n\n");

    shm_key = ftok("/tmp", 'A');
    sem_key = ftok("/tmp", 'B');

    shmid = shmget(shm_key, BUFFER_SIZE * sizeof(int), IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget failed");
        return 1;
    }

    buffer = (int *)shmat(shmid, NULL, 0);
    if (buffer == (int *)(-1))
    {
        perror("shmat failed");
        return 1;
    }

    semid = semget(sem_key, 3, IPC_CREAT | 0666);
    if (semid < 0)
    {
        perror("semget failed");
        return 1;
    }

    arg.val = BUFFER_SIZE;
    semctl(semid, 0, SETVAL, arg);

    arg.val = 0;
    semctl(semid, 1, SETVAL, arg);

    arg.val = 1;
    semctl(semid, 2, SETVAL, arg);

    printf("Shared memory and semaphores created.\n");
    printf("Buffer size: %d, Items to produce: %d\n\n", BUFFER_SIZE, NUM_ITEMS);

    pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        for (i = 0; i < NUM_ITEMS; i++)
        {
            int item = rand() % 100;

            sem_wait_op(semid, 0);
            sem_wait_op(semid, 2);

            buffer[in] = item;
            printf("Producer: produced item %d at position %d\n", item, in);
            in = (in + 1) % BUFFER_SIZE;

            sem_signal_op(semid, 2);
            sem_signal_op(semid, 1);

            usleep(100000);
        }
        exit(0);
    }
    else
    {
        int consumed = 0;
        while (consumed < NUM_ITEMS)
        {
            sem_wait_op(semid, 1);
            sem_wait_op(semid, 2);

            int item = buffer[out];
            printf("Consumer: consumed item %d from position %d\n", item, out);
            out = (out + 1) % BUFFER_SIZE;
            consumed++;

            sem_signal_op(semid, 2);
            sem_signal_op(semid, 0);

            usleep(150000);
        }

        wait(NULL);

        shmdt(buffer);
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
        semctl(semid, 1, IPC_RMID);
        semctl(semid, 2, IPC_RMID);

        printf("\nAll %d items produced and consumed.\n", NUM_ITEMS);
        printf("Shared memory and semaphores cleaned up.\n");
    }

    return 0;
}
