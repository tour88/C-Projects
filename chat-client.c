1 #include <sys/socket.h>
2 #include <stdio.h>
3 #include <arpa/inet.h>
4 #include <poll.h>
5 #include <unlistd.h>
6
7 int main() {
8	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
9
10	struct sockaddr_in address = {	
11	     AF_INET, 
12	     htons(9999), 	
13	     0
14	};
15
16	connect(sockfd, &address, sizeof(address));
17
18	// stdin - 0
19	struct pollfd fds[2] = {          {
20	    {
21		0,
22              POLLIN,
23              0
24          },
25          {
26              sockfd,
27              POLLIN,
28              0
29          }
30      };
31
32      for (;;) {
33         char buffer[256] = { 0 };
34
35	    poll(fds, 2, 5000);
36
37	    if (fds[0].revents & POLLIN) {
38		read(0, buffer, 255);
39		send(sockfd, buffer, 255, 0);
40	    } else if (fds[1].revents & POLLIN) {
41		if (recv(sockfd, buffer, 255, 0) == 0) {
42		    return 0;	
43		}
44
45		printf("%s\n", buffer);
46	    }
47	}
48
49	return 0; 
50


