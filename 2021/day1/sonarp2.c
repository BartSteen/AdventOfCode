#include <stdio.h>
#include <stdbool.h>

#define SIZE 3

int windowSum(int window[]) {
    int sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += window[i];
    }
    return sum;
}

void printWindow(int window[]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d - ", window[i]);
    }
    printf("\n");
}

int main() {
    int lastSum = 100000000;
    int incCount = 0;
    int window[SIZE];
    int i = 0;

    while (true) {
        int curInput;
        scanf("%d", &curInput);
        if (curInput == -1) {
            break;
        }
        if (i < SIZE) {
            //first couple of fillers
            window[i] = curInput;
            if (i == SIZE - 1) {
                lastSum = windowSum(window);
                // printWindow(window);
                // printf("sum of window: %d\n", lastSum);
            }
        } else {
            //full window
            for (int j = 1; j < SIZE; j++) {
                window[j-1] = window[j];
            }            
            window[SIZE-1] = curInput;
            int curSum = windowSum(window);
            if (curSum > lastSum) {
                incCount++;
            }
            // printWindow(window);
            // printf("sum of window: %d\n", curSum);
            lastSum = curSum;
        }

        i++;
    }
    printf("Total count of increasing: %d", incCount);
    return 0;
}