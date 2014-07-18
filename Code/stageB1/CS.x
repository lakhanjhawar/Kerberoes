struct token2 
{
	unsigned char C[8];
	unsigned char S[8];
	unsigned Key[8];
};

struct tokenmsg2 
{
	unsigned char sermsg[9];
	unsigned char msg[255];
	int len;
}; 

struct clntreqtoken
{
	int len;
	unsigned char C[8];
	unsigned char msg1[1000];
	unsigned char msg2[1000];
	int enc_len;
};

struct Reply
{
	unsigned char C[8];
	unsigned char S[8];
	unsigned char msg[10000];
};

struct tokenrply2
{
	int len;
	unsigned char msg[5000];

};

struct tokenrqst2
{
	int len;
	unsigned char msg[10000];

};

program SP_PROG 
{
	version SP_VERS 
	{
		
		tokenrply2 STRFUNC (clntreqtoken) = 1;
	} = 1; 
} = 0x34222212;

