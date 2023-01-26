#include <winsock2.h>
#include <stdio.h>
#include "grid.h"

int main(void)
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2, 0), &WSAData);
    SOCKET sock;
    SOCKADDR_IN sin;

    // socket technical information
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); // public address here
    sin.sin_family = AF_INET;
    sin.sin_port = htons(4148);

    // socket creation and binding
    sock = socket(AF_INET, SOCK_STREAM, 0);
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));

    // connexion
    connect(sock, (SOCKADDR *)&sin, sizeof(sin));

    printf("Connected\n");

    // send how many evolution steps you want to see
    int steps = 0;
    char msg[48];
    int result = recv(sock, msg, 48, 0);
    if (result > 0)
    {
        printf("%s", msg);
    }
    else
    {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    scanf("%d", &steps);

    result = send(sock, (void *)&steps, sizeof(int), 0);
    if (result == SOCKET_ERROR)
    {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Receive the 2D array from the server
    Cell **grid = create_grid();
    int i, j;
    for (int s = 0; s < steps; s++)
    {
        for (i = 0; i < LENGTH; i++)
        {
            for (j = 0; j < WIDTH; j++)
            {
                int state;
                if (recv(sock, (void *)&state, sizeof(int), 0) == SOCKET_ERROR)
                {
                    printf("Error receiving steps: %d\n", WSAGetLastError());
                    closesocket(sock);
                    return 1;
                }
                grid[i][j].alive = ntohl(state);
            }
        }
        display_grid(grid);
    }

    // Free grid
    for (int i = 0; i < LENGTH; i++)
        free(grid[i]);
    free(grid);

    closesocket(sock);
    WSACleanup();
    WSACleanup();
    return 0;
}
