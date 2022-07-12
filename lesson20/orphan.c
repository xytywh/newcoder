#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    // 创建子进程
    pid_t pid = fork();

    // 判断是父进程还是子进程
    if (pid > 0) {

        printf("i am parent process, pid : %d, ppid : %d\n", getpid(), getppid());

    } else if (pid == 0) {
        // 这里睡眠一秒 等待父进程已经结束了  从而可以当前子进程变成孤儿进程的效果
        sleep(1);
        // 当前是子进程
        printf("i am child process, pid : %d, ppid : %d\n", getpid(), getppid());

    }

    // for循环
    for (int i = 0; i < 3; i++) {
        printf("i : %d , pid : %d\n", i, getpid());
    }



    // 打印是下面的形式 原因是当前进程(1553)的父进程是当前终端 结束之后会切换到前台(即会打印出xytywh@LAPTOP-9JN0V0LG:/xxxx) 当前终端进程
    // 并不知道他的子进程还有一个子进程
//    xytywh@LAPTOP-9JN0V0LG:/mnt/d/My_Project/newcoder/lesson20$ ./orphan
//    i am parent process, pid : 1553, ppid : 541
//    i : 0 , pid : 1553
//    i : 1 , pid : 1553
//    i : 2 , pid : 1553
//    xytywh@LAPTOP-9JN0V0LG:/mnt/d/My_Project/newcoder/lesson20$ i am child process, pid : 1554, ppid : 1
//    i : 0 , pid : 1554
//    i : 1 , pid : 1554
//    i : 2 , pid : 1554

    return 0;
}
