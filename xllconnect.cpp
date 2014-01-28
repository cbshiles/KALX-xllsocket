// xllconnect.cpp
#include "xllsocket.h"

using namespace xll;

static AddIn xai_socket_connect(
	Function(XLL_LONG, "?xll_socket_connect", "SOCKET.CONNECT")
	.Arg(XLL_LONG, "socket", "is a socket returned by SOCKET.")
	.Arg(XLL_CSTRING, "host", "is the host name or IP address.")
	.Arg(XLL_CSTRING, "port", "is the optional service name or port number.")
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a socket.")
);
SOCKET WINAPI xll_socket_connect(SOCKET s, xcstr host, xcstr port)
{
#pragma XLLEXPORT
	try {
		ensure (0 <= sock::connect(s, host, port));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return INVALID_SOCKET;
	}

	return s;
}

