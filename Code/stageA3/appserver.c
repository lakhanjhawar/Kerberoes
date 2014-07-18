#include<rpc/rpc.h>
#include"CS.h"
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
float* gpa_1(cidtoken app1,strmsg a)
{
		static float gpa1;
	  char str1[100],str2[100],str3[100],str4[100];
	  int lnth;
	  FILE *fp;
	  memset(str4,'\0',a.len);
	  memcpy(str4,a.firstname,a.len);
	  fp=fopen("dirData","r");
	while(fscanf(fp,"%s%s%s%f",str1,str2,str3,&gpa1)==4)
	{
	  if(strcmp(str4,str1)==0)
	  {
		  printf("the gpa of the name given by client is= %f\n",gpa1);
		  fclose(fp);
		  return (&gpa1);
	  }
	}
	      fclose(fp);
		  return NULL;
	}
str2msg* last_1(cidtoken app2,strmsg a)
{
	static str2msg str4;
	char str1[100],str2[100],str3[100],gpa1[10],str5[100];
	int lnth,lnth1;
	  FILE *fp;
	  memset(str5,'\0',a.len);
	  memcpy(str5,a.firstname,a.len);
	  printf("The firstname given by client is= %s\n",str5);
	  fp=fopen("dirData","r");
	while(fscanf(fp,"%s%s%s%s",str1,str2,str3,gpa1)==4)
	{
	  if(strcmp(str5,str1)==0)
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
int validator(cidtoken req)
 {
	return 1;
}




