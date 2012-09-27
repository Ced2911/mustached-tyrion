#pragma once

struct in_addr {
  unsigned int s_addr;               /* the IP address in network byte order    */
};

/* members are in network byte order */
struct sockaddr_in {
  byte sin_len;
  byte sin_family;
  unsigned short sin_port;
  struct in_addr sin_addr;
  char sin_zero[8];
};

struct sockaddr {
  byte sa_len;
  byte sa_family;
  char sa_data[14];
};
