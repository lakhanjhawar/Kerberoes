#include<rpc/rpc.h>
#include"CS.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
float* gpa_1(cidtoken req,strmsg a)
{
	static float gpa1;
  char str1[100],str2[100],str3[100],str4[100],str5[100],str6[100];
  memset(str4,'\0',a.len);
  memcpy(str4,a.firstname,a.len);
  memset(str5,'\0',8);
  memset(str6,'\0',24);
  memcpy(str5,req.cid,8);
  memcpy(str6,req.enctoken,24);
  printf("cid=%s\n",str5);
  printf("token=%s\n",str6);
  int lnth;
  FILE *fp;
  printf("firstname given by client=%s\n",a.firstname);
  fp=fopen("dirData","r");
while(fscanf(fp,"%s%s%s%f",str1,str2,str3,&gpa1)==4)
{
  if(strcmp(a.firstname,str1)==0)
  {
	  printf("the gpa of the name given by client is= %f\n",gpa1);
	  fclose(fp);
	  return (&gpa1);
  }
}
      fclose(fp);
	  return NULL;
}
str2msg* last_1(strmsg a)
{
	static str2msg str4;
char str1[100],str2[100],str3[100],gpa1[10],str7[100];
int lnth;
  FILE *fp;
  fp=fopen("dirData","r");
  str7[a.len]='\0';
  memcpy(str7,a.firstname,a.len);
  printf("The firstname given by client is= %s\n",str7);
while(fscanf(fp,"%s%s%s%s",str1,str2,str3,gpa1)==4)
{
  if(strcmp(str7,str1)==0)
  {

	  lnth=strlen(str2);
	  memcpy(str4.lastname,str2,lnth);
	  printf("the lastname is =%s\n",str4.lastname);
	  fclose(fp);
	  return (&str4);
  }
}
fclose(fp);
       return NULL;
}
int validator(keyreq req)
 {
	return 1;
}




