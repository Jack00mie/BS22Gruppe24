//
// Created by leonp on 28.04.2022.
//

#ifndef UNTITLED_KEYVALSTORE_H
int put(char *key, char *value);

int get(char *key, char *res);

int del(char *key);

#define UNTITLED_KEYVALSTORE_H

typedef struct KeyVal {
    char key[100];
    char value[100];
} KeyVal;

int setKeyVal(struct KeyVal * keyVal1);

int initializeKeyValSM();

#endif //UNTITLED_KEYVALSTORE_H
