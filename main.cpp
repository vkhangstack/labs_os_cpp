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
// #include <pthread.h>
// #include <stdio.h>
// #include <semaphore.h>
//
// sem_t sem1;
// sem_t sem2;
// sem_t sem3;
//
// void *ProccessT1(void *message)
// {
//     printf("Process T1 execute\n");
//     sem_post(&sem1);
//     sem_post(&sem1);
//     return NULL;
// }
// void *ProccessT2(void *message)
// {
//     sem_wait(&sem1);
//     printf("Process T2 execute\n");
//     sem_post(&sem2);
//     return NULL;
// }
// void *ProccessT3(void *message)
// {
//     sem_wait(&sem1);
//     printf("Process T3 execute\n");
//     sem_post(&sem3);
//     return NULL;
// }
// void *ProccessT4(void *message)
// {
//     sem_wait(&sem2);
//     sem_wait(&sem3);
//     printf("Process T4 execute\n");
//     return NULL;
// }
//
// int main()
// {
//     pthread_t idthreadT1, idthreadT2,idthreadT3,idthreadT4;
//     sem_init(&sem1, 0,0);
//     sem_init(&sem2, 0,0);
//     sem_init(&sem3, 0,0);
//
//     pthread_create(
//         &idthreadT1,
//         NULL,
//         &ProccessT1,
//         NULL
//     );
//
//     pthread_create(
//         &idthreadT2,
//         NULL,
//         &ProccessT2,
//         NULL
//     );
//
//
//     pthread_create(
//         &idthreadT3,
//         NULL,
//         &ProccessT3,
//         NULL
//     );
//
//     pthread_create(
//         &idthreadT4,
//         NULL,
//         &ProccessT4,
//         NULL
//     );
//     while (1){}
//     return  0;
// }


// lab01.3
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIZE 10
#define NUM_OPERATIONS 20

// Mảng toàn cục và các biến đếm
int a[MAX_SIZE];
int count = 0;  // Số phần tử hiện tại trong mảng

// Mutex để bảo vệ critical section
pthread_mutex_t mutex;

// Semaphore để đồng bộ hóa
sem_t empty;  // Đếm số slot trống
sem_t full;   // Đếm số phần tử có sẵn

// Hàm thêm phần tử vào mảng (Producer)
void* producer(void* arg) {
    int thread_id = *((int*)arg);

    while (1){
        // Chờ có slot trống
        sem_wait(&empty);

        // Vào critical section
        pthread_mutex_lock(&mutex);

        // Sinh số ngẫu nhiên và thêm vào mảng
        int random_num = rand() % 100;
        a[count] = random_num;
        count++;

        printf("Producer %d: Thêm %d vào mảng. Số phần tử: %d\n",
               thread_id, random_num, count);

        // Ra khỏi critical section
        pthread_mutex_unlock(&mutex);

        // Báo hiệu có thêm một phần tử
        sem_post(&full);
    }
    return NULL;
}

// Hàm lấy phần tử từ mảng (Consumer)
void* consumer(void* arg) {
    int thread_id = *((int*)arg);

    while (1) {
        // Chờ có phần tử để lấy
        sem_wait(&full);

        // Vào critical section
        pthread_mutex_lock(&mutex);

        if (count > 0) {
            // Lấy phần tử cuối cùng (có thể thay đổi logic này)
            int removed_value = a[count - 1];
            count--;

            printf("Consumer %d: Lấy ra %d từ mảng. Số phần tử: %d\n",
                   thread_id, removed_value, count);
        } else {
            printf("Consumer %d: Nothing in array a\n", thread_id);
        }

        // Ra khỏi critical section
        pthread_mutex_unlock(&mutex);

        // Báo hiệu có thêm một slot trống
        sem_post(&empty);

    }

    return NULL;
}


void* unsafe_producer(void* arg) {
  while (1){
        // RACE CONDITION: Không có protection
        if (count < MAX_SIZE) {
            int random_num = rand() % 100;
            a[count] = random_num;
            count++; // LỖI: Có thể bị ghi đè bởi thread khác
            printf("Producer: Thêm %d, count = %d\n", random_num, count);
        }
    }
    return NULL;
}

