/*

    #include <pthread.h>
    void pthread_exit(void *retval);
        功能：终止一个线程，在哪个线程中调用，就表示终止哪个线程
        参数：
            retval:需要传递一个指针，作为一个返回值，可以在pthread_join()中获取到。

    pthread_t pthread_self(void);
        功能：获取当前的线程的线程ID

    int pthread_equal(pthread_t t1, pthread_t t2);
        功能：比较两个线程ID是否相等
        不同的操作系统，pthread_t类型的实现不一样，有的是无符号的长整型（大多数平台），有的
        是使用结构体去实现的，所以不好执行比较值是否相等，需要有一个函数 一般化直接比较值也行
*/
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *callback(void *arg) {
    printf("child thread id : %ld\n", pthread_self());
    return NULL;    // 相当于pthread_exit(NULL);
}

int main() {

    // 创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if (ret != 0) {
        char *errstr = strerror(ret);
        printf("error : %s\n", errstr);
    }

    // 主线程 会和子线程交替执行 所以我们可以看到一个效果就是主线程在打印数字的过程中执行了子线程 即子线程打印了 "child thread id : xxxx"
    for (int i = 0; i < 100; i++) {
        printf("%d\n", i);
    }

    printf("tid : %ld, main thread id : %ld\n", tid, pthread_self());

    // 让主线程退出，当主线程退出时，不会影响其他正常运行的线程。 可以理解下面的return 0或者通常使用exit(0)是结束了一个进程
    pthread_exit(NULL);

    // 主线程都结束了 这里不会打印的
    printf("main thread exit\n");

    return 0;   // exit(0);
}