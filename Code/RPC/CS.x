/* CS.x */

struct mySTR {
	int len;
	unsigned char msg[100];
	}; /* ; required */

struct myREC {
	int len;
	unsigned char msg1[100];
	unsigned char msg2[100];
	}; /* ; required */

program AS_PROG {
	version AS_VERS {
		int VOWELS (mySTR) = 1;
		mySTR SUBSTR (mySTR) = 2;
		mySTR CONCAT (mySTR, myREC) = 3;
		} = 1; /* version number */
	} = 1280000000; /*0x34243542;  program number should be large & unique */

