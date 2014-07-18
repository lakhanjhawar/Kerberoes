#include <stdio.h>
#include <rpc/rpc.h>
#include "CK.h"
#include "CS.h"
#include <stdlib.h>
char * nullassigner(unsigned char * hosts);
char * nullassignertoken(unsigned char * hosts);

main(argc, argv)
	int argc;char *argv[];
    {
	CLIENT *cl,*ca;
	unsigned char userid[20];
	unsigned char keyid[20];
	char *hostName,*hostname1;
	struct str2msg *a;
	float *gp;
		struct strmsg arg1,arg3;
	struct keyreq request;
	struct totalreply *replyp, *reply;
	char strng[100],strng2[100];
	struct cidtoken req1;
	if (argc != 5)
    {
		printf("Provide arguments : USERID, KEYID, SERVERHOST1,SERVERHOST2 \n");
		exit(1);
	}
    else
    {

		strcpy(userid, argv[1]);
		memcpy(request.C,userid,8);
		strcpy(keyid,argv[2]);
		memcpy(request.S, keyid, 8);
		hostName = argv[3];
		hostname1=argv[4];
	}
	if ((cl = clnt_create(hostName, CS_PROG, AS_VERS, "udp")) == NULL)
     {
		clnt_pcreateerror(hostName);
		exit(2);
	}

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
	if ((ca = clnt_create(hostname1, SP_PROG, AS_VERS1, "udp")) == NULL)
	     {
			clnt_pcreateerror(hostname1);
			exit(2);
		}
    	printf("Enter the name for whom you want to know gpa\n");
		scanf("%s",strng);
		arg1.len = strlen(strng);
		memcpy(arg1.firstname,strng,arg1.len);
		memcpy(req1.cid1,userid,8);
		memcpy(req1.enctoken,reply->R.token,24);
		if ((gp= gpa_1(req1,arg1,ca)) == NULL)
	    {
			printf("The name doesn't exist start the server for service\n");
			clnt_perror(ca, "call failed");
			exit(3);
		}
		printf("gpa = %f\n",*gp );
		printf("\n Enter the input for getting lastname\n");
		scanf("%s",strng2);
		arg3.len = strlen(strng2);
		printf("the string length is %d\n",arg3.len);
		memcpy(arg3.firstname,strng2,arg3.len);
		if ((a= last_1(req1,arg3,ca)) == NULL)
		{
			printf("The name doesn't exist start the server for service\n");
			clnt_perror(ca, "call failed");
			exit(3);
		}
		printf("last name = %s\n",a->lastname);
		clnt_destroy(ca);
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
