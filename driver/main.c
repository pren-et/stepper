#include "stdio.h"
#include "l6480.h"

int main(void) {
    printf("Hello World\n");
    l6480_init();
    printf("hardhiz\n");
    l6480_cmd_hardhiz();
    printf("run\n");
    l6480_cmd_run(1, 2);
    return 0;
}
