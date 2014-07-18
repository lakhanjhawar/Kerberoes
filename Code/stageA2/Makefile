#
BIN= SERVER CLIENT2
GEN = CS_xdr.c CS_clnt.c CS_svc.c CS.h
LIB = -lnsl
CFLAGS = -I.. -O 
CC = gcc -DDEBUG

all:            $(GEN) $(BIN)

$(GEN):         CS.x
		rpcgen -N CS.x

SERVER:         CS_svc.o CS_xdr.o appserver.o
		$(CC) -o $@ appserver.c CS_svc.o CS_xdr.o $(LIB)

CLIENT2:         CS_clnt.c CS_xdr.o client2.o
		$(CC) -o $@ client2.c CS_clnt.c CS_xdr.o $(LIB)

client2.o:       CS.c CS.h

appserver.o:         appserver.c CS.h

clean:
		rm -f $(GEN) *.o $(BIN)


