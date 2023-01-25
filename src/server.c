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
    sin.sin_addr.s_addr    = inet_addr("127.0.0.1"); //private address here
    sin.sin_family        = AF_INET;
    sin.sin_port        = htons(4148);

    //socket creation and binding
    sock = socket(AF_INET,SOCK_STREAM,0);
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));

    //connexion
    SOCKET csock;
    SOCKADDR_IN csin;
    listen(sock, 1);
    int val = 0;
    while(1)
    {
        int sizeof_csin = sizeof(csin);
        csock = accept(sock, (SOCKADDR *)&csin, &sizeof_csin);
        if(csock != INVALID_SOCKET)
        {
            Cell **grid = create_grid();
            for (int i = 0; i < LENGTH; i++) 
            {
                for (int j = 0; j < WIDTH; j++) 
                {
                    //We could use serialization to send a struct through a socket
                    int int_to_send = htons(grid[i][j].alive);
                    send(csock, (void *)&int_to_send, sizeof(int), 0);
                }
            }
            closesocket(csock);
        }
    }

    //close socket server
    printf("Close\n");
    closesocket(sock);
    WSACleanup();
    return 0;
}
