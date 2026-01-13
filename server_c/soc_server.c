#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5000
#define BUF_SIZE 128

int main() 
{
    int server_fd, client_fd;
    struct sockaddr_in addr;
    char buffer[BUF_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) 
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) 
    {
        perror("bind");
        exit(1);
    }

    if(listen(server_fd, 5) < 0) 
    {
        perror("listen");
        exit(1);
    }

    printf("Server C in ascolto sulla porta %d\n", PORT);

    while (1) 
    {
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) continue;

        memset(buffer, 0, BUF_SIZE);
        read(client_fd, buffer, BUF_SIZE - 1);

        char cmd[8];
        int id;

        if (sscanf(buffer, "%7s %d", cmd, &id) == 2) 
        {
            if (strcmp(cmd, "INC") == 0 || strcmp(cmd, "DEC") == 0) 
            {
                char reply[64];
                snprintf(reply, sizeof(reply), "OK %s %d\n", cmd, id);
                write(client_fd, reply, strlen(reply));
                printf("Ricevuto: %s", reply);
            } 
            else 
            {
                write(client_fd, "ERR comando_non_valido\n", 24);
            }
        } 
        
        else 
        {
            write(client_fd, "ERR formato\n", 12);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}