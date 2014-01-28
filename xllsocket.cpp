// socket.cpp - Using sockets
#include "xllsocket.h"

using namespace xll;

sock::startup init;

// address family
XLL_ENUM(AF_UNSPEC, AF_UNSPEC, CATEGORY, "The address family is unspecified. ");
XLL_ENUM(AF_INET, AF_INET, CATEGORY, "The Internet Protocol version 4 (IPv4) address family. ");
XLL_ENUM(AF_IPX, AF_IPX, CATEGORY, "The IPX/SPX address family. This address family is only supported if the NWLink IPX/SPX NetBIOS Compatible Transport protocol is installed. ");
XLL_ENUM(AF_APPLETALK, AF_APPLETALK, CATEGORY, "The AppleTalk address family. This address family is only supported if the AppleTalk protocol is installed. ");
XLL_ENUM(AF_NETBIOS, AF_NETBIOS, CATEGORY, "The NetBIOS address family. This address family is only supported if the Windows Sockets provider for NetBIOS is installed. ");
XLL_ENUM(AF_INET6, AF_INET6, CATEGORY, "The Internet Protocol version 6 (IPv6) address family. ");
XLL_ENUM(AF_IRDA, AF_IRDA, CATEGORY, "The Infrared Data Association (IrDA) address family. ");
XLL_ENUM(AF_BTH, AF_BTH, CATEGORY, "The Bluetooth address family. ");

// socket type
XLL_ENUM(SOCK_STREAM, SOCK_STREAM, CATEGORY, "A socket type that provides sequenced, reliable, two-way, connection-based byte streams with an OOB data transmission mechanism. This socket type uses the Transmission Control Protocol (TCP) for the Internet address family (AF_INET or AF_INET6). ");
XLL_ENUM(SOCK_DGRAM, SOCK_DGRAM, CATEGORY, "A socket type that supports datagrams, which are connectionless, unreliable buffers of a fixed (typically small) maximum length. This socket type uses the User Datagram Protocol (UDP) for the Internet address family (AF_INET or AF_INET6). ");
XLL_ENUM(SOCK_RAW, SOCK_RAW, CATEGORY, "A socket type that provides a raw socket that allows an application to manipulate the next upper-layer protocol header. To manipulate the IPv4 header, the IP_HDRINCL socket option must be set on the socket. ");
XLL_ENUM(SOCK_RDM, SOCK_RDM, CATEGORY, "A socket type that provides a reliable message datagram. An example of this type is the Pragmatic General Multicast (PGM) multicast protocol implementation in Windows, often referred to as reliable multicast programming. ");
XLL_ENUM(SOCK_SEQPACKET, SOCK_SEQPACKET, CATEGORY, "A socket type that provides a pseudo-stream packet based on datagrams. ");

// protocol
XLL_ENUM(IPPROTO_ICMP, IPPROTO_ICMP, CATEGORY, "The Internet Control Message Protocol (ICMP). This is a possible value when the af parameter is AF_UNSPEC, AF_INET, or AF_INET6 and the type parameter is SOCK_RAW or unspecified. ");
XLL_ENUM(IPPROTO_IGMP, IPPROTO_IGMP, CATEGORY, "The Internet Group Management Protocol (IGMP). This is a possible value when the af parameter is AF_UNSPEC, AF_INET, or AF_INET6 and the type parameter is SOCK_RAW or unspecified. ");
XLL_ENUM(IPPROTO_TCP, IPPROTO_TCP, CATEGORY, "The Transmission Control Protocol (TCP). This is a possible value when the af parameter is AF_INET or AF_INET6 and the type parameter is SOCK_STREAM. ");
XLL_ENUM(IPPROTO_UDP, IPPROTO_UDP, CATEGORY, "The User Datagram Protocol (UDP). This is a possible value when the af parameter is AF_INET or AF_INET6 and the type parameter is SOCK_DGRAM. ");
XLL_ENUM(IPPROTO_ICMPV6, IPPROTO_ICMPV6, CATEGORY, "The Internet Control Message Protocol Version 6 (ICMPv6). This is a possible value when the af parameter is AF_UNSPEC, AF_INET, or AF_INET6 and the type parameter is SOCK_RAW or unspecified. ");

static AddIn xai_socket(
	Function(XLL_LONG, "?xll_socket", "SOCKET")
	.Arg(XLL_LONG, "_af", "is an optional address family from the AF_* enumeration. Default is AF_UNSPEC.")
	.Arg(XLL_LONG, "_type", "is an optional socket type from the SOCK_* enumeration. Default is SOCK_STREAM.")
	.Arg(XLL_LONG, "_proto", "is an optional protocol from the IPPROTO_* enumeration. Default is IPPROTO_TCP.")
	.Category(CATEGORY)
	.FunctionHelp("Return a socket.")
);
SOCKET WINAPI xll_socket(LONG af, LONG type, LONG proto)
{
#pragma XLLEXPORT

	if (!af)
		af = AF_UNSPEC;
	if (!type)
		type = SOCK_STREAM;
	if (!proto)
		proto = IPPROTO_TCP;

	return ::socket(af, type, proto);
}

/*
#ifdef _DEBUG

int xll_test_sock()
{
	try {
		size_t size;
		size = sizeof(SOCKET);
		int ret;
		sock::et s;
		ensure (s != INVALID_SOCKET);

//		ret = s.connect("127.0.0.1", "5000");
		ret = sock::connect(s, "example.com", "http");
//		ret = sock::connect(s, "google.com", "http");
		ret = WSAGetLastError();
		const char* get = "HEAD /index.html HTTP/1.0\r\n";
		ret = ::send(s, get, strlen(get), 0);
		ret = ::send(s, "\r\n", 2, 0);
		ret = WSAGetLastError();
//		::shutdown(s, SD_SEND);
//		char buf[1024];
		std::string str = sock::recv(s);
//		ret = ::recv(s, buf, 1024, 0);
		ret = WSAGetLastError();

		ret = ret;
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenX> xao_test_sock(xll_test_sock);

#endif // _DEBUG
*/