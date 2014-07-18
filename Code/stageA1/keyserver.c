#include<rpc/rpc.h> 
#include"CK.h"
#include<stdio.h>
#include<stdlib.h>
int validate(keyreq req);
void keygen(unsigned char *KCS);
void tokengen(totalreply *replyp);
void genrply(totalreply *replyp);
totalreply * requestsessionkey_1(keyreq req)
 {
	char cid[20],sid[20];
	memset(cid,NULL,8);
	memset(sid,NULL,8);
	memcpy(cid,req.C,8);
	memcpy(sid,req.S,8);
	cid[8]='\0';
	sid[8]='\0';
	printf("Recieved request\n");
	printf("The cid=%s\n",cid);
	printf("The sid=%s\n",sid);
	struct totalreply * replyp = malloc(sizeof(struct totalreply));
	memset(replyp->R.C,' ',8);
	memset(replyp->R.S,' ',8);
	memcpy(replyp->R.C,req.C,8);
	memcpy(replyp->R.S,req.S,8);
	if (validate(req) == 1) 
    {
		keygen(replyp->R.keycs);
		tokengen(replyp);
		genrply(replyp);
	} 
    else
     {
		replyp->rplylen = -1;
	}	
	return replyp;
}

int validate(keyreq req)
 {
	return 1; 
}

void keygen(unsigned char *KCS) 
{
	char temp[8] = "12345678";
	printf("\n key= %s",temp);
	memcpy(KCS, temp, 8);
}

void tokengen(totalreply *replyp)
 {
     char tk[24];
	memcpy(tk, replyp->R.C,8);
	memcpy(tk+8, replyp->R.S,8);
	memcpy(tk+16,replyp->R.keycs,8);
	printf("the token is TOKEN=%s\n",tk);
	memcpy(replyp->R.token,tk,24);
}
void genrply(totalreply *replyp)
 {
	replyp->rplylen = sizeof(reply);
}
