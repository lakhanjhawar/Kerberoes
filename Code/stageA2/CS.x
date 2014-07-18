struct cidtoken
{
unsigned char cid[8];
unsigned char enctoken[24];
};

struct strmsg 
{
	int len;
	unsigned char firstname[100];
}; 

struct str2msg
{
	unsigned char lastname[100];
	unsigned char fstname[100];
	int len;
}; 
struct keyreq
{
	int len;
	unsigned char C[8];
	unsigned char S[8];
};


program SP_PROG 
{
	version AS_VERS 
	{
        float GPA(cidtoken,strmsg) =1;
        str2msg LAST(strmsg)=2;   
         
	} = 1; /* version number */
} = 0x34247123;

