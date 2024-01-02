#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int main() {

    int depth = 0;
    int hp = 0;
    bool looping = true;
    while (looping) {
        char line[20];
        
        fgets(line, 20, stdin);
        char ss[5];
        switch(line[0]) {
            case '-':
                printf("depth: %d  -  hp: %d\n", depth, hp);
                printf("result: %d\n", depth * hp);
                return 0;
            case 'f':
                strncpy(ss, &line[7], strlen(line)-7);
                hp += atoi(ss);
                break;

            case 'u':
                strncpy(ss, &line[2], strlen(line)-2);
                //printf("%s", ss);
                depth -= atoi(ss);
                break;

            case 'd':
                strncpy(ss, &line[4], strlen(line)-4);
                depth += atoi(ss);  
                break;     
                 
        }
    }

    return 0;
}