#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<rpc/rpc.h>
#include <md5.h>
#include "CK.h"
#include "CS.h"
#include "global.h"
#include "rsaref.h"
#include "ckey.h"

main(argc, argv)
	int argc;char *argv[];
	{
	CLIENT *cl,*C2;
	unsigned char C[10];
	unsigned char S[10],KeyServer_rep[20000],iv[8],ClientSerReq[10000],iv2[8],servicereply[10000],sername2[9];
	char *server = argv[1],*hostName,*hostname2;
	struct tokenrqst request;
	struct tokenrply reply;
	struct encryptedtoken* EncReply;
	int i6,KeyServer_replen;
	char Cintoken[9];
	struct clntreqtoken servreq1,servreq2;
	char strng[100];
	char strng2[100];
	struct tokenmsg2 arg1;
	unsigned int CSReqlen;
	int SVR;
	struct tokenrply2* encreply1;
	struct Reply decreply;
    char sertemp[10];
	struct tokenmsg2 argmsg;
	unsigned char ClientKey[8]=ckey;
	struct tokenrply2* tokrep;
	unsigned char vared1[10000];
	unsigned int vared;
	unsigned char ivared[8];
	unsigned char replyC2[100000];
	int replyVS;
	struct Reply repgan;
	unsigned char chkservname[9];
	char temper1[10];
	if (argc != 5)
    {
		printf("Arguements: USERID KEYID APPLICATION KEYSERVER \n");
		exit(1);
	}
	strcpy(C,argv[1]);
	printf("arg=%s\n",argv[1]);
	strcpy(S,argv[2]);
	hostName = argv[3];
	if ((cl = clnt_create(hostName, CS_PROG, CS_VERS, "udp")) == NULL)
	{
		clnt_pcreateerror(hostName);
		exit(2);
	}
	memcpy(request.C, C, 8);
	memcpy(request.S, S, 8);
	printf("c=%s\n",C);
	printf("s=%s\n",S);
	printf("reqc=%s\n",request.C);
	printf("reqs=%s\n",request.S);
	request.len=16;
	if ((EncReply = requestsessionkey_1(request,cl)) == NULL)
	{
		clnt_perror(cl,"call failed");
		exit(3);
	}
	memset(iv,'\0',8);
	R_DecryptPEMBlock(KeyServer_rep, &KeyServer_replen, EncReply->msg,EncReply->len,ClientKey,iv);
	memcpy((char *)&reply,KeyServer_rep,KeyServer_replen);
	Cintoken[8]='\0';
	memcpy(Cintoken,reply.C,8);
	if(strcmp(Cintoken,C)==0)
	{
	printf("\n Client ID in token and Client ID  sent match session server validated");
	}
	else
	{
	printf("\n Client ID in token and Client ID  sent do not match  Exiting \n ");
	exit(0);
	}
	memset(C,' ',8);
	memset(C,' ',8);
	memcpy(C,argv[1],8);
	memcpy(S,argv[2],8);
	hostname2 = argv[4];
	if ((C2 = clnt_create(hostname2, SP_PROG, SP_VERS, "udp")) == NULL)
	{
		clnt_pcreateerror(hostname2);
		exit(2);
	}
	printf("\n Enter the firstname for whom you want to get the GPA\n");
	scanf("%s",strng);
	printf("\n Enter the firstname for whom you want to get the Lastname\n");
	scanf("%s",strng2);
	memset(arg1.sermsg,' ',9);
	memset(arg1.msg,' ',255);
	memcpy(arg1.sermsg,"first_gpa",strlen("first_gpa"));
	arg1.sermsg[9]='\0';
	memcpy(arg1.msg,strng,strlen(strng));
	arg1.len=strlen(strng);
	memset(iv2, '\0', 8);
	CSReqlen = sizeof(arg1);
	memcpy(ClientSerReq, (unsigned char*) &arg1, CSReqlen);
	R_EncryptPEMBlock(servreq1.msg1,&servreq1.enc_len,ClientSerReq,CSReqlen,sesskey,iv2);
	memcpy(servreq1.C,C,8);
	memcpy (servreq1.msg2, reply.msg, reply.len);
	servreq1.len = reply.len;
	if ((encreply1 = strfunc_1(servreq1,C2)) == NULL)
	{
		clnt_perror(C2, "call failed");
		exit(3);
	}
	R_DecryptPEMBlock(servicereply, &SVR, encreply1->msg, encreply1->len,reply.Key,iv);
	memcpy((unsigned char*)&decreply,servicereply,SVR);
	memcpy(sername2,arg1.sermsg,9);
	sertemp[9] = '\0';
	memcpy(sertemp,sername2,strlen(sername2));
	if(strcmp(sertemp,"first_gpa") == 0)
	{
		char *servreply1 = decreply.msg;
		printf("The GPA of %s,is %s\n",strng,decreply.msg);
	}
	if(strcmp(sertemp,"last_name") == 0)
	{
		char *servreply2 = decreply.msg;
		printf("For %s, the last name is %s\n",strng2,servreply2);
	}
	memset(argmsg.sermsg,' ',9);
	memset(argmsg.msg,' ',255);
	memcpy(argmsg.sermsg,"last_name",strlen("last_name"));
	argmsg.sermsg[9]='\0';
	memcpy(argmsg.msg,strng2,strlen(strng2));
	argmsg.len = strlen(strng2);
	memset(ivared, '\0', 8);
	vared = sizeof(argmsg);
	memcpy(vared1, (unsigned char*) &argmsg, vared);
	R_EncryptPEMBlock(servreq2.msg1,&servreq2.enc_len,vared1,vared,sesskey,ivared);
	memcpy (servreq2.C, C, 8);
	memcpy (servreq2.msg2, reply.msg, reply.len);
	servreq2.len = reply.len;
	if ((tokrep = strfunc_1(servreq2, C2)) == NULL)
	{
		clnt_perror(C2, "Function Call to Services Server Failed");
		exit(3);
    }
	R_DecryptPEMBlock(replyC2, &replyVS, tokrep->msg,tokrep->len,reply.Key,ivared);
	memcpy((unsigned char*)&repgan, replyC2, replyVS);
	memcpy(chkservname,argmsg.sermsg,9);
	temper1[9] = '\0';
	memcpy(temper1,chkservname,9);
	if(strcmp(temper1,"first_gpa") == 0)
	{
		char *servreplyX = repgan.msg;
		printf("The gpa of  %s,is %s\n",strng,repgan.msg);
	}
	if(strcmp(temper1,"last_name") == 0)
	{
		char *servreplyY = repgan.msg;
		printf("For Mr. %s,lastname is %s\n",strng2,repgan.msg);
	}
	clnt_destroy(C2);
	exit(0);
}
