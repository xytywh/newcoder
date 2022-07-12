/*
    #include <unistd.h>
    int execl(const char *path, const char *arg, ...);
        必须要写绝对路径，否则不会到环境变量中去找该可执行文件
        - 参数：
            - path:需要指定的执行的文件的路径或者名称
                a.out /home/nowcoder/a.out 推荐使用绝对路径
                ./a.out hello world

            - arg:是执行可执行文件所需要的参数列表
                第一个参数一般没有什么作用，为了方便，一般写的是执行的程序的名称
                从第二个参数开始往后，就是程序执行所需要的的参数列表。
                参数最后需要以NULL结束（哨兵）

        - 返回值：
            只有当调用失败，才会有返回值，返回-1，并且设置errno
            如果调用成功，没有返回值。

*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {


    // 创建一个子进程，在子进程中执行exec函数族中的函数
    pid_t pid = fork();

    if (pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n", getpid());
        // 这里要加sleep，不然会产生孤儿进程
        sleep(1);
    } else if (pid == 0) {
        // 子进程
        // 最后传的环境变量参数envp必须是下面的类型才可以
        char *command[] = {"ps", "aux", NULL};
        char *envp[] = {"/mnt/d/My_Project/newcoder/lesson19/", NULL};
        int a = rand() % 20;
        a = 11;
        switch (a) {
            case 0:
                printf("case :%d\n", 0);
                execl("hello", "hello", NULL);
                break;
            case 1:
                printf("case :%d\n", 1);
                execl("/bin/ps", "ps", "aux", NULL);
                break;
            case 2:
                printf("case :%d\n", 2);
                // 找不到ps，不会从环境变量中去找，默认是当前路径，找不到就不执行，就会执行下面的内容
                execl("ps", "ps", "aux", NULL);
                break;
            case 3:
                printf("case :%d\n", 3);
                // 找不到，回到环境变量中去找，环境变量中没有，所以找不到
                execlp("hello", "hello", NULL);
                break;
            case 4:
                printf("case :%d\n", 4);
                // 可以找到，因为指定了绝对路径
                execlp("./hello", "hello", NULL);
                break;
            case 5:
                printf("case :%d\n", 5);
                // 下面两个写法都可以找到，一个通过绝对路径能找到，一个通过环境变量也能找到
                execlp("ps", "ps", "aux", NULL);
                break;
            case 6:
                printf("case :%d\n", 6);
                execlp("/bin/ps", "ps", "aux", NULL);
                break;
            case 7:
                printf("case :%d\n", 7);
                execle("hello", "hello", NULL, envp);
                break;
            case 8:
                printf("case :%d\n", 7);
                // 找不到ps，不会从环境变量中去找，默认是当前路径，找不到就不执行，就会执行下面的内容
                execv("ps", command);
                break;
            case 9:
                printf("case :%d\n", 7);
                // 给定绝对路径是可以找到的
                execv("/bin/ps", command);
                break;
            case 10:
                printf("case :%d\n", 7);
                // 会到环境变量中找，可以找到
                execvp("ps", command);
                break;
            case 11:
                printf("case :%d\n", 7);
                // 会到环境变量中找，可以找到
                execvpe("hello", command, envp);
                break;
            case 12:
                printf("case :%d\n", 7);
                // 会到环境变量envp中找，可以找到
                execve("hello", command, envp);
                break;
            default:
                break;
        }

        // 成功执行上面的execXXX之后，当前进程内容被替换，后面的都不会再执行了，否则的话没有被替换，下面的继续执行
        perror("execl");
        printf("i am child process, pid : %d\n", getpid());

    }

    for (int i = 0; i < 3; i++) {
        printf("i = %d, pid = %d\n", i, getpid());
    }z`


    return 0;
}