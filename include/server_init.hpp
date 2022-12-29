int init_tcp_socket(const char *port);
void add_socket_to_epoll(int socket_fd, int epoll_fd);
void close_request(int socket_fd, int epoll_fd);