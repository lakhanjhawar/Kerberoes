#include<rpc/rpc.h>
#include"CS.h"
#include"CK.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include <string.h>
#include "skey.h"
int SP_Validator(char *Cmsg, char *CTmsg);
char* gpa_1(char *);
char* last_1(char*);
tokenrply2* strfunc_1(clntreqtoken tokened)
{
	static struct tokenrply2 reply;
	unsigned char tokenstream[100000];
	int tk;
	unsigned char C[8];
	unsigned char S[8];
	unsigned char CSK[8];
	int i=0;
	unsigned char iv[8];
	memset(iv, '\0', 8);
	unsigned char ServerKey[8] = skey;
	R_DecryptPEMBlock(tokenstream, &tk, tokened.msg2,tokened.len,skey,iv);
	struct token TokenTX;
	printf("\n Application Server Recieved a Request");
	memcpy((unsigned char*)&TokenTX, tokenstream, tk);
	for(i=0;i<8;i++)
	{
		C[i] = TokenTX.C[i];
		S[i] = TokenTX.S[i];
		CSK[i] = TokenTX.Key[i];
	}
	char cl1[9],cl2[9],cl3[9];
	cl1[8]='\0'; cl2[8]='\0'; cl2[8]='\0';
	memcpy(cl1,tokened.C,8);
	memcpy(cl2,C,8);
	memcpy(cl3,CSK,8);
	if(SP_Validator(cl1,cl2)==0)
	{
		printf("\n Client IDs and the one in token dont match");
		memcpy(reply.msg,"Client ID validation failed",strlen("Client ID validation failed"));
		reply.len=-1;
		return(&reply);
	}
	else
	{
	printf("\n Client is verified");
	}
	unsigned char ServStream[100000];
	unsigned int ServStreamSize;
	R_DecryptPEMBlock(ServStream, &ServStreamSize, tokened.msg1,tokened.enc_len,sesskey,iv);
	char *repmsg = NULL;
	struct tokenmsg2 srvreq;
	memcpy((unsigned char*)&srvreq, ServStream, ServStreamSize);
	char Srvreq[9],str[100],str2[100];
	for(i = 0; i < 9;i++)
	{
		Srvreq[i]=srvreq.sermsg[i];
	}
	if(strcmp(Srvreq,"first_gpa") == 0)
	{
		memset(str,'\0',srvreq.len);
		memcpy(str,srvreq.msg,srvreq.len);
		repmsg = gpa_1(str);
	}
	else if(strcmp(Srvreq,"last_name") == 0)
	{
		memset(str2,'\0',srvreq.len);
		memcpy(str2,srvreq.msg,srvreq.len);
		repmsg = last_1(str2);
	}
	if(repmsg != NULL)
	{
		struct Reply replyblk;
		memcpy(replyblk.C,C,8);
		memcpy(replyblk.S,S,8);
		memcpy(replyblk.msg,repmsg,strlen(repmsg) + 1);
		unsigned char msgret[20000];
		unsigned int retsize;
		retsize = sizeof(replyblk);
		memcpy(msgret, (unsigned char*) &replyblk, retsize);
		char temp8[retsize];
		temp8[retsize] = '\0';
		memcpy(temp8,msgret,retsize);
		printf("\n");
		R_EncryptPEMBlock(reply.msg,&reply.len,temp8,strlen(temp8),CSK,iv);
		return(&reply);
	}
	else
	{
		printf("Unknown Service requested \n");
		reply.len = -1;
		return(&reply);
	}
}
char* gpa_1(char *a)
{
	static char gpa1[10];
  char str1[100],str2[100],str3[100];
  int lnth;
  FILE *fp;
  fp=fopen("dirData","r");
  printf("firstname=%s\n",a);
while(fscanf(fp,"%s%s%s%s",str1,str2,str3,gpa1)==4)
{
	printf("string=%s\n",str1);
  if(strcmp(a,str1)==0)
  {
	  printf("the gpa of the name given by client is= %s\n",gpa1);
	  fclose(fp);
	  return (gpa1);
  }
}
      fclose(fp);
	  return NULL;
}
char* last_1(char *a)
{
	static char str2[20];
char str1[100],str3[100],gpa1[10];
int lnth;
  FILE *fp;
  fp=fopen("dirData","r");
while(fscanf(fp,"%s%s%s%s",str1,str2,str3,gpa1)==4)
{
  if(strcmp(a,str1)==0)
  {

	  lnth=strlen(str2);
	  printf("the lastname is =%s\n",str2);
	  fclose(fp);
	  return (str2);
  }
}
fclose(fp);
       return NULL;
}
int SP_Validator(char *Cmsg,char *CTmsg)
{
	if(strcmp(Cmsg,CTmsg) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
