/*
    #include <unistd.h>
    unsigned int alarm(unsigned int seconds);
        - 功能：设置定时器（闹钟）。函数调用，开始倒计时，当倒计时为0的时候，
                函数会给当前的进程发送一个信号：SIGALARM
        - 参数：
            seconds: 倒计时的时长，单位：秒。如果参数为0，定时器无效（不进行倒计时，不发信号）。
                    取消一个定时器，通过alarm(0)。
        - 返回值：
            - 之前没有定时器，返回0
            - 之前有定时器，返回之前的定时器剩余的时间

    - SIGALARM ：默认终止当前的进程，每一个进程都有且只有唯一的一个定时器（即后面的定时器会替代前面的）。
        alarm(10);  -> 返回0
        过了1秒
        alarm(5);   -> 返回9 虽然返回9 但其实因为再次调用了alarm函数 所以再过5秒当前进程就终止了

    alarm(100) -> 该函数是不阻塞的
*/

#include <stdio.h>
#include <unistd.h>


// ./alarm1 >> a.txt  重定向  省去IO时间
int main() {

    int seconds = alarm(10);
    printf("seconds = %d\n", seconds);  // 0

    sleep(5);
    printf("start second alarm!\n");
    seconds = alarm(10);    // 不阻塞 下面如果不用while死循环 会直接往下执行  当前程序也就结束了
    printf("seconds = %d\n", seconds);  // 3 上一个打印之后 立即打印当前 说明alarm不阻塞

    while (1) {
        printf("Hello!\n");
        sleep(1); // 这里会打印10次，证明最后一次调用alarm重置了时间
    }

    return 0;
}