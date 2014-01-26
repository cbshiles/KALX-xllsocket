// socket.cpp - Using sockets
#include "xllsocket.h"

using namespace xll;

sock::startup init;

XLL_ENUM(SD_RECEIVE, SD_RECEIVE, CATEGORY, "Shutdown receive operations.");
XLL_ENUM(SD_SEND, SD_SEND, CATEGORY, "Shutdown send operations.");
XLL_ENUM(SD_BOTH, SD_BOTH, CATEGORY, "Shutdown both send and receive operations.");

static AddIn xai_socket_shutdown(
	Function(XLL_WORD, "?xll_socket_shutdown", "SOCKET.SHUTDOWN")
	.Arg(XLL_WORD, "host", "is the host name or IP address.")
	.Arg(XLL_SHORT, "how", "is an SD_* enumeration.")
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a socket.")
);
SOCKET WINAPI xll_socket_shutdown(SOCKET s, SHORT how)
{
#pragma XLLEXPORT
	try {
		ensure (SOCKET_ERROR != ::shutdown(s, how));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		s = INVALID_SOCKET;
	}

	return s;
}

static AddIn xai_socket_connect(
	Function(XLL_WORD, "?xll_socket_connect", "SOCKET.CONNECT")
	.Arg(XLL_CSTRING, "host", "is the host name or IP address.")
	.Arg(XLL_CSTRING, "port", "is the optional service name or port number.")
	.Category(CATEGORY)
	.FunctionHelp("Return a handle to a socket.")
);
SOCKET WINAPI xll_socket_connect(xcstr host, xcstr port)
{
#pragma XLLEXPORT
	SOCKET s(INVALID_SOCKET);

	try {
		s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		ensure (0 <= sock::connect(s, host, port));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return s;
}

static AddIn xai_socket_send(
	FunctionX(XLL_WORD, "?xll_socket_send", "SOCKET.SEND")
	.Arg(XLL_WORD, "socket", "is a handle returned by SOCKET.CONNECT.")
	.Arg(XLL_LPOPER, "data", "is the data string to send to the socket.")
	.Arg(XLL_BOOL, "_CRLF", "optional boolean indicating CR LF message separators.")
	.Category(CATEGORY)
	.FunctionHelp("Send data down a socket.")
);
SOCKET WINAPI xll_socket_send(SOCKET s, LPOPER pData, BOOL crlf)
{
#pragma XLLEXPORT
	try {
		const OPER& data(*pData);
		for (WORD i = 0; i < data.size(); ++i) {
			ensure (xltypeStr == data[i].xltype);
			ensure (data[i].val.str[0] == ::send(s, data[i].val.str + 1, data[i].val.str[0], 0));
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

static AddIn xai_socket_recv(
	Function(XLL_HANDLE, "?xll_socket_recv", "SOCKET.RECV")
	.Arg(XLL_WORDX, "socket", "is a handle returned by SOCKET.SEND.")
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

#ifdef _DEBUG

int xll_test_sock()
{
	try {
		int ret;
		SOCKET s = socket(AF_UNSPEC, SOCK_STREAM, IPPROTO_TCP);
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