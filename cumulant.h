// cumulant.h - cumulants of various distributions
#pragma once
#include <cmath>
#include <iterator>

namespace cumulant {

	// X ~ mu + sigma Z, Z standard normal
	// log E exp(sX) = mu s + sigma^2s^2/2
	template<class S, class X>
	inline auto normal(S s, X mu = 0, X sigma = 1)
	{
		return mu*s + sigma*sigma*s*s/2;
	}

	// X ~ Gamma(a, b)
	// pdf(x) = x^(a-1) exp(-bx) b^a/Gamma(a), x > 0
	// E X = ab, Var X = ab^2
	// log E exp(sX) = log int_0^infty exp(s x) x^(a-1) exp(-bx) dx b^a/Gamma(a)
	//               = log int_0^infty x^(a-1) exp(-(b - s)x) dx b^a/Gamma(a)
	//               = log Gamma(a)/(b - s)^a b^a/Gamma(a)
	//               = log (b/(b - s))^a
	//               = a log b/(b - s)
	template<class S, class X>
	inline auto Gamma(S s, X a, X b)
	{
		return a*log(s/(b - s));
	}

	// X ~ exponential(lambda)
	// pdf(x) = lambda exp(-lambda x), x > 0
	// Exponential(lambda) ~ Gamma(1, lambda)
	template<class S, class X>
	inline auto exponential(S s, X lambda)
	{
		return log(s/(lambda - s));
	}

	// X ~ Poisson(lambda)
	// P(X = k) = lambda^k/k! exp(-lambda), k = 0, 1, 2,...
	// log E exp(s X) = log sum_0^infty e^(sk) lambda^k/k! e^-lambda 
	//	              = log sum_0^infty e^(sk) lambda^k/k! e^-lambda 
	//	              = log sum_0^infty (e^s lambda)^k/k! e^-lambda
	//	              = log e^(e^s lambda) e^-lambda
	//	              = log e^((e^s - 1) lambda)
	//	              = (e^s - 1) lambda
	template<class S, class X>
	inline auto Poisson(S s, X lambda)
	{
		return (exp(s) - 1)*lambda;
	}

} // cumulant