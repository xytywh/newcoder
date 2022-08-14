#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *print(void *mutex) {
    printf("mutex=%d\n", *(int *) mutex);
    return NULL;
}

int main() {

    int mutex = 100;

    // 创建3个子线程
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, print, &mutex);
    pthread_create(&tid2, NULL, print, &mutex);
    pthread_create(&tid3, NULL, print, &mutex);

    // 回收子线程的资源,阻塞
    pthread_detach(tid1);
    pthread_detach(tid2);
    pthread_detach(tid3);

    pthread_exit(NULL); // 退出主线程

    return 0;
}