void* unsafe_consumer(void* arg) {
   while (1){
        // RACE CONDITION: Không có protection
        if (count > 0) {
            int value = a[count - 1];
            count--; // LỖI: Có thể bị ghi đè bởi thread khác
            printf("Consumer: Lấy %d, count = %d\n", value, count);
        } else {
            printf("Consumer: Nothing in array a\n");
        }
    }
    return NULL;
}

int main() {
    // Khởi tạo seed cho random
    srand(time(NULL));

    // Khởi tạo mutex
    pthread_mutex_init(&mutex, NULL);

    // Khởi tạo semaphore
    sem_init(&empty, 0, 10);  // Ban đầu có MAX_SIZE slot trống
    sem_init(&full, 0, 0);          // Ban đầu có 0 phần tử

    // Tạo thread
    pthread_t producer_thread, consumer_thread;
    int producer_id = 1, consumer_id = 1;

    printf("=== CHƯƠNG TRÌNH VỚI ĐỒNG BỘ HÓA ===\n");
    printf("Mảng có thể chứa tối đa %d phần tử\n\n", MAX_SIZE);

    // Tạo và chạy các thread
    pthread_create(&producer_thread, NULL, unsafe_producer, &producer_id);
    pthread_create(&consumer_thread, NULL, unsafe_consumer, &consumer_id);

    // printf("\nChương trình kết thúc. Số phần tử còn lại: %d\n", count);
    while (1){}
    // Chờ các thread kết thúc
    // pthread_join(producer_thread, NULL);
    // pthread_join(consumer_thread, NULL);
    //
    // // Dọn dẹp
    // pthread_mutex_destroy(&mutex);
    // sem_destroy(&empty);
    // sem_destroy(&full);


    return 0;
}

/*
=== PHIÊN BAN KHÔNG ĐỒNG BỘ HÓA (CÓ LỖI) ===

void* unsafe_producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        // RACE CONDITION: Không có protection
        if (count < MAX_SIZE) {
            int random_num = rand() % 100;
            a[count] = random_num;
            count++; // LỖI: Có thể bị ghi đè bởi thread khác
            printf("Producer: Thêm %d, count = %d\n", random_num, count);
        }
        usleep(100000);
    }
    return NULL;
}

void* unsafe_consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        // RACE CONDITION: Không có protection
        if (count > 0) {
            int value = a[count - 1];
            count--; // LỖI: Có thể bị ghi đè bởi thread khác
            printf("Consumer: Lấy %d, count = %d\n", value, count);
        } else {
            printf("Consumer: Nothing in array a\n");
        }
        usleep(150000);
    }
    return NULL;
}

CÁC LỖI KHI CHƯA ĐỒNG BỘ HÓA:

1. RACE CONDITION trên biến 'count':
   - Hai thread có thể đọc/ghi cùng lúc
   - Kết quả không đoán trước được
   - Có thể dẫn đến count sai

2. BUFFER OVERFLOW/UNDERFLOW:
   - Producer có thể thêm quá MAX_SIZE phần tử
   - Consumer có thể lấy từ mảng rỗng

3. DATA CORRUPTION:
   - Truy cập đồng thời vào mảng a[]
   - Có thể đọc dữ liệu đang được ghi

4. INCONSISTENT STATE:
   - count có thể không phản ánh đúng số phần tử thực tế
   - Dẫn đến logic sai

GIẢI PHÁP ĐỒNG BỘ HÓA:

1. MUTEX: Bảo vệ critical section (count, a[])
2. SEMAPHORE:
   - empty: Đếm số slot trống
   - full: Đếm số phần tử có sẵn
3. Đảm bảo atomic operations
*/

/*
CÁCH BIÊN DỊCH VÀ CHẠY:

gcc -o thread_program thread_program.c -lpthread
./thread_program

HOẶC với debug:
gcc -g -Wall -o thread_program thread_program.c -lpthread
*/