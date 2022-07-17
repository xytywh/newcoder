#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

// 我们可以通过打开两个终端  测试一下  当有一个进程执行了删除共享内存之后  用ipcs -m查看会发现键变成了0(标记共享内存待删除)
// 但是可能还有别的进程和该共享内存连接 因此连接数不为0 只有等到连接数为0的时候才会真正删除该共享内存
int main() {    

    // 1.创建一个共享内存
    int shmid = shmget(100, 4096, IPC_CREAT|0664);
    printf("shmid : %d\n", shmid);
    
    // 2.和当前进程进行关联
    void * ptr = shmat(shmid, NULL, 0);

    char * str = "helloworld";

    // 3.写数据
    memcpy(ptr, str, strlen(str) + 1);

    // 如果我们在执行当前进程  当前面完成共享内存创建以及数据写入之后  如果进程终止了(比如按下ctrl+C)  那么这块共享内存就还在内存中
    // 此时虽然该进程不再执行了  但是我们去执行write_shm.c也还是能读取到数据的  不过如果关机了那就没有了  因为是在内存中
    printf("按任意键继续\n");
    getchar();

    // 4.解除关联
    shmdt(ptr);

    // 5.删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}