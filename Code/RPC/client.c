/* client.c */
#include        <stdio.h>
#include        <rpc/rpc.h> 
#include        "CS.h"
#include	<stdlib.h>

main(argc, argv)
int     argc;
char    *argv[];
{
	CLIENT          *cl;            /* RPC handle */
	char            *server;
	int 		*vowel_result;
	struct mySTR* substr_result;
	struct mySTR arg1; 
	struct myREC arg2;
	server = argv[1];
/********************************************/
	/* Set up connection with the server which provides services given in AS_PROG.
	Connection is called client "handle." */
	if ( (cl = clnt_create(server, AS_PROG, AS_VERS, "udp")) == NULL) {
	 clnt_pcreateerror(server);
	 exit(2);
	}

/********************************************/
        //prepare argument for a service request
        arg1.len = 10;
	memcpy (arg1.msg, "abcdefghij", 8);
	// call service passing the request
	if ( (vowel_result = vowels_1(arg1, cl)) == NULL) {
		clnt_perror(cl, "call failed");
		exit(3);
        }

	printf ("vowel count = %d\n", *vowel_result);
/********************************************/
        
	//prepare another service request
	arg1.len = 3;
	if ( (substr_result = substr_1(arg1, cl)) == NULL) {
		clnt_perror(cl, "call failed");
		exit(3);
        }

	printf ("substr = %s\n", substr_result -> msg);
/********************************************/

	//prepare yet another service request
	memcpy (arg1.msg, "abc", 3);
	arg1.len = 3; 
	memcpy(arg2.msg1, "Gopal", 5);
	memcpy(arg2.msg2, "Lakhani", 7);
	arg2.len = 12; 
	if ( (substr_result = concat_1(arg1, arg2, cl)) == NULL) {
		clnt_perror(cl, "call failed");
		exit(3);
        }

	printf ("substr = %s\n", substr_result -> msg);
/********************************************/
       
	//Add a new service here


/********************************************/
        clnt_destroy(cl);               /* done with the handle */
	exit(0);
}
