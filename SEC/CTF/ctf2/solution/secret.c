#include <stdio.h>      /* printf, sprintf */
#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */

char response[4096];
char buffer[1024];

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int open_socket(char *host, int port)
{
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
    error("ERROR opening socket\n");

  struct hostent *server = gethostbyname(host);
  if (server == NULL)
    error("ERROR no such host\n");

  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting\n");

  return sockfd;
}

int send_request(char *request, int socket)
{
  int total = strlen(request);
  int sent = 0;
  int bytes;

  do
  {
    bytes = write(socket, request + sent, total - sent);

    if (bytes < 0)
    {
      error("ERROR writing message to socket\n");
    }

    if (bytes == 0)
    {
      break;
    }

    sent += bytes;

  } while (sent < total);

  return total;
}

int receive_response(int socket)
{
  memset(response, 0, sizeof(response));
  int total = sizeof(response) - 1;
  int received = 0;
  int bytes;

  do
  {
    bytes = read(socket, response + received, total - received);

    if (bytes < 0)
    {
      error("ERROR reading response from socket\n");
    }

    if (bytes == 0)
    {
      break;
    }

    received += bytes;

  } while (received < total);

  if (received == total)
  {
    error("ERROR storing complete response from socket\n");
  }

  return received;
}

char *build_request(char *host, int port, char *path)
{
  int message_size = 0;
  message_size += strlen("GET %s%s%s HTTP/1.0\r\n");
  message_size += strlen(path);
  message_size += strlen("\r\n");

  char *message = malloc(message_size);
  sprintf(message, "GET %s HTTP/1.0\r\n", path);
  strcat(message, "\r\n");

  return message;
}

int main(int argc, char *argv[])
{
  int port = 8000;
  char *path = "/";
  char *host = "auth";

  char *message = build_request(host, port, path);
  int socket = open_socket(host, port);

  int total = send_request(message, socket);
  int received = receive_response(socket);

  close(socket);
  free(message);

  char *substring = "\r\n\r\n";
  char *body = strstr(response, substring);

  if (body == NULL)
  {
    error("ERROR reading request body\n");
  }
  body += strlen(substring);

  if (!strncmp(body, "true", 4))
  {
    FILE *file = fopen("/secret/flag.txt", "r+");
    if (file == NULL)
    {
      error("ERROR reading 'flag.txt' file\n");
    }

    fgets(buffer, sizeof(buffer), file);
    printf("%s\n", buffer);
    fclose(file);
  }
  else
  {
    printf("Unauthorized!\n");
  }

  return 0;
}
