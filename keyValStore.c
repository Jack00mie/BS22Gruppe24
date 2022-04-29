//
// Created by leonp on 28.04.2022.
//

#include "keyValStore.h"
#include <stdio.h>
#include <string.h>

typedef struct KeyVal {
    char key[100];
    char value[100];
} KeyVal;

struct KeyVal keyVal[500];
int i = 0;

int put(char *key, char *value) {
    strcpy(keyVal[i].key, key);
    strcpy(keyVal[i].value, value);
    printf("%s\n",keyVal[i].key);
    printf("%s\n",keyVal[i].value);
    i++;
    return 0;
}

int get(char *key, char *value) {
    for(int j = 0; j < i; j++) {
        if(strcmp(keyVal[j].key, key) == 0) {
            strcpy(value, keyVal[j].value);
            return 0;
        }
    }
    printf("Key not found.");
    return -1;
}

int del(char *key) {
    for(int j = 0; j < i; j++) {
        if(strcmp(keyVal[j].key, key) == 0) {
            for(int k = j; k < i - 1; k++) {
                strcpy(keyVal[k].key, keyVal[k + 1].key);
                strcpy(keyVal[k].value, keyVal[k + 1].value);
            }
            i--;
            return 0;
        }
    }
    printf("Key not found.");
    return -1;
}
#include "keyValStore.h"
