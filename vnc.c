#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define EN0 0
#define CHALLENGESIZE 16

void
rfbEncryptBytes(unsigned char *bytes, char *passwd)
{
    unsigned char key[8];
    unsigned int i;

    /* key is simply password padded with nulls */

    for (i = 0; i < 8; i++) {
	if (i < strlen(passwd)) {
	    key[i] = passwd[i];
	} else {
	    key[i] = 0;
	}
    }

    rfbDesKey(key, EN0);

    for (i = 0; i < CHALLENGESIZE; i += 8) {
	rfbDes(bytes+i, bytes+i);
    }
}









int main(int argc, char **argv) {
    char* ip = "127.0.0.1"; int port = 5901;
    int sock = 0;
    struct sockaddr_in sockaddr;
    
	if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		printf("Failed to create socket");
	}
    
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(ip);
	sockaddr.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) < 0) {
		printf("Failed to connect with server");
	}
    
    char recvline[1024];
    char sendline[1024];
    
	int recvNum = -1;
	int sendNum = -1;
    
	memset(recvline, 0x00, sizeof(recvline));
	recvNum = recv(sock, recvline, sizeof(recvline) - 1, 0);
    printf("recvNum=%d recvline=%s\n", recvNum, recvline);
    
	memset(sendline, 0x00, sizeof(sendline));
    sprintf(sendline, "RFB 003.003\n");
	sendNum = send(sock, sendline, strlen(sendline), 0);
    printf("sendNum=%d sendline=%s\n", sendNum, sendline);
    
	memset(recvline, 0, sizeof(recvline));
	recvNum = recv(sock, recvline, sizeof(recvline) - 1, 0);
    printf("recvNum=%d recvline=%s\n", recvNum, recvline);
    printf("recvNum=%d recvline=%d %d %d %d\n", recvNum, recvline[0],recvline[1],recvline[2],recvline[3]);
    
    char challenge_and_response[CHALLENGESIZE];
    char *passwd = "543604";
    memset(challenge_and_response, 0x00, CHALLENGESIZE);
    memcpy(challenge_and_response, recvline+4, CHALLENGESIZE);
    printf("passwdlen=%d passwd=%s\n", 6, passwd);
    printf("passwdlen=%d radomB=%s\n", 16, challenge_and_response);
    rfbEncryptBytes(challenge_and_response, passwd);
    printf("passwdlen=%d radomA=%s\n", 16, challenge_and_response);
    
	memset(sendline, 0x00, sizeof(sendline));
    memcpy(sendline, challenge_and_response, CHALLENGESIZE);
	sendNum = send(sock, sendline, CHALLENGESIZE, 0);
    printf("sendNum=%d sendline=%s\n", sendNum, sendline);
    
	memset(recvline, 0, sizeof(recvline));
	recvNum = recv(sock, recvline, sizeof(recvline) - 1, 0);
    printf("recvNum=%d recvline=%s\n", recvNum, recvline);
    printf("recvNum=%d recvline=%d %d %d %d\n", recvNum, recvline[0],recvline[1],recvline[2],recvline[3]);
    
    
    memset(sendline, 0x00, sizeof(sendline));
    sprintf(sendline, "1");
	sendNum = send(sock, sendline, strlen(sendline), 0);
    printf("sendNum=%d sendline=%s\n", sendNum, sendline);
    
	memset(recvline, 0, sizeof(recvline));
	recvNum = recv(sock, recvline, sizeof(recvline) - 1, 0);
    printf("recvNum=%d recvline=%s\n", recvNum, recvline);
    printf("recvNum=%d recvline=%d %d %d %d %d %d\n", recvNum, recvline[0],recvline[1],recvline[2],recvline[3],recvline[4],recvline[5]);
    
    
    
    return 0;
}





