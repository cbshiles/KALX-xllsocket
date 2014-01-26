// socket.h - socket wrappers
#pragma once
#include <string>
#include "../xll8/xll/ensure.h"
#include <WinSock2.h>
#include <ws2tcpip.h>

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

	inline std::string recv(SOCKET s, int bufsiz = 4096)
	{
		std::string buf;

		int n, off(0);
		do {
			buf.reserve(off + bufsiz);
			ensure (0 <= (n = ::recv(s, &buf[off], bufsiz, 0)));
			off += bufsiz;
		} while (n == bufsiz);

		return buf;
	}

} // socket