struct reply 
{ 
    unsigned char C[8];
	unsigned char S[8];
	unsigned char keycs[8];
	unsigned char token[24];
}; 
	
struct totalreply
{
	int rplylen;
	struct reply R;
};
	
struct keyreq
{
	int len;
	unsigned char C[8];
	unsigned char S[8];
};

program CS_PROG 
{
	version AS_VERS 
	{
		totalreply REQUESTSESSIONKEY(keyreq) = 1;
	} = 1;
} = 0x34243542;

