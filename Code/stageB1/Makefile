#For enc
BIN_ALL = KEYSERVER APPSERVER CLIENT
CORE = core
GEN_CK = CK_xdr.c CK_clnt.c CK_svc.c CK.h
GEN_CS = CS_xdr.c CS_clnt.c CS_svc.c CS.h
LIB = -lnsl -lmd5 rsaref.a
CFLAGS = -I.. -O 
CC = gcc -DDEBUG

all:            $(GEN_CK) $(GEN_CS) $(BIN_ALL)

$(GEN_CK):         CK.x
		rpcgen -N CK.x
		
$(GEN_CS): 		CS.x
		rpcgen -N CS.x

KEYSERVER:         CK_svc.o CK_xdr.o keyserver.o
		$(CC) -o $@ keyserver.c CK_svc.o CK_xdr.o $(LIB)
		
APPSERVER:			CS_svc.o CS_xdr.o appserver.o
			$(CC) -o $@ appserver.c CS_svc.o CS_xdr.o $(LIB)

CLIENT:         CK_clnt.c CK_xdr.o CS_clnt.c CS_xdr.o client.o
		$(CC) -o $@ client.c CK_clnt.c CK_xdr.o CS_clnt.c CS_xdr.o $(LIB)

client.o:       client.c CS.h CS.h

keyserver.o:			keyserver.c CK.h

SP_proc.o:         appserver.c CS.h

clean:
		rm -f $(GEN_CK) $(GEN_CS) *.o $(BIN_ALL) $(CORE)


