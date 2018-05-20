#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>


#define SHM_SIZE 27
char SEM_NAME[] = "vik";

int main()
{
    sem_t* mutex;
    key_t shm_key;
    int shm_id;
    int* shm;  
    int i;
    

    mutex = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if  (mutex == SEM_FAILED)
    {   perror("unable to create semaphore");
        sem_unlink(SEM_NAME);
        exit(-1);
    }

    shm_key = 1000;
    shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | 0666);
    if  (shm_id < 0)
    {   perror("failure in shmget");
        exit(-1);
    }

    shm = shmat(shm_id, NULL, 0);

    printf("client prepare\n");

    for (i = 0; i < 10; i++)
    {
        sem_wait(mutex);
        //*shm = i;
        //printf("server: %d\n", i);
        printf("server\n");
        sleep(1);
        sem_post(mutex);
    }

    sleep(1);

    sem_close(mutex);
    sem_unlink(SEM_NAME);

    shmctl(shm_id, IPC_RMID, 0);

    exit(0);
}