#include <unistd.h>

#include <cstring>
#include <iostream>

using namespace std;

void error_handling(const char *error_message) {
    perror(error_message);
    exit(1);
}

bool is_string_match(const char *buffer, const char *key) { return (strncmp(buffer, key, strlen(key)) == 0); }


void write_plain_text(int fd, const char *message) { write(fd, message, strlen(message)); }