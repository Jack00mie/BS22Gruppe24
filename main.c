
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include "sub.h"
#include <unistd.h>
#include <arpa/inet.h>
#include "keyValStore.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSIZE 1024 // Größe des Buffers
#define TRUE 1
#define ENDLOSSCHLEIFE 1
#define PORT 5678



int main() {
    int rfd; // Rendevouz-Descriptor
    int cfd; // Verbindungs-Descriptor

    int pid; // ProzessID


    struct sockaddr_in client; // Socketadresse eines Clients
    socklen_t client_len; // Länge der Client-Daten
    char in[BUFSIZE]; // Daten vom Client an den Server
    int bytes_read = 1; // Anzahl der Bytes, die der Client geschickt hat


    // Socket erstellen
    rfd = socket(AF_INET, SOCK_STREAM, 0);
    if (rfd < 0 ){
        fprintf(stderr, "socket konnte nicht erstellt werden\n");
        exit(-1);
    }


    // Socket Optionen setzen für schnelles wiederholtes Binden der Adresse
    int option = 1;
    setsockopt(rfd, SOL_SOCKET, SO_REUSEADDR, (const void *) &option, sizeof(int));


    // Socket binden
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    int brt = bind(rfd, (struct sockaddr *) &server, sizeof(server));
    if (brt < 0 ){
        fprintf(stderr, "socket konnte nicht gebunden werden\n");
        exit(-1);
    }

    // Socket lauschen lassen
    int lrt = listen(rfd, 5);
    if (lrt < 0 ){
        fprintf(stderr, "socket konnte nicht listen gesetzt werden\n");
        exit(-1);
    }

    /**
    int id;

    struct KeyVal * keyVal;

    id = shmget(IPC_PRIVATE, sizeof(KeyVal) * 500, IPC_CREAT|0777); // 0600 // 0666
    printf("%d\n", id);
    keyVal= (struct KeyVal *) shmat(id, 0, 0);

    setKeyVal(keyVal);
    */
    initializeKeyValSM();
    int clientsConnected = 0;
    int quit = 0;
    while(ENDLOSSCHLEIFE) {
        // Neuer Verbindungs-Descriptor
        cfd = accept(rfd, (struct sockaddr *)&client, &client_len);

        if(cfd < 0) {
            exit(-1);
        }

        printf("Neue Verbindung von IP Adresse: %s : %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        printf("Verbundene Clients: %d\n\n", ++clientsConnected);

        if((pid = fork()) == 0) { // Neuer Child-Prozess

            close(rfd);

            while(quit == 0) {
                read(cfd, in, BUFSIZE);
                quit = executeCommand(in, cfd);
            }
            close(cfd);
            exit(0);
        }

        close(cfd);
    }

    return 0;
}




