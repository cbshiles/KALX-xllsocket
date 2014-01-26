// xllsocket.h - sockets in Excel
#pragma once
//#define EXCEL12
#include "../xll8/xll/xll.h"
#include "socket.h"

#ifndef CATEGORY
#define CATEGORY _T("XLL")
#endif
#ifndef PREFIX
#define PREFIX _T("")
#endif

typedef xll::traits<XLOPERX>::xword xword;
typedef xll::traits<XLOPERX>::xchar xchar;
typedef xll::traits<XLOPERX>::xcstr xcstr;
typedef xll::traits<XLOPERX>::xstring xstring;

