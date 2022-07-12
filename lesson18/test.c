#include <stdio.h>


void f() {
	printf("HelloWorld!\n");
}

int main() {
	int x = f();
	printf("x = %d\n", x);
	return 0;
}
