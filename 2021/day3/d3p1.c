#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define LANG 12

void printarr(int arr[]) {
    for (int i = 0; i < LANG; i++) {
        printf("%d", arr[i]);
    }
}

int main() {
    int zerocount[LANG];
    int onecount[LANG];

    //init at 0
    for (int i = 0; i < LANG; i++) {
        zerocount[i] = 0;
        onecount[i] = 0;
    }

    while (true) {
        char input[LANG+1]; 
        //printf("Give input\n");
        fgets(input, LANG+2, stdin);
        //printf("%s", input);
        if (input[0] == '-') {
            break;
        } 

        for (int i = 0; i < LANG; i++) {
            if (input[i] == '0') {
                zerocount[i]++;
            } else {
                onecount[i]++;
            }
        }
        // printf("zc: ");
        // printarr(zerocount);
        // printf("\noc: ");
        // printarr(onecount);
        // printf("\n");
    }

    int gamma[LANG];
    int epsilon[LANG];

    for (int i = 0; i < LANG; i++) {
        if (zerocount[i] > onecount[i]) {
            gamma[i] = 0;
            epsilon[i] = 1;
        } else {
            gamma[i] = 1;
            epsilon[i] = 0;
        }
    }
    printf("Epsilon: ");
    printarr(epsilon);
    printf("\nGamma: ");
    printarr(gamma);
    printf("\n");

    int gamdec = 0;
    int epsdec = 0;
    for (int i = LANG - 1; i >= 0; i--) {
        gamdec += gamma[i] * pow(2, LANG - i - 1);
        epsdec += epsilon[i] * pow(2, LANG - i - 1);
    }
    printf("gamma: %d - epsilon: %d\nresult: %d", gamdec, epsdec, gamdec * epsdec);
    return 0;
}