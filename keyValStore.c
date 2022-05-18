//
// Created by leonp on 28.04.2022.
//

#include "keyValStore.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 100



struct KeyVal * keyVal;

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
    printf("Key not found.\n");
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
    printf("Key not found.\n");
    return -1;
}

int setKeyVal(struct KeyVal * keyVal1) {
    keyVal = keyVal1;
}

/**
int sizeOfKeyVal() {
    id = shmget(IPC_PRIVATE, sizeof(KeyVal) * SIZE, IPC_CREAT);
    printf("%d\n", id);
    keyVal = (struct KeyVal *) shmat(id, 0, 0);
    return sizeof(KeyVal);
}
*/

