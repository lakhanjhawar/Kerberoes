struct cidtoken
{
unsigned char cid1[8];
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

program SP_PROG 
{
	version AS_VERS1 
	{
        float GPA(cidtoken,strmsg) =1;
        str2msg LAST(cidtoken,strmsg)=2;   
         
	} = 1; /* version number */
} = 0x34242173;

