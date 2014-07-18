/* proc.c */
#include        <rpc/rpc.h>     /* standard RPC include file */
#include        "CS.h"
#include 	<stdio.h>
#include 	<stdlib.h>

int* vowels_1(mySTR S)
{
static int count;
/* count vowels - put some code  */
/* prepare reply */
count = 10;
return (&count);
}
mySTR* substr_1(mySTR S)
{
static mySTR reply;
/* compute substring - code */
FILE *flog;
flog = fopen("LOG", "a");
fprintf (flog, "server:substr input=%s\n", S.msg);
/* prepare reply */
reply.len = 5;
memcpy(reply.msg, "gopal", 5);
fclose(flog);
return (&reply);
}

mySTR* concat_1(mySTR S, myREC T)
{
static mySTR reply;
char R[200];
/* code for concatenation of two strings */
printf("server:concat input1=%s, input2=%s\n", S.msg, T.msg1);
/* prepare reply */
memcpy(R, S.msg, 3);
memcpy(R+3, T.msg1, 4);
memcpy(R+7, T.msg2, 5);
reply.len = 12;
memcpy(reply.msg, R, reply.len);
return (&reply);
}


