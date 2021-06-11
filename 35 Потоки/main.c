#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>

#define N 5 // количество магазинов (и мьютексов)
#define M 3 // количество покупателей

int stores[N];
int customer_needs[M];
int working = M;
pthread_mutex_t store_mutexes[N];
pthread_mutex_t work_mutex = PTHREAD_MUTEX_INITIALIZER;

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void *customer_move(void *p)
{
    long n = (long) p; // номер покупателя
    int need = 1;
    while(need > 0) {
        int i = random() % N;
        pthread_mutex_lock(store_mutexes+i);
        need = customer_needs[n] -= stores[i];
        stores[i] = 0;
        pthread_mutex_unlock(store_mutexes+i);
        printf("Покупатель %ld: закупился в магазине %d, потребность %d\n", n, i, need);
        sleep(2);
    }
    pthread_mutex_lock(&work_mutex);
    working--;
    pthread_mutex_unlock(&work_mutex);
    return NULL;
}

void *loader_move(void *p)
{
    int working_local = 1;
    while(working_local > 0) {
        pthread_mutex_lock(&work_mutex);
        working_local = working;
        pthread_mutex_unlock(&work_mutex);

        int i = rand() % N;
        int goods;
        pthread_mutex_lock(store_mutexes+i);
        goods = stores[i] += 500;
        pthread_mutex_unlock(store_mutexes+i);
        printf("Погрузчик: в мазазине %d теперь %d единиц товара\n", i, goods);
        sleep(1);
    };
    return NULL;
}

int main()
{
    for(int i = 0; i < N; i++)
        if(pthread_mutex_init(store_mutexes+i, NULL))
            error("Не могу ициниализировать мьютекс");
    
    srand(time(NULL));
    for(int i = 0; i < N; i++) {
        stores[i] = 950 + (rand() % 100);
        printf("Магазин %d: единиц товара %d\n", i, stores[i]);
    }
        
    for(int i = 0; i < M; i++) {
        customer_needs[i] = 4500 + (rand() % 1000);
        printf("Покупатель %d: потребность %d\n", i, customer_needs[i]);
    }
    
    pthread_t customers[M];
    for(long i = 0; i < M; i++)
        if(pthread_create(customers+i, NULL, customer_move, (void *) i) == -1) // в качестве аргумента передаем номер покупателя
            error("Не могу создать поток");

    pthread_t loader;
    if(pthread_create(&loader, NULL, loader_move, NULL) == -1)
        error("Не могу создать поток");

    for(int i = 0; i < M; i++)
        if(pthread_join(customers[i], NULL))
            error("Не могу дождаться завершения потока");
    if(pthread_join(loader, NULL))
        error("Не могу дождаться завершения потока");

    for(int i = 0; i < N; i++)
        if(pthread_mutex_destroy(store_mutexes+i))
            error("Не могу уничтожить мьютекс");

    return 0;
}