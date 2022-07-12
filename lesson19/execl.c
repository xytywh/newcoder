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

int main() {


    // 创建一个子进程，在子进程中执行exec函数族中的函数
    pid_t pid = fork();

    if(pid > 0) {
        // 父进程
        printf("i am parent process, pid : %d\n",getpid());
        // 这里要加sleep，不然会产生孤儿进程
        sleep(1);
    }else if(pid == 0) {
        // 子进程
        // execl("hello","hello",NULL);

        execl("/bin/ps", "ps", "aux", NULL);
        // 找不到ps，不会从环境变量中去找，默认是当前路径，找不到就不执行，就会执行下面的内容
        execl("ps", "ps", "aux", NULL);
        // 执行上面的execl之后，当前进程内容被替换，后面的都不会再执行了
        perror("execl");
        printf("i am child process, pid : %d\n", getpid());

    }

    for(int i = 0; i < 3; i++) {
        printf("i = %d, pid = %d\n", i, getpid());
    }


    return 0;
}