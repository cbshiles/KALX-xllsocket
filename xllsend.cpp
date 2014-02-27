// xllsend.cpp
#include "xllsocket.h"

using namespace xll;

static AddIn xai_socket_send(
	FunctionX(XLL_LONG, "?xll_socket_send", "SOCKET.SEND")
	.Arg(XLL_LONG, "socket", "is a socket returned by SOCKET.")
	.Arg(XLL_LPOPER, "data", "is the data string to send to the socket.")
	.Arg(XLL_BOOL, "_CRLF", "optional boolean indicating CR LF message separators.")
	.Arg(XLL_PSTRING, "_sep", "optional field separator.")
	.Category(CATEGORY)
	.FunctionHelp("Send data down a socket.")
);
SOCKET WINAPI xll_socket_send(SOCKET s, LPOPER pData, BOOL crlf, xcstr sep)
{
#pragma XLLEXPORT
	try {

		const OPER& data(*pData);
		int nsep = strlen(sep);
		for (WORD i = 0; i < data.rows(); ++i) {
			for (WORD j = 0; j < data.columns(); ++j) {
				ensure (xltypeStr == data(i,j).xltype);
				if (nsep && i > 0) {
					ensure (nsep == ::send(s, sep, nsep, 0));
				}
				ensure (data(i,j).val.str[0] == ::send(s, data(i,j).val.str + 1, data(i,j).val.str[0], 0));
			}
			if (crlf)
				ensure (2 == ::send(s, "\r\n", 2, 0));
		}
		if (crlf) {
			ensure (2 == ::send(s, "\r\n", 2, 0));
		}
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		s = INVALID_SOCKET;
	}

	return s;
}

