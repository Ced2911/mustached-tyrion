// net_wins.c

#include <unistd.h>
#include <errno.h>

//=============================================================================

void NetadrToSockadr (void *a, void *s)
{
	
}

void SockadrToNetadr (void *s, void *a)
{

}


int	NET_CompareAdr (int a, int b)
{
	return 0;
}

/*
===================
NET_CompareBaseAdr

Compares without the port
===================
*/
int	NET_CompareBaseAdr (int a, int b)
{
	return 0;
}

char	*NET_AdrToString (int a)
{
	return NULL;
}

char	*NET_BaseAdrToString (int a)
{
	return NULL;
}

/*
=============
NET_StringToAdr

localhost
idnewt
idnewt:28000
192.246.40.70
192.246.40.70:28000
=============
*/
int	NET_StringToSockaddr (char *s, void *sadr)
{
	return 0;
}

/*
=============
NET_StringToAdr

localhost
idnewt
idnewt:28000
192.246.40.70
192.246.40.70:28000
=============
*/
int	NET_StringToAdr (char *s, void *a)
{
	return 0;
}


int	NET_IsLocalAddress (int adr)
{
	return NET_CompareAdr (adr, 0);
}

/*
=============================================================================

LOOPBACK BUFFERS FOR LOCAL PLAYER

=============================================================================
*/

int	NET_GetLoopPacket (int sock, void *net_from, void *net_message)
{
	return 0;
}


void NET_SendLoopPacket (int sock, int length, void *data, int to)
{
	
}

//=============================================================================

int	NET_GetPacket (int sock, void *net_from, void *net_message)
{

	return 0;
}

//=============================================================================

void NET_SendPacket (int sock, int length, void *data, int to)
{
	
}


//=============================================================================




/*
====================
NET_OpenIP
====================
*/
void NET_OpenIP (void)
{
	
}

/*
====================
NET_OpenIPX
====================
*/
void NET_OpenIPX (void)
{
}


/*
====================
NET_Config

A single player game will only use the loopback code
====================
*/
void	NET_Config (int multiplayer)
{
	
}


//===================================================================


/*
====================
NET_Init
====================
*/
void NET_Init (void)
{
}


/*
====================
NET_Socket
====================
*/
int NET_Socket (char *net_interface, int port)
{
	return 0;
}


/*
====================
NET_Shutdown
====================
*/
void	NET_Shutdown (void)
{
	NET_Config (0);	// close sockets
}


/*
====================
NET_ErrorString
====================
*/
char *NET_ErrorString (void)
{
	int		code;

	code = errno;
	return strerror (code);
}

// sleeps msec or until net socket is ready
void NET_Sleep(int msec)
{

}

