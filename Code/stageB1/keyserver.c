#include<rpc/rpc.h>
#include"CK.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include   "ckey.h"
#include   "skey.h"
int KP_Validator(tokenrqst Creq,int V);
void GenerateKey(unsigned char *Key);
void GenerateToken(tokenrply *replyp);
encryptedtoken* requestsessionkey_1(tokenrqst req)
 {
	printf("\n KeyServer Recieved Request ");
	struct tokenrply encreply;
	static encryptedtoken encfinalrep;
	if (KP_Validator(req,1) == 0)
	{
		encfinalrep.len=-1;
		printf("\n Client Id not found");
		memcpy(encfinalrep.msg,"C ID not found",strlen("C ID not found"));
		return(&encfinalrep);
	}
	if (KP_Validator(req,2) == 0)
	{
		encfinalrep.len=-1;
		printf("\n Server Id not found");
		memcpy(encfinalrep.msg,"S ID not found",strlen("S ID not found"));
		return(&encfinalrep);
	}
	memcpy(encreply.C,req.C,8);
	memcpy(encreply.S, req.S ,8);
	GenerateKey(encreply.Key);
	encreply.Key[8]='\0';
	GenerateToken(&encreply);
	struct tokenrply encreply2;
	memcpy(encreply2.C,req.C,8);
	encreply2.C[9]='\0';
	memcpy(encreply2.S, req.S ,8);
	encreply2.S[9]='\0';
	memcpy(encreply2.Key,encreply.Key,8);
	memcpy(encreply2.msg,(unsigned char*) &encreply.msg, strlen(encreply.msg));
	encreply2.len=strlen(encreply2.msg);
	unsigned char genenc[10000];
	int ii;
	ii = sizeof(encreply2);
	memcpy(genenc, (unsigned char*) &encreply2, sizeof(encreply2));
	unsigned char iv[8];
	memset(iv, '\0', 8);
	unsigned char ClientKey[8] = ckey;
	R_EncryptPEMBlock(encfinalrep.msg,&encfinalrep.len,genenc,ii,ClientKey,iv);
	printf("\n key server encrypted reply to client");
	return(&encfinalrep);
}

int KP_Validator(tokenrqst Creq, int V)
{
	char val[9];
	val[8]='\0';
	int valid=0;
	if(V == 1)
	{
		memcpy(val,Creq.C,8);
		printf("val=%s\n",val);
	}
	else if(V == 2)
	{
		memcpy(val,Creq.S,8);
	}
	FILE * fp;
	fp=fopen("DB.key","r");
	char FH[20];
	char FB[9];
	FB[8]='\0';
	int a;
	int b;
	int c;
	while(fscanf(fp,"%s",FH)!=NULL)
	{
		if(strcmp(val,FH)==0)
		{
			valid=1;
			break;
		}
	}
	fclose(fp);
	return(valid);
}

void GenerateKey(unsigned char *Key)
{
	char temp[8] = "12345678";
	FILE *fp, *popen();
	unsigned char text[128], randText[128];
	fp = popen("date; ps -e", "r");
	fread(text, 128, 1, fp);
	md5_calc(randText, text, 128);
	memcpy(temp, randText, 8);
	pclose(fp);
	temp[9]='\0';
	memcpy(Key,temp,8);
}
void GenerateToken(tokenrply *replyp)
{
	unsigned char Key[8] = "77777777";
	struct token TB, TB2Decrypted;
	memcpy(TB.C,replyp->C,8);
	TB.C[8]='\0';
	memcpy(TB.S,replyp->S,8);
	TB.S[8]= '\0';
	replyp->Key[8]='\0';
	printf("\n token generated with Servers private key");
	memcpy(TB.Key,replyp->Key,8);
	unsigned char stream[10000];
	unsigned int streamsize;
	int szize= sizeof(TB);
	memcpy(stream, (unsigned char*) &TB, sizeof(TB));
	unsigned char iv[8];
	memset(iv, '\0', 8);
	unsigned char serverkey[8] = skey;
	R_EncryptPEMBlock(replyp->msg,&replyp->len,stream,szize,skey,iv);
}

