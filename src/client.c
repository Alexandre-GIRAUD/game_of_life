#include <winsock2.h>
#include <stdio.h>
#include "grid.h"


int main(void)
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    SOCKET sock;
    SOCKADDR_IN sin;

    //socket technical information
    sin.sin_addr.s_addr    = inet_addr("127.0.0.1"); //public address here
    sin.sin_family        = AF_INET;
    sin.sin_port        = htons(4148);

    //socket creation and binding
    sock = socket(AF_INET,SOCK_STREAM,0);
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));

    //connexion
    connect(sock, (SOCKADDR *)&sin, sizeof(sin));

    printf("Connected\n");
    // Receive the 2D array from the server
    Cell **grid = create_grid();
    int i, j;
    for (i = 0; i < LENGTH; i++) {
        for (j = 0; j < WIDTH; j++) {
            int state;
            recv(sock, (void *)&state, sizeof(int), 0);
            grid[i][j].alive = ntohl(state);
        }
    }
    display_grid(grid);
    closesocket(sock);
    WSACleanup();
    WSACleanup();
    return 0;
}
