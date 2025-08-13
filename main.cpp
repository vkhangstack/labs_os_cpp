// 1.1 Tạo tiểu trình
// #include <iostream>
// #include <pthread.h>
//
// void *thread_print(void *message)
// {
//     while (1)
//         printf("Hello, how are you?\n");
// }
//
//
// int main()
// {
//     pthread_t id_pthread;
//
//     pthread_create(
//         &id_pthread,
//         NULL,
//         &thread_print,
//         NULL
//         );
//     while (1)
//         printf("I'm fine, and you?\n");
//     return 0;
// }

// 1.2. Huỷ tiểu trình
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
//
// #define NUM_THREADS 2
//
// void *thread_print(void *threadid)
// {
//     long tid;
//     tid = (long)threadid;
//     printf("Hello IT007! I'm Thread #%ld!\n", tid);
//     pthread_exit(NULL);
// }
//
// int main()
// {
//     pthread_t threads[NUM_THREADS];
//     int check;
//     long tID;
//
//     for(tID = 0; tID < NUM_THREADS; tID++)
//     {
//         check = pthread_create(
//                     &threads[tID],
//                     NULL,
//                     &thread_print,
//                     (void *)tID
//                 );
//
//         if (check != 0)
//         {
//             printf("[MAIN_THREAD] ERROR! Can't create Thread #%ld\n", tID);
//             exit(-1);
//         }
//     }
//
//
//     sleep(10);
//
//     printf("[MAIN THREAD] Bye bye!\n");
//     pthread_exit(NULL);
//     return 0;
// }

// 1.3. Hợp và gỡ tiểu trình
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
//
// #define NUM_THREADS 2
//
// void *thread_print(void *threadid)
// {
//     long tid;
//     tid = (long)threadid;
//     printf("Hello IT007! I'm Thread #%ld!\n", tid);
//     sleep(10);
//     printf("[%ld] Bye bye\n", tid);
//     pthread_exit(NULL);
// }
//
// int main()
// {
//     pthread_t threads[NUM_THREADS];
//     int check;
//     long tID;
//
//     for(tID = 0; tID < NUM_THREADS; tID++)
//     {
//         printf("[MAIN THREAD] Create Thread #%ld\n", tID);
//         check = pthread_create(
//                     &threads[tID],
//                     NULL,
//                     &thread_print,
//                     (void *)tID
//                 );
//
//         if (check != 0)
//         {
//             printf("[MAIN_THREAD] ERROR! Can't create Thread #%ld\n", tID);
//             exit(-1);
//         }
//
//         // pthread_join(threads[tID], NULL);
//     }
//
//     printf("[MAIN THREAD] Bye bye!\n");
//     pthread_exit(NULL);
//     return 0;
// }

// 1.4. Truyền tham số cho tiểu trình
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
//
// struct print_params
// {
//     char character;
//     int count;
// };
//
// void *char_print(void* args)
// {
//     struct print_params *p = (struct print_params *)args;
//     int i;
//
//     for (i = 0; i < p->count; i++)
//     {
//         printf("%c\n", p->character);
//         printf("%ld\n", i);
//     }
//
//
//     return NULL;
// }
//
// int main()
// {
//     pthread_t tid;
//     struct print_params th_args;
//
//     th_args.character = 'A';
//     th_args.count = 3;
//
//     pthread_create(
//         &tid,
//         NULL,
//         &char_print,
//         &th_args
//     );
//
//     pthread_join(tid, NULL);
//
//     pthread_exit(NULL);
//     return 0;
// }


