#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "../include/utility.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int client_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) error_handling("socket()");

    struct sockaddr_in address;
    address.sin_family = AF_INET;

    if (argc == 3) {
        address.sin_addr.s_addr = inet_addr(argv[1]);
        address.sin_port = htons(atoi(argv[2]));
    } else {
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_port = htons(9999);
    }

    if (connect(client_socket, (struct sockaddr *)&address, sizeof(address)) == -1) error_handling("connect()");

    // printf("TCP connection has been created\n");
    printf("******************************\n");
    printf("* Welcome to the TCP server. *\n");
    printf("******************************\n");


    fd_set reads, temps;
    FD_ZERO(&reads);
    FD_SET(0, &reads);
    FD_SET(client_socket, &reads);

    while (true) {
        putchar('%');
        putchar(' ');
        fflush(stdout);


        temps = reads;
        int select_result = select(client_socket + 1, &temps, 0, 0, 0);
        if (select_result == -1) error_handling("select()");
        if (select_result == 0) continue;

        if (FD_ISSET(client_socket, &temps)) {
            char buffer[BUFFER_SIZE] = {0};
            int message_length = read(client_socket, buffer, BUFFER_SIZE);
            buffer[message_length] = 0;

            printf("\r%s\n", buffer);
        }

        if (FD_ISSET(0, &temps)) {
            char buffer[BUFFER_SIZE] = {0};
            int message_length = read(0, buffer, BUFFER_SIZE);
            buffer[message_length] = 0;

            if (message_length == 0) continue;

            if (is_string_match(buffer, "exit") or is_string_match(buffer, "Exit")) break;

            write(client_socket, buffer, message_length);
        }
    }

    return 0;
}