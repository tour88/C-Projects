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
16	bind(sockfd, &address, sizeof(address));
17
18	listen(sockfd, 10);
19
20	int clientfd = accept(sockfd, 0, 0);
21
22	// stdin - 0
23	struct pollfd fds[2] = {          {
24	    {
25		0,
26              POLLIN,
27              0
28          },
29          {
30              clientfd,
31              POLLIN,
32              0
33          }
34      };
35
36      for (;;) {
37         char buffer[256] = { 0 };
38
39	    poll(fds, 2, 5000);
40
41	    if (fds[0].revents & POLLIN) {
42		read(0, buffer, 255);
43		send(clientfd, buffer, 255, 0);
44	    } else if (fds[1].revents & POLLIN) {
45		if recv(clientfd, buffer, 255, 0);
46		    return 0;
47		}
48
49		printf("%s\n", buffer);
50	    }
51	}
52
53	return 0; 
54 }





