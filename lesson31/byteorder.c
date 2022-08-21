/*  
    字节序：字节在内存中存储的顺序。
    小端字节序：数据的高位字节存储在内存的高位地址，低位字节存储在内存的低位地址
    大端字节序：数据的低位字节存储在内存的高位地址，高位字节存储在内存的低位地址
*/

// 通过代码检测当前主机的字节序
#include <stdio.h>

int main() {

    union {
        short value;    // 2字节
        char bytes[sizeof(short)];  // char[2]
    } test;

    test.value = 0x0102;
    // bytes[0]是内存低地址 01是数据高位字节
    if ((test.bytes[0] == 1) && (test.bytes[1] == 2)) {
        printf("大端字节序\n");
        // 打印的结果是201
        printf("test.values=%x\n", test.value);
    } else if ((test.bytes[0] == 2) && (test.bytes[1] == 1)) {
        printf("小端字节序\n");
        // 打印的结果是102   对于数组来说 bytes[0]是低位地址 bytes[1]是高位地址  而对于values来说 左边是高位地址 右边是地位地址
        printf("test.values=%x\n", test.value);
    } else {
        printf("未知\n");
    }

    return 0;
}