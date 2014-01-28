// xllstring.cpp - handles to std::string
//#define EXCEL12
#include <cstring>
#include <mbstring.h>
#include "../xll8/xll/xll.h"

#ifndef CATEGORY
#define CATEGORY _T("XLL")
#endif

using namespace xll;

typedef traits<XLOPERX>::xchar xchar;
typedef traits<XLOPERX>::xcstr xcstr;
typedef traits<XLOPERX>::xstring xstring;
typedef traits<XLOPERX>::xword xword;

static AddInX xai_string_set(
	FunctionX(XLL_HANDLEX, _T("?xll_string_set"), _T("STRING.SET"))
	.Arg(XLL_LPOPERX, _T("Range"), _T("is a range of cells."))
	.Uncalced()
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a handle to a std::string."))
);
HANDLEX WINAPI xll_string_set(LPOPERX pStr)
{
#pragma XLLEXPORT
	handlex h;

	try {
		h = handle<xstring>(new xstring(pStr->to_string())).get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return h;
}

static AddInX xai_string_split(
	FunctionX(XLL_LPOPERX, _T("?xll_string_split"), _T("STRING.SPLIT"))
	.Arg(XLL_LPOPERX, _T("String"), _T("is a string or handle to a string."))
	.Arg(XLL_CSTRINGX, _T("Sep"), _T("is a string of characters used to separate records."))
	.Arg(XLL_BOOLX, _T("_All"), _T("is an optional boolean indicating all of Sep must be used instead of any."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a range that is split based on the separator."))
);
LPOPERX WINAPI xll_string_split(LPOPERX po, xcstr sep, BOOL all)
{
#pragma XLLEXPORT
	static OPERX o;

	try {
		size_t n;
		xcstr s;

		if (po->xltype == xltypeNum) {
			handle<xstring> hs(po->val.num);
			s = hs->c_str();
			n = hs->size();
		}
		else if (po->xltype == xltypeStr) {
			s = po->val.str + 1;
			n = po->val.str[0];
		}
		else {
			// ??? if column of strings split on record sep???
			return po; // do nothing
		}

		o.resize(0,0);

		std::function<xcstr(xcstr, xcstr)> strsep;
		xchar incr;

		if (all) {
			strsep = [](xcstr s, xcstr t) { return _tcsstr(s, t); };
			incr = static_cast<xchar>(_tcslen(sep));
		}
		else {
			strsep = [](xcstr s, xcstr t) { return _tcspbrk(s, t); };
			incr = 1;
		}

		xcstr b = s;

		for (xcstr e = strsep(b, sep); e; b = e + incr, e = strsep(b, sep)) {
			o.push_back(OPERX(b, static_cast<char>(e - b)));
		}

		o.push_back(OPERX(b, static_cast<char>(n - (b - s))));
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		o = OPERX(xlerr::NA);
	}

	return &o;
}

static AddInX xai_string_get(
	FunctionX(XLL_LPOPERX, _T("?xll_string_get"), _T("STRING.GET"))
	.Arg(XLL_HANDLEX, _T("Handle"), _T("is handle to a std::string."))
	.Arg(XLL_CSTRINGX, _T("Sep"), _T("is a string of characters used to separate records."))
	.Arg(XLL_BOOLX, _T("_All"), _T("is an optional boolean indicating all of Sep must be used instead of any."))
	.Category(CATEGORY)
	.FunctionHelp(_T("Return a std::string."))
	.Documentation(R"(
		Prior to Excel 2007 strings were limited to 255 characters. Use a separator
		to split long strings into a range.
	)")
);
LPOPER WINAPI xll_string_get(HANDLEX h, xcstr sep, BOOL all)
{
#pragma XLLEXPORT
	static OPERX s;

	s = OPERX(xlerr::NA);
	try {
		OPERX hs(h);

		s = *xll_string_split(&hs, sep, all);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return &s;
}

#ifdef _DEBUG

void test_string(const xstring& str, xcstr sep, BOOL all, const std::vector<xstring> res)
{
	OPERX o(str), o_;
	o_ = *xll_string_split(&o, sep, all);
	ensure (o_.rows() == (xword)res.size() && o_.columns() == 1);
	for (xword i = 0; i < (xword)res.size(); ++i)
		ensure (o_[i] == res[i]);

	handle<xstring> hs(new xstring(str));
	OPERX s(hs.get());
	o_ = *xll_string_split(&s, sep, all);
	ensure (o_.rows() == (xword)res.size() && o_.columns() == 1);
	for (xword i = 0; i < (xword)res.size(); ++i)
		ensure (o_[i] == res[i]);

}

int xll_test_string(void)
{
	try {
		std::vector<xstring> res = {_T("a"), _T("b"), _T("c")};
		test_string(_T("a,b,c"), _T(","), 0, res);
		test_string(_T("a--b--c"), _T("--"), 1, res);

		res = {_T("a"), _T(""), _T("b"), _T(""), _T("c")};
		test_string(_T("a--b--c"), _T("-"), 0, res);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());

		return 0;
	}

	return 1;
}
static Auto<OpenAfterX> xao_test_string(xll_test_string);

#endif // _DEBUG
