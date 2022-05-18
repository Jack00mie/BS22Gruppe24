//
// Created by leonp on 28.04.2022.
//

#ifndef UNTITLED_KEYVALSTORE_H


#define UNTITLED_KEYVALSTORE_H

int put(char *key, char *value);

int get(char *key, char *res);

int del(char *key);

int initializeKeyValShM();

int dtKeyValShM();

#endif //UNTITLED_KEYVALSTORE_H
