// xllsocket_option.cpp - get/setsockopt wrapper
#include "xllsocket.h"
#include "Af_irda.h"

using namespace xll;

//XLL_ENUM(SOL_APPLETALK, SOL_APPLETALK, CATEGORY, "Socket options applicable at the AppleTalk level. For more information, see the SOL_APPLETALK Socket Options. ");
XLL_ENUM(SOL_IRLMP, SOL_IRLMP, CATEGORY, "Socket options applicable at the InfraRed Link Management Protocol level. For more information, see the SOL_IRLMP Socket Options. ");
XLL_ENUM(SOL_SOCKET, SOL_SOCKET, CATEGORY, "Socket options applicable at the socket level. For more information, see the SOL_SOCKET Socket ");

XLL_ENUM(SO_ACCEPTCONN, SO_ACCEPTCONN, CATEGORY, "get [DWORD (boolean)] Returns whether a socket is in listening mode. This option is only Valid for connection-oriented protocols. ");
XLL_ENUM(SO_BROADCAST, SO_BROADCAST, CATEGORY, "get/set [DWORD (boolean)] Configure a socket for sending broadcast data. This option is only Valid for protocols that support broadcasting (IPX and UDP, for example). ");
//XLL_ENUM(SO_BSP_STATE, SO_BSP_STATE, CATEGORY, "get [CSADDR_INFO] Returns the local address, local port, remote address, remote port, socket type, and protocol used by a socket. See the SO_BSP_STATE reference for more information. ");
XLL_ENUM(SO_CONDITIONAL_ACCEPT, SO_CONDITIONAL_ACCEPT, CATEGORY, "get/set [DWORD (boolean)] Indicates if incoming connections are to be accepted or rejected by the application, not by the protocol stack. See the SO_CONDITIONAL_ACCEPT reference for more information. ");
XLL_ENUM(SO_CONNDATA, SO_CONNDATA, CATEGORY, "get/set [char []] Additional data, not in the normal network data stream, that is sent with network requests to establish a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_CONNDATALEN, SO_CONNDATALEN, CATEGORY, "/set [ULONG] The length, in bytes, of additional data, not in the normal network data stream, that is sent with network requests to establish a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_CONNECT_TIME, SO_CONNECT_TIME, CATEGORY, "get [ULONG] Returns the number of seconds a socket has been connected. This option is only valid for connection-oriented protocols. ");
XLL_ENUM(SO_CONNOPT, SO_CONNOPT, CATEGORY, "get/set [char []] Additional connect option data, not in the normal network data stream, that is sent with network requests to establish a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_CONNOPTLEN, SO_CONNOPTLEN, CATEGORY, "/set [ULONG] The length, in bytes, of connect option data, not in the normal network data stream, that is sent with network requests to establish a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_DISCDATA, SO_DISCDATA, CATEGORY, "get/set [char []] Additional data, not in the normal network data stream, that is sent with network requests to disconnect a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_DISCDATALEN, SO_DISCDATALEN, CATEGORY, "/set [ULONG] The length, in bytes, of additional data, not in the normal network data stream, that is sent with network requests to disconnect a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_DISCOPT, SO_DISCOPT, CATEGORY, "get/set [char []] Additional disconnect option data, not in the normal network data stream, that is sent with network requests to disconnect a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_DISCOPTLEN, SO_DISCOPTLEN, CATEGORY, "/set [ULONG] The length, in bytes, of additional disconnect option data, not in the normal network data stream, that is sent with network requests to disconnect a connection. This option is used by legacy protocols such as DECNet, OSI TP4, and others. ");
XLL_ENUM(SO_DEBUG, SO_DEBUG, CATEGORY, "get/set [DWORD (boolean)] Enable debug output. Microsoft providers currently do not output any debug information. ");
XLL_ENUM(SO_DONTLINGER, SO_DONTLINGER, CATEGORY, "get/set [DWORD (boolean)] Indicates the state of the l_onoff member of the linger structure associated with a socket. If this member is nonzero, a socket remains open for a specified amount of time after a closesocket function call to enable queued data. ");
XLL_ENUM(SO_DONTROUTE, SO_DONTROUTE, CATEGORY, "get/set [DWORD (boolean)] Indicates that outgoing data should be sent on whatever interface the socket is bound to and not a routed on some other interface. This option is only Valid for message-oriented protocols. ");
XLL_ENUM(SO_ERROR, SO_ERROR, CATEGORY, "get [DWORD] Returns the last error code on this socket. This per-socket error code is not always immediately set. ");
XLL_ENUM(SO_EXCLUSIVEADDRUSE, SO_EXCLUSIVEADDRUSE, CATEGORY, "get/set [DWORD (boolean)] Prevents any other socket from binding to the same address and port. This option must be set before calling the bind function. See the SO_EXCLUSIVEADDRUSE reference for more information. ");
XLL_ENUM(SO_GROUP_ID, SO_GROUP_ID, CATEGORY, "get [unsigned int] This socket option is reserved and should not be used. ");
XLL_ENUM(SO_GROUP_PRIORITY, SO_GROUP_PRIORITY, CATEGORY, "get/set [int] This socket option is reserved and should not be used. ");
XLL_ENUM(SO_KEEPALIVE, SO_KEEPALIVE, CATEGORY, "get/set [DWORD (boolean)] Enables keep-alive for a socket connection. Valid only for protocols that support the notion of keep-alive (connection-oriented protocols). For TCP, the default keep-alive timeout is 2 hrs and the keep-alive interval is 1 sec. ");
XLL_ENUM(SO_LINGER, SO_LINGER, CATEGORY, "get/set [struct linger] Indicates the state of the linger structure associated with a socket. If the l_onoff member of the linger structure is nonzero, a socket remains open for a specified amount of time after a closesocket function. ");
XLL_ENUM(SO_MAX_MSG_SIZE, SO_MAX_MSG_SIZE, CATEGORY, "get [ULONG] Returns the maximum outbound message size for message-oriented sockets supported by the protocol. Has no meaning for stream-oriented sockets. ");
XLL_ENUM(SO_MAXDG, SO_MAXDG, CATEGORY, "get [ULONG] Returns the maximum size, in bytes, for outbound datagrams supported by the protocol. This socket option has no meaning for stream-oriented sockets. ");
XLL_ENUM(SO_MAXPATHDG, SO_MAXPATHDG, CATEGORY, "get [ULONG] Returns the maximum size, in bytes, for outbound datagrams supported by the protocol to a given destination address. This socket option has no meaning for stream-oriented sockets. Microsoft providers may silently treat this as SO_MAXDG. ");
XLL_ENUM(SO_OOBINLINE, SO_OOBINLINE, CATEGORY, "get/set [DWORD (boolean)] Indicates that out-of-bound data should be returned in-line with regular data. This option is only valid for connection-oriented protocols that support out-of-band data. ");
XLL_ENUM(SO_OPENTYPE, SO_OPENTYPE, CATEGORY, "get/set [DWORD] Once set, affects whether subsequent sockets that are created will be non-overlapped. The possible values for this option are SO_SYNCHRONOUS_ALERT and SO_SYNCHRONOUS_NONALERT. This option should not be used. ");
XLL_ENUM(SO_PORT_SCALABILITY, SO_PORT_SCALABILITY, CATEGORY, "get/set [DWORD (boolean)] Enables local port scalability for a socket by allowing port allocation to be maximized by allocating wildcard ports multiple times for different local address port pairs on a local machine. ");
XLL_ENUM(SO_PROTOCOL_INFO, SO_PROTOCOL_INFO, CATEGORY, "get [WSAPROTOCOL_INFO] This option is defined to the SO_PROTOCOL_INFOW socket option if the UNICODE macro is defined. If the UNICODE macro is not defined, then this option is defined to the SO_PROTOCOL_INFOA socket option. ");
XLL_ENUM(SO_RCVBUF, SO_RCVBUF, CATEGORY, "get/set [DWORD] The total per-socket buffer space reserved for receives. This is unrelated to SO_MAX_MSG_SIZE and does not necessarily correspond to the size of the TCP receive window. ");
XLL_ENUM(SO_RCVLOWAT, SO_RCVLOWAT, CATEGORY, "get/set [DWORD] A socket option from BSD UNIX included for backward compatibility. This option sets the minimum number of bytes to process for socket input operations. ");
XLL_ENUM(SO_RCVTIMEO, SO_RCVTIMEO, CATEGORY, "get/set [DWORD] The timeout, in milliseconds, for blocking receive calls. The default for this option is zero, which indicates that a receive operation will not time out. ");
XLL_ENUM(SO_REUSEADDR, SO_REUSEADDR, CATEGORY, "get/set [DWORD (boolean)] Allows socket to bind to an address and port already in use. The SO_EXCLUSIVEADDRUSE option can prevent this. Also, if two sockets are bound to the same port the behavior is undefined as to which port will receive packets. ");
XLL_ENUM(SO_SNDBUF, SO_SNDBUF, CATEGORY, "get/set [DWORD] The total per-socket buffer space reserved for sends. This is unrelated to SO_MAX_MSG_SIZE and does not necessarily correspond to the size of a TCP send window. ");
XLL_ENUM(SO_SNDLOWAT, SO_SNDLOWAT, CATEGORY, "get/set [DWORD] A socket option from BSD UNIX included for backward compatibility. This option sets the minimum number of bytes to process for socket output operations. ");
XLL_ENUM(SO_SNDTIMEO, SO_SNDTIMEO, CATEGORY, "get/set [DWORD] The timeout, in milliseconds, for blocking send calls. The default for this option is zero, which indicates that a send operation will not time out. If a blocking send call times out, the connection is in an indeterminate state. ");
XLL_ENUM(SO_TYPE, SO_TYPE, CATEGORY, "get [DWORD] Returns the socket type for the given socket (SOCK_STREAM or SOCK_DGRAM, for example). ");
XLL_ENUM(SO_UPDATE_ACCEPT_CONTEXT, SO_UPDATE_ACCEPT_CONTEXT, CATEGORY, "/set [DWORD (boolean)] This option is used with the AcceptEx function. This option updates the properties of the socket which are inherited from the listening socket. ");
XLL_ENUM(SO_UPDATE_CONNECT_CONTEXT, SO_UPDATE_CONNECT_CONTEXT, CATEGORY, "/set [DWORD (boolean)] This option is used with the ConnectEx, WSAConnectByList, and WSAConnectByName functions. This option updates the properties of the socket after the connection is established. ");
XLL_ENUM(SO_USELOOPBACK, SO_USELOOPBACK, CATEGORY, "get/set [DWORD (boolean)] Use the local loopback address when sending data from this socket. This option should only be used when all data sent will also be received locally. ");

static AddIn xai_socket_option( 
	Function(XLL_LPOPER, "?xll_socket_option", "SOCKET.OPTION")
	.Arg(XLL_LONG, "socket", "is a socket.")
	.Arg(XLL_LONG, "level", "is an SOL_* enumeration.")
	.Arg(XLL_LONG, "option", "is an SO_* enumeration.")
	.Arg(XLL_LPOPER, "_value", "is an optional value to set.")
	.Category(CATEGORY)
	.FunctionHelp("Set socket option to value and return socket, or get option value if missing. ")
);
LPOPER WINAPI xll_socket_option(SOCKET s, LONG level, LONG option, LPOPER pValue)
{
#pragma XLLEXPORT
	static OPER result;

	try {
		result = OPER(xlerr::NA);

		switch (level) {
		case SOL_SOCKET:
			switch (option) {
//			case SO_BSP_STATE:CSADDR_INFO
			case SO_ERROR:
			case SO_OPENTYPE:
			case SO_RCVBUF:
			case SO_RCVLOWAT:
			case SO_RCVTIMEO:
			case SO_SNDBUF:
			case SO_SNDLOWAT:
			case SO_TYPE: {
				DWORD dw;
				int len(sizeof(DWORD));
				if (pValue->xltype == xltypeMissing) {
					ensure (0 == ::getsockopt(s, level, option, (char*)&dw, &len));
					result = (double)dw;
				}
				else {
					ensure (pValue->xltype == xltypeNum);
					dw = static_cast<DWORD>(pValue->val.num);
					ensure (0 == ::setsockopt(s, level, option, (char*)&dw, len));
					result = (double)s;
				}

				break;
			}
			case SO_BROADCAST:
			case SO_CONDITIONAL_ACCEPT:
			case SO_DEBUG:
			case SO_DONTLINGER:
			case SO_DONTROUTE:
			case SO_EXCLUSIVEADDRUSE:
			case SO_KEEPALIVE:
			case SO_OOBINLINE:
			case SO_PORT_SCALABILITY:
			case SO_REUSEADDR:
			case SO_UPDATE_ACCEPT_CONTEXT:
			case SO_UPDATE_CONNECT_CONTEXT:
			case SO_USELOOPBACK:
			case SO_ACCEPTCONN: {
				DWORD dw;
				int len(sizeof(DWORD));
				if (pValue->xltype == xltypeMissing) {
					ensure (0 == ::getsockopt(s, level, option, (char*)&dw, &len));
					result = dw != 0;
				}
				else {
					ensure (pValue->xltype == xltypeBool);
					dw = static_cast<DWORD>(pValue->val.xbool);
					ensure (0 == ::setsockopt(s, level, option, (char*)&dw, len));
					result = (double)s;
				}

				break;
			}
//			case SO_LINGER:struct linger
			case SO_CONNDATALEN:
			case SO_CONNECT_TIME:
			case SO_CONNOPTLEN:
			case SO_DISCDATALEN:
			case SO_DISCOPTLEN:
			case SO_MAX_MSG_SIZE:
			case SO_MAXDG:
			case SO_MAXPATHDG: {
				ULONG ul;
				int len(sizeof(ULONG));
				if (pValue->xltype == xltypeMissing) {
					ensure (0 == ::getsockopt(s, level, option, (char*)&ul, &len));
					result = (double)ul;
				}
				else {
					ensure (pValue->xltype == xltypeNum);
					ul = static_cast<ULONG>(pValue->val.num);
					ensure (0 == ::setsockopt(s, level, option, (char*)&ul, len));
					result = (double)s;
				}

				break;
			}
			case SO_PROTOCOL_INFO: {
				XLL_INFO("SOCKET.OPTION: use SOCKET.PROTOCOL.INFO for this");

				break;
			}
			default:
				XLL_ERROR("SOCKET.OPTION: unknown option");
			}

			break;
		default:
			XLL_ERROR("SOCKET.OPTION: unknown level");
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &result;
}

static AddIn xai_socket_protocol_info(
	Function(XLL_LPOPER, "?xll_socket_protocol_info", "SOCKET.PROTOCOL.INFO")
	.Arg(XLL_LONG, "socket", "is a socket.")
	.Category("XLL")
	.FunctionHelp("Returns a two column array of ...")
	.Documentation(R"(
		"This functions calls <codeInline>getsockinfo</codeInline> with <codeInline>SOL_SOCKET</codeInline> 
		and <codeInline>SO_PROTOCOL_INFO</codeInline> arguments.
	)")
);
LPOPER WINAPI xll_socket_protocol_info(SOCKET s)
{
#pragma XLLEXPORT
	static OPER result;

	try {
		result = OPER(xlerr::NA);

		WSAPROTOCOL_INFO pi;
		int npi(sizeof(pi));
		ensure (0 == ::getsockopt(s, SOL_SOCKET, SO_PROTOCOL_INFO, (char*)&pi, &npi));
		result.resize(11,2);
		xword r(0);
		result(r,0) = "Version"; result(r,1) = pi.iVersion;
		++r;
		result(r,0) = "AddressFamily"; result(r,1) = pi.iAddressFamily;
		++r;
		result(r,0) = "MaxSockAddr"; result(r,1) = pi.iMaxSockAddr;
		++r;
		result(r,0) = "MinSockAddr"; result(r,1) = pi.iMinSockAddr;
		++r;
		result(r,0) = "SocketType"; result(r,1) = pi.iSocketType;
		++r;
		result(r,0) = "Protocol"; result(r,1) = pi.iProtocol;
		++r;
		result(r,0) = "ProtocolMaxOffset"; result(r,1) = pi.iProtocolMaxOffset;
		++r;
		result(r,0) = "NetworkByteOrder"; result(r,1) = pi.iNetworkByteOrder;
		++r;
		result(r,0) = "SecurityScheme"; result(r,1) = pi.iSecurityScheme;
		++r;
		result(r,0) = "MessageSize"; result(r,1) = pi.dwMessageSize;
		++r;
		result(r,0) = "Protocol"; result(r,1) = pi.szProtocol;
		++r;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &result;
}
