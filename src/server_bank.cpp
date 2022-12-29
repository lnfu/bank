#include <unistd.h>

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/utility.hpp"

using namespace std;

void show_accounts(int fd, int accounts[]) {
    char buffer[BUFFER_SIZE] = {0};

    for (int i = 0; i < ACCOUNT; i++) {
        char row[100] = {0};
        sprintf(row, "ACCOUNT%d: %d\n", i + 1, accounts[i]);
        strcat(buffer, row);
    }

    write_plain_text(fd, buffer);
}

void deposit(int fd, char *buffer, int accounts[]) {
    int account = -1;
    int money = -1;

    sscanf(buffer, "deposit ACCOUNT%d %d", &account, &money);
    if (money <= 0) {
        write_plain_text(fd, "Deposit a non-positive number into accounts.\n");
        return;
    }

    accounts[account - 1] += money;

    memset(buffer, 0, BUFFER_SIZE);

    sprintf(buffer, "Successfully deposits %d into ACCOUNT%d.\n", money, account);

    write_plain_text(fd, buffer);
}

void withdraw(int fd, char *buffer, int accounts[]) {
    int account = -1;
    int money = -1;

    sscanf(buffer, "withdraw ACCOUNT%d %d", &account, &money);
    if (money <= 0) {
        write_plain_text(fd, "Withdraw a non-positive number into accounts.\n");
        return;
    }

    if (accounts[account - 1] - money < 0) {
        write_plain_text(fd, "Withdraw excess money from accounts.\n");
        return;
    }

    accounts[account - 1] -= money;

    memset(buffer, 0, BUFFER_SIZE);

    sprintf(buffer, "Successfully withdraws %d into ACCOUNT%d.\n", money, account);

    write_plain_text(fd, buffer);
}