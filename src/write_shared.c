#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1000  /* размер разделяемой памяти */
#define PERMS 0666     /* права доступа */

void sys_err(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int shmid;                    /* идентификатор разделяемой памяти */
    key_t key;                    /* ключ для разделяемой памяти */
    char *shmaddr;                /* адрес разделяемой памяти */

    /* Генерация ключа для разделяемой памяти */
    if ((key = ftok(".", 'A')) == -1) {
        sys_err("client: ftok error");
    }
    
    /* Создание региона разделяемой памяти */
    if ((shmid = shmget(key, SHM_SIZE, PERMS | IPC_CREAT)) == -1) {
        sys_err("client: shmget error");
    }

    /* Получение адреса разделяемой памяти */
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *)-1) {
        sys_err("client: shmat error");
    }

    /* Запись строки "Hello world!" в разделяемую память */
    strncpy(shmaddr, "Hello world!", SHM_SIZE);

    /* Вывод ключа разделяемой памяти */
    printf("Shared memory key: %d\n", key);

    /* Отсоединение от разделяемой памяти */
    if (shmdt(shmaddr) == -1) {
        sys_err("client: shmdt error");
    }

    return 0;
}