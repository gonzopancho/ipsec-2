#include "sender.h"

int setkey_send()
{
	int sockfd;
	int clilen;
	int result;

	struct sockaddr_in serveraddr;

	clilen = sizeof(serveraddr);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0)
	{
		perror("Socket error : ");
		return -1;
	}

	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(IPSEC_ADDR);
	serveraddr.sin_port = htons(IPSEC_PORT);
	
	sendto(sockfd, (void *)&parameter, sizeof(parameter), 0, (struct sockaddr *)&serveraddr, clilen);
	recvfrom(sockfd, (void *)&result, sizeof(result), 0, NULL, NULL); 

	if(result < 0)
	{
		printf("Send error : need to resend\n");
		return -1;
	}
	close(sockfd);

	return 0;
}

