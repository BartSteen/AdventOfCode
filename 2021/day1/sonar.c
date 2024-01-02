#include <stdio.h>

int main() {
    int lastInput = 100000;
    int incCount = 0;

    while (lastInput != -1) {
        int curInput;
        scanf("%d", &curInput);
        //printf("%d", curInput);
        if (curInput > lastInput) {
            incCount++;
          //  printf(" increasing\n");
        } else {
          //  printf("decreasing\n");
        }
        lastInput = curInput;
    }
    printf("Total count of increasing: %d", incCount);
    return 0;
}