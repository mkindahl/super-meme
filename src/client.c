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

int main(int argc, char **argv) {
  int sockfd, portno, n;
  struct sockaddr_in serveraddr;
  struct hostent *server;
  char *hostname;

  /* check command line arguments */
  if (argc != 4) {
    fprintf(stderr, "usage: %s <hostname> <port> <message>\n", argv[0]);
    exit(0);
  }
  hostname = argv[1];
  portno = atoi(argv[2]);

  /* socket: create the socket */
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("socket");
    exit(1);
  }

  /* gethostbyname: get the server's DNS entry */
  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr, "ERROR, no such host as %s\n", hostname);
    exit(1);
  }

  /* build the server's Internet address */
  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr,
        server->h_length);
  serveraddr.sin_port = htons(portno);

  /* send the message to the server */
  {
    socklen_t serverlen = sizeof(serveraddr);
    int n = sendto(sockfd, argv[3], strlen(argv[3]), 0,
                   (struct sockaddr *)&serveraddr, serverlen);
    if (n < 0) {
      perror("sendto");
      exit(1);
    }
  }

  /* print the server's reply */
  {
    char mbuf[BUFSIZE];
    socklen_t serverlen = sizeof(serveraddr);
    int n = recvfrom(sockfd, mbuf, sizeof(mbuf), 0,
                     (struct sockaddr *)&serveraddr, &serverlen);
    if (n < 0) {
      perror("recvfrom");
      exit(1);
    }

    const char *addr = inet_ntoa(serveraddr.sin_addr);

    if (addr)
      printf("Message received from address %s: %s\n", addr, mbuf);
    else
      printf("Message received from unknown address: %s\n", mbuf);
  }
  return 0;
}
