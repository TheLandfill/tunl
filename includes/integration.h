#ifndef TUNL_INTEGRATION_H
#define TUNL_INTEGRATION_H
#include "real.h"
#include <cstddef>

struct Simpson_Points {
public:
	real start;
	real dx;
	const size_t n;
	Simpson_Points(real a, real b, size_t n);
};

template <typename T>
struct Simpson_Sums {
public:
	T trapezoid_sum;
	T midpoint_sum;
	T value_holder;
};

template <typename T, typename FuncType>
T simpson_rule(FuncType f, const Simpson_Points & sp, Simpson_Sums<T>& ss) {
	real cur_x = sp.start;
	real dx = sp.dx * 0.5;

	f(ss.value_holder, cur_x);
	ss.trapezoid_sum += 0.5 * ss.value_holder;

	cur_x += dx;

	f(ss.value_holder, cur_x);
	ss.midpoint_sum += ss.value_holder;

	cur_x += dx;

	for (size_t i = 1; i < sp.n; i++) {
		f(ss.value_holder, cur_x);
		ss.trapezoid_sum += ss.value_holder;

		cur_x += dx;

		f(ss.value_holder, cur_x);
		ss.midpoint_sum += ss.value_holder;

		cur_x += dx;
	}

	f(ss.value_holder, cur_x);
	ss.trapezoid_sum += 0.5 * ss.value_holder;

	const real ONE_THIRD = 1.0 / 3.0;
	return (2.0 * ss.midpoint_sum + ss.trapezoid_sum) * ONE_THIRD * sp.dx;
}

#endif
