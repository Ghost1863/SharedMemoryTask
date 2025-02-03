# Shared Memory Example

Этот проект демонстрирует использование разделяемой памяти (shared memory)  для взаимодействия между двумя программами на языке C. Проект состоит из двух программ:
- `write_shared.c` — программа, которая создает разделяемую память и записывает в неё данные.
- `read_shared.c` — программа, которая читает данные из разделяемой памяти.

## Требования

- Компилятор `gcc 11.3.0`
- Docker (для запуска в контейнере)
- Операционная система Linux (или WSL для Windows)

## Сборка и запуск

### 1. Сборка вручную

Клонируйте репозиторий:

   ```bash
   git clone <ваш-репозиторий>
   cd <ваш-репозиторий>
   ```
Скомпилируйте программы:

   ```bash
   gcc -o write_shared src/write_shared.c
   gcc -o read_shared src/read_shared.c
   ```
Запустите программы:

   ```bash
   ./write_shared | ./read_shared
   ```
Программа write_shared создаст разделяемую память, запишет в неё строку "Hello world!" и передаст ключ разделяемой памяти программе read_shared, которая прочитает и выведет данные.

### 2. Запуск скрипта

Вы можете использовать скрипт run.sh для автоматической сборки и запуска программ:
   ```bash
      ./scripts/run.sh
   ```
Скрипт скомпилирует программы, запустит их и удалит бинарные файлы после завершения.

### 3. Запуск с помощью Docker

Соберите Docker-образ:

   ```bash
   docker build -t shared-memory-app .
   ```
Запустите контейнер:

   ```bash
   docker run -it --rm shared-memory-app
   ```
Используйте  скрипт:

   ```bash
   ./scripts/run.sh
   ```
