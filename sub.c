//
// Created by leonp on 28.04.2022.
//
#include "sub.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "keyValStore.h"

int cleanString(char *string1) {
    int i = 0;
    char *newString;
    if(string1 != NULL) {
        while (string1[i] != '\r' && string1[i] != '\n' && string1[i] != '\0') {
            newString[i] = string1[i];
            i++;
        }
        newString[i] = '\0';

        strcpy(string1, newString);
    }
    return 0;
}


int executeCommand(const char *commandAndInput, int socket) {
    char get1[3] = "GET";
    char put1[3] = "PUT";
    char del1[3] = "DEL";
    char quit[4] = "QUIT";

    char *command;
    char *key;
    char *value;
    char *input;

    input = malloc(150);

    int i = 0;

    if(commandAndInput != NULL) {
        while (commandAndInput[i] != '\r' && commandAndInput[i] != '\n' && commandAndInput[i] != '\0') {
            input[i] = commandAndInput[i];
            i++;
        }
        input[i] = '\0';
    }


    command = strtok(input, "\r\n ");
    key = strtok(NULL, "\r\n ");
    value = strtok(NULL, "\r\n ");


    if (strncmp(command, get1, 3) == 0) {
        value = malloc(100);
        printf("%s\n", key);
        int success = get(key, value);
        printf("%s\n", value);
        if(success == 0) {
            strcat(value, "\n");
            write(socket, value, strlen(value));
        } else write(socket, "Key not found.\n", strlen("Key not found.\n"));
        free(value);
    }
    else if(strncmp(command, put1, 3) == 0) {
        printf("%s\n", key);
        printf("%s\n", value);
        put(key, value);
        write(socket, "Inserted\n", strlen("Inserted\n"));
    }
    else if(strncmp(command, del1, 3) == 0) {
        int success = del(key);
        if(success == 0) write(socket, "Deleted\n", strlen("Deleted\n"));
        if(success == -1) write(socket, "Key not found.\n", strlen("Key not found.\n"));
    }
    else if(strncmp(command, quit, 4) == 0) {
        return 1;
    }
    else {
        char *noValidCommand = "No vaild command.\n";
        write(socket, noValidCommand, strlen(noValidCommand));
    }
    free(input);
    return 0;
}


