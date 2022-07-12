/*
    #include <stdlib.h>
    void exit(int status);

    #include <unistd.h>
    void _exit(int status);

    status参数：是进程退出时的一个状态信息。父进程回收子进程资源的时候可以获取到。
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    printf("hello\n");
    printf("world");

    // 打印 hello
    // world
    // exit(0);
    // 打印hello 不会打印world 因为_exit不会刷新缓冲区 而wordld内容还在缓冲区中
    _exit(0);
    
    return 0;
}