/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "CK.h"

bool_t
xdr_reply(xdrs, objp)
	register XDR *xdrs;
	reply *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	int i;
	if (!xdr_vector(xdrs, (char *)objp->C, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->S, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->keycs, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->token, 24,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_totalreply(xdrs, objp)
	register XDR *xdrs;
	totalreply *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	if (!xdr_int(xdrs, &objp->rplylen))
		return (FALSE);
	if (!xdr_reply(xdrs, &objp->R))
		return (FALSE);
	return (TRUE);
}

bool_t
xdr_keyreq(xdrs, objp)
	register XDR *xdrs;
	keyreq *objp;
{

#if defined(_LP64) || defined(_KERNEL)
	register int *buf;
#else
	register long *buf;
#endif

	int i;
	if (!xdr_int(xdrs, &objp->len))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->C, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	if (!xdr_vector(xdrs, (char *)objp->S, 8,
		sizeof (u_char), (xdrproc_t) xdr_u_char))
		return (FALSE);
	return (TRUE);
}