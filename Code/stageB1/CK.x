struct token 
{
	unsigned char C[8];
	unsigned char S[8];
	unsigned char Key[8];
};

struct tokenmsg 
{
	unsigned char C[8];
	unsigned char S[8];
	unsigned Key[8];
	struct token Tmsg;
}; 

struct clientreq
{
	unsigned char C[8];
	unsigned char S[8];
};

struct tokenrqst
{
	int len;
	unsigned char C[8];
	unsigned char S[8];
};

struct tokenrply
{
	unsigned char C[8];
	unsigned char S[8];
	unsigned char Key[8];
	unsigned char msg[1000];
	unsigned int len;
};
struct encryptedtoken
{
	int len;
	unsigned char msg[10000];
};
	


program CS_PROG 
{
	version CS_VERS 
	{
		encryptedtoken REQUESTSESSIONKEY(tokenrqst) = 1;
	} = 1; 
} = 0x34242488;

