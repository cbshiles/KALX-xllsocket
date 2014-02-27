// socket.h - socket wrappers
#pragma once
#include <random>
#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include "../xll8/xll/ensure.h"
#include "codec.h"

#pragma comment(lib, "Ws2_32.lib")

namespace sock {

	struct startup {
		static int init()
		{
			static int result(-1);
			static bool first(true);
			static WSADATA wsaData;

			if (first) {
				result =  WSAStartup(MAKEWORD(2,2), &wsaData);
				first = false;
			}

			return result;
		}
		startup()
		{
			ensure (0 == init());
		}
		startup(const startup&) = delete;
		startup& operator=(const startup&) = delete;
		~startup()
		{
			WSACleanup();
		}
	};

	class et {
		static startup wsa;
		SOCKET s_;
	public:
		// default to either IPv6 or IPv4 TCP
		et(int af = AF_UNSPEC, int type = SOCK_STREAM, int proto = IPPROTO_TCP)
			: s_(::socket(af, type, proto))
		{
			ensure (INVALID_SOCKET != s_);
		}
		et(const et&) = default;
		et& operator=(const et&) = default;
		~et()
		{
			closesocket(s_);
		}
		operator SOCKET()
		{
			return s_;
		}
	};

	class addrinfo {
		::addrinfo* pai_;
	public:
		addrinfo(const char* host, const char* port, SOCKET s = INVALID_SOCKET)
			: pai_(0)
		{
			::addrinfo hints;

			ZeroMemory(&hints, sizeof(hints));
			if (INVALID_SOCKET != s) {
				WSAPROTOCOL_INFO pi;

				int npi(sizeof(pi));
				ensure (0 == getsockopt(s, SOL_SOCKET, SO_PROTOCOL_INFO, (char*)&pi, &npi));

				hints.ai_family = pi.iAddressFamily;
				hints.ai_socktype = pi.iSocketType;
				hints.ai_protocol = pi.iProtocol;
			}
			else {
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;
			}

			ensure (0 == getaddrinfo(host, port, &hints, &pai_));
		}
		~addrinfo()
		{
			if (pai_)
				freeaddrinfo(pai_);
		}

		::addrinfo* ptr()
		{
			return pai_;
		}
		const ::addrinfo* ptr() const
		{
			return pai_;
		}
	};

	inline int connect(SOCKET s, const char* host, const char* port)
	{
		addrinfo ai(host, port, s);

		return ::connect(s, ai.ptr()->ai_addr, ai.ptr()->ai_addrlen);
	}

	inline int send(SOCKET s, const char* buf, size_t len = 0, int flags = 0)
	{
		if (!len)
			len = strlen(buf);

		return ::send(s, buf, len, flags);
	}
	inline int send(SOCKET s, const std::string& buf, int flags = 0)
	{
		return ::send(s, buf.c_str(), buf.length(), flags);
	}

	inline std::string recv(SOCKET s, int bufsiz = 4096)
	{
		std::string buf;
		buf.resize(bufsiz);

		for (int n = bufsiz, off = 0; n == bufsiz || n == 0; off += bufsiz) {
			buf.reserve(off + bufsiz);
			n = ::recv(s, &buf[off], bufsiz, 0);
			buf.resize(off + n);
		}

		return buf;
	}

	// websocket
	class web {
		static unsigned int rand()
		{
			static std::default_random_engine dre_;

			return dre_();
		}
		sock::et s_;
		std::string key_;
		// uuencoded 16 byte random key
		static std::string make_key(void)
		{
			union {
				int i[4];
				BYTE b[16];
			} key;
			for (int i = 0; i < 4; ++i)
				key.i[i] = rand();
			return Base64::Encode(&(key.b[0]), 16);
		}
	public:
		web(const char* host, const char* port = "80", const char* resource = "/", bool secure = false)
			: key_(make_key())
		{
			ensure (0 == sock::connect(s_, host, port));

			sock::send(s_, "Cache-Control:no-cache\r\n");
			sock::send(s_, "Connection:Upgrade\r\n");
			sock::send(s_, "Host:echo.websocket.org\r\n");
			sock::send(s_, "Origin:http://www.websocket.org\r\n");
			sock::send(s_, "Pragma:no-cache\r\n");
//			sock::send(s_, "Sec-WebSocket-Extensions:permessage-deflate; client_max_window_bits, x-webkit-deflate-frame\r\n");
			sock::send(s_, "Sec-WebSocket-Key:");
			sock::send(s_, key_);
			sock::send(s_, "\r\nSec-WebSocket-Version:13\r\n");
			sock::send(s_, "Upgrade:websocket\r\n");
			sock::send(s_, "\r\n");

		}
		web(const web&) = delete;
		web& operator=(const web&) = delete;
		~web()
		{ }
		const std::string& key(void) const
		{
			return key_;
		}
	};

} // socket