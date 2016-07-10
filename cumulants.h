// cumulants.h - cumulants of various distributions
// log E exp(sX) = kappa(s) = sum_1^infty kappa_n s^n/n!
#pragma once
#include <iterator>
#include <limits>

namespace cumulants {

	template<class X>
	class constant : public std::iterator<std::forward_iterator_tag, X> {
		size_t n;
	public:
		constant()
			: n(0)
		{ }
		bool operator==(const constant& n) const
		{
			return this->n == n.n;
		}
		bool operator!=(const constant& n) const
		{
			return !operator==(n);
		}
		X operator*() const
		{
			return n == 0 ? 1 : 0;
		}
		constant& operator++()
		{
			++n;

			return *this;
		}
		constant operator++(int)
		{
			auto n_(*this);

			operator++();

			return n_;
		}
	};

	template<class X>
	class normal : public std::iterator<std::forward_iterator_tag, X> {
		size_t n;
	public:
		normal()
			: n(0)
		{ }
		bool operator==(const normal& n) const
		{
			return this->n == n.n;
		}
		bool operator!=(const normal& n) const
		{
			return !operator==(n);
		}
		X operator*() const
		{
			return n == 1 ? 1 : 0;
		}
		normal& operator++()
		{
			++n;

			return *this;
		}
		normal operator++(int)
		{
			auto n_(*this);

			operator++();

			return n_;
		}
	};

	// kappa(s) = a log b/(b - s)
	//          = a log 1/(1 - s/b)
	//          = a sum_1^infty (s/b)^n/n
	// so kappa_n = (n-1)! a/b^n
	template<class X>
	class Gamma : public std::iterator<std::forward_iterator_tag, X> {
		size_t n;
		X kappa;
		X b;
	public:
		Gamma(X a, X b)
			: n(0), kappa(a/b), b(b)
		{ }
		bool operator==(const Gamma& g) const
		{
			return this->n == n.n
				&& this->kappa == g.kappa
				&& this->b == g.b;
		}
		bool operator!=(const Gamma& g) const
		{
			return !operator==(g);
		}
		X operator*() const
		{
			return kappa;
		}
		Gamma& operator++()
		{
			++n;
			kappa *= n/b;

			return *this;
		}
		Gamma operator++(int)
		{
			auto n_(*this);

			operator++();

			return n_;
		}
	};

	// kappa(s) = lambda (e^s - 1)
	// so kappa_n = lambda
	template<class X>
	class Poisson : public std::iterator<std::forward_iterator_tag, X> {
		X lambda;
	public:
		Poisson(X lambda)
			: lambda(lambda)
		{ }
		bool operator==(const Poisson& p) const
		{
			return this->lambda == p.lambda;
		}
		bool operator!=(const Poisson& g) const
		{
			return !operator==(g);
		}
		X operator*() const
		{
			return lambda;
		}
		Poisson& operator++()
		{
			return *this;
		}
		Poisson operator++(int)
		{
			return *this;
		}
	};
} // cumulants
