#include <stdio.h>
#include <stdlib.h>

void func() {
    puts("I'm a func");
}
int main(void) {
    void (*f)() = func;
    f();
    (*f)();
    return EXIT_SUCCESS;
}