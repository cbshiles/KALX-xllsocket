// xllrecv.cpp
#include "xllsocket.h"

using namespace xll;

static AddIn xai_socket_recv(
	Function(XLL_HANDLE, "?xll_socket_recv", "SOCKET.RECV")
	.Arg(XLL_LONG, "socket", "is a handle returned by SOCKET.SEND.")
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to the string buffer received from a socket.")
);
HANDLEX WINAPI xll_socket_recv(SOCKET s)
{
#pragma XLLEXPORT
	handlex h;

	try {
		h = handle<std::string>(new std::string(sock::recv(s))).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}
