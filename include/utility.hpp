#define TRUE 1
#define FALSE 0
#define EPOLL_SIZE 50
#define BUFFER_SIZE 1024
#define MESSAGE_SIZE 512
#define ACCOUNT 2

void error_handling(const char *error_message);
bool is_string_match(const char *buffer, const char *key);
void write_plain_text(int fd, const char *message);