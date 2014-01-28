// xllsocket_shutdown.cpp
#include "xllsocket.h"

using namespace xll;


XLL_ENUM(SD_RECEIVE, SD_RECEIVE, CATEGORY, "Shutdown receive operations. ");
XLL_ENUM(SD_SEND, SD_SEND, CATEGORY, "Shutdown send operations. ");
XLL_ENUM(SD_BOTH, SD_BOTH, CATEGORY, "Shutdown both send and receive operations. ");

static AddIn xai_socket_shutdown(
	Function(XLL_LONG, "?xll_socket_shutdown", "SOCKET.SHUTDOWN")
	.Arg(XLL_LONG, "socket", "is a socket. ")
	.Arg(XLL_LONG, "_how", "is an optional SD_* enumeration. Default is SD_BOTH. ")
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a socket.")
);
SOCKET WINAPI xll_socket_shutdown(SOCKET s, LONG how)
{
#pragma XLLEXPORT
	try {
		if (!how)
			how = SD_BOTH;

		ensure (SOCKET_ERROR != ::shutdown(s, how));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		s = INVALID_SOCKET;
	}

	return s;
}

