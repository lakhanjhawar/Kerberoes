#
BIN = KEYSERVER CLIENT1
GEN = CK_xdr.c CK_clnt.c CK_svc.c CK.h
LIB = -lnsl
CFLAGS = -I.. -O 
CC = gcc -DDEBUG

all:            $(GEN) $(BIN)

$(GEN):         CK.x
		rpcgen -N CK.x

KEYSERVER:         CK_svc.o CK_xdr.o keyserver.o
		$(CC) -o $@ keyserver.c CK_svc.o CK_xdr.o $(LIB)

CLIENT1:         CK_clnt.c CK_xdr.o client1.o
		$(CC) -o $@ client1.c CK_clnt.c CK_xdr.o $(LIB)

client1.o:       client1.c CK.h

keyserver.o:         keyserver.c CK.h

clean:
		rm -f $(GEN) *.o $(BIN)


