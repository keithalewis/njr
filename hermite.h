// hermite.h - Hermite polynomials
#pragma once

namespace poly {

	// H_{n+1} = x H_n - n H_{n-1}
	template<class X = double>
	inline X Hermite(size_t n, const X& x)
	{
		if (n == 0)
			return X(1);
		if (n == 1)
			return x;

		X _H = 1, H = x, H_ = x*x - 1;
		for (size_t k = 1; k < n; ++k) {
			H_ = x*H - k*_H;
			_H = H;
			H  = H_;
		}

		return H_;
	}

} // poly namespace

#ifdef _DEBUG
#include <ctime>
#include <random>

inline void test_hermite()
{
	std::default_random_engine dre{static_cast<unsigned>(time(0))};
	std::uniform_real_distribution<> u;

	for (int i = 0; i < 100; ++i) 
	{
		auto x = u(dre);

		ensure (poly::Hermite(0, x) == 1);
		ensure (poly::Hermite(0,1/x) == 1);
		ensure (poly::Hermite(0, -x) == 1);
		ensure (poly::Hermite(0,-1/x) == 1);

		ensure (poly::Hermite(1, x) == x);
		ensure (poly::Hermite(1,1/x) == 1/x);
		ensure (poly::Hermite(1, -x) == -x);
		ensure (poly::Hermite(1,-1/x) == -1/x);

		ensure (poly::Hermite(2, x) == x*x - 1);
		ensure (poly::Hermite(2,1/x) == (1/x)*(1/x) - 1);
		ensure (poly::Hermite(2, -x) == (-x)*(-x) - 1);
		ensure (poly::Hermite(2,-1/x) == (-1/x)*(-1/x) - 1);

	}
}

#endif // _DEBUG