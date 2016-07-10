// hermite.cpp - Hermite polynomials
#include "njr.h"
#include "hermite.h"
#include "ftap.h"

using namespace xll;

AddIn xai_hermite(Function(XLL_DOUBLE, L"?xll_hermite", CATEGORY_ L"HERMITE")
	.Arg(XLL_WORD, L"n", L"the order of the Hermite polynomial")
	.Arg(XLL_DOUBLE, L"x", L"the value at which to evaluate the polynomial")
	.Category(CATEGORY)
	.FunctionHelp(L"The value of the n-th Hermite polynomial evaluated at x")
);
double WINAPI xll_hermite(DWORD n, double x)
{
#pragma XLLEXPORT
	return poly::Hermite(n, x);
}

#ifdef _DEBUG
#include "../xll12/xll/test.h"

BEGIN_TEST(hermite)
	test_hermite();
	test_choose();
	test_ftap();
END_TEST

#endif // _DEBUG