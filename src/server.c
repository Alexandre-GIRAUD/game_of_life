#include <winsock2.h>
#include <stdio.h>
#include <pthread.h>
#include "grid.h"

void *handle_client(void *arg)
{
    int socket_client = *(int *)arg;
    char msg[] = "Server : How many steps do you want to receive\n";

    if (send(socket_client, msg, strlen(msg) + 1, 0) == SOCKET_ERROR)
    {
        // Error handling
        printf("Error sending message: %d\n", WSAGetLastError());
        closesocket(socket_client);
        free(arg);
        pthread_exit(NULL);
    }

    int steps;
    if (recv(socket_client, (void *)&steps, sizeof(int), 0) == SOCKET_ERROR)
    {
        printf("Error receiving steps: %d\n", WSAGetLastError());
        closesocket(socket_client);
        free(arg);
        pthread_exit(NULL);
    }

    printf("steps well received : %d\n", steps);
    Cell **grid = create_grid();
    for (int s = 0; s < steps; s++)
    {
        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                // We could use serialization to send a struct through a socket
                int int_to_send = htons(grid[i][j].alive);
                if (send(socket_client, (void *)&int_to_send, sizeof(int), 0) == SOCKET_ERROR)
                {
                    fprintf(stderr, "Error sending data to client: %d\n", WSAGetLastError());
                    closesocket(socket_client);
                    free(arg);
                    pthread_exit(NULL);
                }
            }
        }
        update_gridv2(grid);
    }

    closesocket(socket_client);

    // free grid space
    for (int i = 0; i < LENGTH; i++)
        free(grid[i]);
    free(grid);

    free(arg);
    pthread_exit(NULL);
}

int main(void)
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    SOCKET sock;
    SOCKADDR_IN sin;

    // socket technical information
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // private address here
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4148);

    // socket creation and binding
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));

    // connexion
    SOCKET csock;
    SOCKADDR_IN csin;
    listen(sock, 3); //define the max size queue of clients

    // Thread for multiple clients
    pthread_t clientThread;

    while (1)
    {
        int sizeof_csin = sizeof(csin);
        csock = accept(sock, (SOCKADDR *)&csin, &sizeof_csin);
        if (csock != INVALID_SOCKET)
        {
            int *arg = malloc(sizeof(int));
            *arg = csock;
            pthread_create(&clientThread, NULL, handle_client, arg);
        }
    }

    // close socket server
    printf("Close\n");
    closesocket(sock);
    WSACleanup();
    return 0;
}
