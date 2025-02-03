#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1000  /* размер разделяемой памяти */

void sys_err(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int shmid;                    /* идентификатор разделяемой памяти */
    key_t key;                    /* ключ для разделяемой памяти */
    char *shmaddr;                /* адрес разделяемой памяти */
    char input[256];              /* буфер для ввода ключа */

    /* Считывание ключа из стандартного ввода */
    if (fgets(input, sizeof(input), stdin) == NULL) {
        sys_err("client: failed to read key from stdin");
    }

    /* Парсинг ключа из строки */
    if (sscanf(input, "Shared memory key: %d", &key) != 1) {
        sys_err("client: invalid key format");
    }
    printf("Shared memory key from first programm: %d\n",key);

    /* Получение доступа к разделяемой памяти */
    if ((shmid = shmget(key, SHM_SIZE, 0666)) == -1) {
        sys_err("client: shmget error");
    }

    /* Получение адреса разделяемой памяти */
    if ((shmaddr = shmat(shmid, NULL, 0)) == (char *)-1) {
        sys_err("client: shmat error");
    }

    /* Чтение и вывод содержимого разделяемой памяти */
    printf("Shared memory content: %s\n", shmaddr);

    /* Отсоединение от разделяемой памяти */
    if (shmdt(shmaddr) == -1) {
        sys_err("client: shmdt error");
    }

    /* Удаление разделяемой памяти */
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        sys_err("client: shmctl error");
    }

    return 0;
}