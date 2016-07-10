// ftap.h
#pragma once
#include <cmath>
#include <functional>
#include <iterator>
#include <numeric>

// [b, b + 1, ..., e]
template<class T>
class sequence : public std::iterator<std::input_iterator_tag, T> {
	T b, e, i;
public:
	sequence(T b, T e)
		: b(b), e(e), i(b)
	{ }
	sequence(T b, T e, T i)
		: b(b), e(e), i(i)
	{ }
	bool operator==(const sequence& s) const
	{
		return b == s.b && e == s.e && i == s.i;
	}
	bool operator!=(const sequence& s) const
	{
		return !operator==(s);
	}
	const T& operator*() const
	{
		return i;
	}
	sequence& operator++()
	{
		++i;

		return *this;
	}
	sequence operator++(int)
	{
		auto s(*this);

		operator++();

		return s;
	}
	sequence begin() const
	{
		return sequence(b, e, b);
	}
	sequence end() const
	{
		return sequence(b, e + 1, e + 1);
	}
};

inline size_t choose(size_t n, size_t k)
{
	size_t cnk = 1;
	if (k > n/2)
		k = n - k;
	// backwards to avoid integer truncation
	for (size_t i = 1; i <= k; ++i) {
		cnk *= n--;
		cnk /= i;
	}

	return cnk;
}

template<size_t N>
struct binomial_algebra {
	struct atom {
		size_t value;
		atom(size_t value)
			: value(value)
		{
			//ensure (value <= N);
		}
		bool operator==(const atom& a) const
		{
			return value == a.value;
		}
		class iterator {
			atom a;
		public:
			iterator(size_t i)
				: a(i);
			{ }
			bool operator==(const iterator& i) const
			{
				return a == i.a;
			}
			bool operator!=(const iterator& i) const
			{
				return !operator==(i);
			}
			atom operator*() const
			{
				return a;
			}
			iterator& operator++()
			{
				++a.value;
					
				return *this;
			}
		};
	};
	// choose(n, i)/2^n
	double measure(const atom& a)
	{
		return ldexp(choose(N, a.value), -N);
	}
};

template<class Atom>
using random_variable = std::function<double(const Atom&)>;

template<class Atom>
using measure = std::function<double(const Atom&)>;

template<class Atom>
inline measure<Atom> operator*(const random_variable<Atom>& X, const measure<Atom>& Pi)
{
	return [&X,&Pi](const Atom& a) { return X(a)*Pi(a); }
}

#ifdef _DEBUG
#include <cassert>

inline void test_choose()
{
	assert (choose(0, 0) == 1);
	assert (choose(1, 0) == 1);
	assert (choose(1, 1) == 1);
	assert (choose (5, 2) == (5*4)/2);
	assert (choose (5, 3) == 10);
}

inline void test_ftap()
{
	{
		auto s = sequence<size_t>(0, 3);
		auto s_(s);
		assert (s == s_);
		s = s_;
		assert (!(s != s_));

		assert (s == s.begin());
		assert (*s == 0);
		assert (*++s == 1);
		s++;
		assert (*s == 2);
		
		assert (++s == s.end());
	}
	{
	}
}

#endif // _DEBUG