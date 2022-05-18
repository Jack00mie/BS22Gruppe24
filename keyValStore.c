//
// Created by leonp on 28.04.2022.
//

#include "keyValStore.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 500 //Größe des KeyVal Arrays

typedef struct KeyVal {
    char key[100];
    char value[100];
} KeyVal;

struct KeyVal * keyVal;

int * i;
int idKV;
int idi;

int put(char *key, char *value) {
    strcpy(keyVal[*i].key, key);
    strcpy(keyVal[*i].value, value);
    printf("%s\n",keyVal[*i].key);
    printf("%s\n",keyVal[*i].value);
    *i += 1;
    return 0;
}

int get(char *key, char *value) {
    for(int j = 0; j < *i; j++) {
        if(strcmp(keyVal[j].key, key) == 0) {
            strcpy(value, keyVal[j].value);
            return 0;
        }
    }
    printf("Key not found.\n");
    return -1;
}

int del(char *key) {
    for(int j = 0; j < *i; j++) {
        if(strcmp(keyVal[j].key, key) == 0) {
            for(int k = j; k < *i - 1; k++) {
                strcpy(keyVal[k].key, keyVal[k + 1].key);
                strcpy(keyVal[k].value, keyVal[k + 1].value);
            }
            *i -= 1;
            return 0;
        }
    }
    printf("Key not found.\n");
    return -1;
}


int initializeKeyValShM() {
    idKV = shmget(IPC_PRIVATE, sizeof(KeyVal) * SIZE, IPC_CREAT|0777); // 0600 // 0666
    printf("Shared Memory mit id: %d wurde erstellt\n", idKV);
    keyVal = (struct KeyVal *) shmat(idKV, 0, 0);

    idi = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0777); // 0600 // 0666
    printf("Shared Memory mit id: %d wurde erstellt\n", idi);
    i = (int *) shmat(idi, 0, 0);

    *i = 0;
}

int dtKeyValShM() {
    shmdt(i);
    shmdt(keyVal);
}

int rmKeyValShM() {
    shmctl(idi, IPC_RMID, 0);
    shmctl(idKV, IPC_RMID, 0);
}

