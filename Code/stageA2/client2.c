#include <stdio.h>
#include <rpc/rpc.h>
#include "CS.h"
#include <stdlib.h>

char * nullassigner(unsigned char * hosts);
#define KEY "12345678"
main(argc, argv)
	int argc;char *argv[];
    {
	CLIENT *cl;
	str2msg *a;
	float *gp;
	struct strmsg arg1;
	strmsg arg3;
	char userid[8];
	char keyid[8];
	char *hostName;
	char token[24];

	if (argc != 4)
     {
		printf("Provide arguments : USERID, KEYID, SERVER \n");
		exit(1);
	}
    else
    {
		memset(userid, '\0', 8);
		memset(keyid, '\0', 8);
		memcpy(userid, argv[1], 8);
		memcpy(keyid, argv[2], 8);
		hostName = argv[3];
	}
	if ((cl = clnt_create(hostName, SP_PROG, AS_VERS, "udp")) == NULL)
     {
		clnt_pcreateerror(hostName);
		exit(2);
	}
	struct totalreply *replyp, *reply;
	struct cidtoken request;
	memcpy(request.cid, userid, 8);
	memcpy(token,request.cid,8);
	memcpy(token+8,keyid,8);
	memcpy(token+16,KEY,8);
	memcpy(request.enctoken,token,24);
	char strng[100];
	printf("Enter the name for whom you want to know gpa\n");
	scanf("%s",strng);
	arg1.len = strlen(strng);
	memcpy(arg1.firstname,strng,arg1.len);
	if ((gp= gpa_1(request,arg1,cl)) == NULL)
    {
		printf("The name doesn't exist start the server for service\n");
		clnt_perror(cl, "call failed");
		exit(3);
	}
	printf("gpa = %f\n",*gp );
	char strng2[100];
	printf("\n Enter the input for getting lastname\n");
	scanf("%s",strng2);
	arg3.len = strlen(strng2);
	printf("len=%d\n",arg3.len);
	memcpy(arg3.firstname,strng2,arg3.len);
	if ((a= last_1(arg3,cl)) == NULL)
	{
		printf("The name doesn't exist start the server for service\n");
		clnt_perror(cl, "call failed");
		exit(3);
	}
	printf("last name = %s\n",a->lastname);
	clnt_destroy(cl);
	exit(0);
}
char * nullassigner(unsigned char * hosts)
 {
	char * K = malloc(sizeof(char) * 9);
	memcpy(K, hosts, 8);
	K[8] = '\0';
	return K;
}