// 2. Mutex Locks
// #include <pthread.h>
// #include <stdio.h>
//
// int x = 0; // Bien toan cuc, duoc chia se giua A va B
// pthread_mutex_t mut; // Khai bao mutex toan cuc
//
// void *ProcessA(void *message)
// {
//     while(1)
//     {
//         pthread_mutex_lock(&mut); // Lock mutex hay acquire
//         x = x + 1;
//         if (x == 20)
//             x = 0;
//         printf("Process A | x = %d\n", x);
//         pthread_mutex_unlock(&mut); // Unlock mutex hay release
//     }
// }
//
// void *ProcessB(void *message)
// {
//     while(1)
//     {
//         pthread_mutex_lock(&mut); // Lock mutex
//         x = x + 1;
//         if (x == 20)
//             x = 0;
//         printf("Process B | x = %d\n", x);
//         pthread_mutex_unlock(&mut); // Unlock mutex
//     }
// }
//
// int main()
// {
//     pthread_t idthreadA, idthreadB;
//     pthread_mutex_init(&mut, NULL); // Khoi tao mutex
//
//     pthread_create(
//         &idthreadA,
//         NULL,
//         &ProcessA,
//         NULL
//     );
//
//     pthread_create(
//         &idthreadB,
//         NULL,
//         &ProcessB,
//         NULL
//     );
//
//     while(1){}
//
//     return 0;
// }



// 3. Semaphores
// #include <pthread.h>
// #include <stdio.h>
// #include <semaphore.h>
//
// int products = 0, sells = 0; // Bien toan cuc, duoc chia se giua A va B
// sem_t stock; // Khai bao semaphore la toan cuc
// sem_t product_limit;
//
// void *Produce(void *message)
// {
//     while(1)
//     {
//         sem_wait(&product_limit);
//         products++;
//         printf("Produce | products = %d\n", products);
//         sem_post(&stock); // Thao tac signal semaphore
//     }
// }
//
// void *Consume(void *message)
// {
//     while(1)
//     {
//         sem_wait(&stock); // Thao tac wait semaphore
//         sells++;
//         printf("Consume | sells = %d\n", sells);
//         sem_post(&product_limit);
//     }
// }
//
// int main()
// {
//     pthread_t idthreadA, idthreadB;
//     sem_init(&stock, 0, products - sells); // Gia tri khoi tao cua stock la products - sells
//     sem_init(&product_limit, 0,67); // Giới hạn product sản xuất bằng 4 số cuối mssv
//
//     pthread_create(
//         &idthreadA,
//         NULL,
//         &Produce,
//         NULL
//     );
//
//     pthread_create(
//         &idthreadB,
//         NULL,
//         &Consume,
//         NULL
//     );
//
//     while(1){} // Giữ cho tiểu trình main tồn tại để quan sát idthreadA và idthreadB
//
//     return 0;
// }


// lab01.2
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem1;
sem_t sem2;
sem_t sem3;

void *ProccessT1(void *message)
{
    printf("Process T1 execute\n");
    sem_post(&sem1);
    sem_post(&sem1);
    return NULL;
}
void *ProccessT2(void *message)
{
    sem_wait(&sem1);
    printf("Process T2 execute\n");
    sem_post(&sem2);
    return NULL;
}
void *ProccessT3(void *message)
{
    sem_wait(&sem1);
    printf("Process T3 execute\n");
    sem_post(&sem3);
    return NULL;
}
void *ProccessT4(void *message)
{
    sem_wait(&sem2);
    sem_wait(&sem3);
    printf("Process T4 execute\n");
    return NULL;
}

int main()
{
    pthread_t idthreadT1, idthreadT2,idthreadT3,idthreadT4;
    sem_init(&sem1, 0,0);
    sem_init(&sem2, 0,0);
    sem_init(&sem3, 0,0);

    pthread_create(
        &idthreadT1,
        NULL,
        &ProccessT1,
        NULL
    );

    pthread_create(
        &idthreadT2,
        NULL,
        &ProccessT2,
        NULL
    );


    pthread_create(
        &idthreadT3,
        NULL,
        &ProccessT3,
        NULL
    );

    pthread_create(
        &idthreadT4,
        NULL,
        &ProccessT4,
        NULL
    );
    while (1){}
    return  0;
}