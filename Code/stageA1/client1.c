#include <stdio.h>
#include <rpc/rpc.h>
#include "CK.h"
#include <stdlib.h>

char * nullassigner(unsigned char * hosts);
char * nullassignertoken(unsigned char * hosts);

main(argc, argv)
	int argc;char *argv[];
    {
	CLIENT *cl;
	unsigned char userid[20];
	unsigned char keyid[20];
	char *hostName;
	struct keyreq request;
	if (argc != 4)
    {
		printf("Provide arguments : USERID, KEYID, SERVERHOST \n");
		exit(1);
	}
    else
    {

		strcpy(userid, argv[1]);
		memcpy(request.C,userid,8);
		strcpy(keyid,argv[2]);
		memcpy(request.S, keyid, 8);
		hostName = argv[3];
	}
	if ((cl = clnt_create(hostName, CS_PROG, AS_VERS, "udp")) == NULL)
     {
		clnt_pcreateerror(hostName);
		exit(2);
	}
	struct totalreply *replyp,*reply;
	request.len = 16;

	if ((replyp = requestsessionkey_1(request, cl)) == NULL)
     {
		clnt_perror(cl, "call failed\n");
		exit(3);
	}
    else
    {
		reply = replyp;
		printf("reply recieved\nc = %s\nS = %s\nkcs = %s\n", nullassigner(reply->R.C),nullassigner(reply->R.S), nullassigner(reply->R.keycs));
		printf("The token is token= %s\n",nullassignertoken(reply->R.token));
		clnt_destroy(cl);
	}
}

char * nullassigner(unsigned char * hosts)
{
	char * K = malloc(sizeof(char) * 9);
	memcpy(K, hosts, 8);
	K[8] = '\0';
	return K;
}
char * nullassignertoken(unsigned char * hosts)
{
	char * K = malloc(sizeof(char) * 25);
	memcpy(K, hosts, 24);
	K[24] = '\0';
	return K;
}
