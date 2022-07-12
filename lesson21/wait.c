/*
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t wait(int *wstatus);
        功能：等待任意一个子进程结束，如果任意一个子进程结束了，次函数会回收子进程的资源。
        参数：int *wstatus
            进程退出时的状态信息，传入的是一个int类型的地址，传出参数。
        返回值：
            - 成功：返回被回收的子进程的id
            - 失败：-1 (所有的子进程都结束，调用函数失败)

    调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或者收到一个不能被忽略的信号时才被唤醒（相当于继续往下执行）
    如果没有子进程了，函数立刻返回，返回-1；如果子进程都已经结束了，也会立即返回，返回-1.

*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {

    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid;

    // 创建5个子进程
    for (int i = 0; i < 5; i++) {
        pid = fork();
        // 这里要是不加下面的判断，会产生5 + 4 + 3 + 2 + 1 + 1(父进程) = 16个进程
        if (pid == 0) {
            break;
        }
    }

    if (pid > 0) {
        // 父进程
        while (1) {
            printf("parent, pid = %d\n", getpid());


            // 父进程会阻塞在这里，直到某个子进程结束，才会继续往下执行，放在循环里的原因是有多个子进程，一次wait只能回收一个子进程
//            int ret = wait(NULL);
            int st;
            int ret = wait(&st);
            // 没有子进程可以回收了 就结束父进程
            if (ret == -1) {
                break;
            }

            if (WIFEXITED(st)) {
                // 是不是正常退出  退出的状态码就是子进程中调用的exit的入参
                printf("退出的状态码：%d\n", WEXITSTATUS(st));
            }
            if (WIFSIGNALED(st)) {
                // 是不是异常终止
                printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
            }

            // 某个进程结束之后被回收 才能走到这里
            printf("child die, pid = %d\n", ret);

            sleep(1);
        }

    } else if (pid == 0) {
        // 子进程
        int count = 30;
        while (count--) {
            printf("child, pid = %d\n", getpid());
            sleep(1);
        }

        // exit的入参可以自己当前的程序定义的一些宏，可以用于表示程序最终的不同的执行状态
        exit(100);
    }

    return 0; // exit(0)
}