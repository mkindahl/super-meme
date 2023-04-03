#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024

void error(const char *str) {
  perror(str);
  exit(1);
}

int init_server(uint16_t port) {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0)
    error("socket");

  const int optval = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0)
    error("setsockopt");

  struct sockaddr_in serveraddr;
  bzero(&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(port);

  if (bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    error("bind");

  return fd;
}

size_t recv_packet(int fd, char *buf, size_t buflen,
                   struct sockaddr_in *caddr) {
  socklen_t clen = sizeof(*caddr);

  int bytes = recvfrom(fd, buf, buflen, 0, (struct sockaddr *)caddr, &clen);
  if (bytes < 0)
    error("recvfrom");
  return bytes;
}

int main(int argc, char **argv) {
  char *hostaddrp;
  int optval;
  char buf[BUFSIZE];
  struct sockaddr_in clientaddr;

  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  uint16_t portno = atoi(argv[1]);

  int sockfd = init_server(portno);

  while (1) {
    size_t received = recv_packet(sockfd, buf, sizeof(buf), &clientaddr);
    const char *hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("inet_ntoa\n");
    printf("server received datagram from %s\n", hostaddrp);
    printf("server received %lu/%lu bytes: %s\n", strlen(buf), received, buf);

    /*
     * sendto: echo the input back to the client
     */
    int n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&clientaddr,
                   sizeof(clientaddr));
    if (n < 0)
      error("sendto");
  }
}
