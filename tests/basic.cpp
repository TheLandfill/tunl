#include "real.h"
#include "integration.h"
#include <iostream>
#include <limits>
#include <cmath>

typedef std::numeric_limits<double> dbl;

void quadratic_integrand(real& holder, real x) {
	holder = x * x + 3;
//	std::cout << "(" << (double)x << ", " << (double)holder << ")\n";
}

real fast_exp(real exponent) {
	if (exponent > 0) {
		return exp(exponent);
	}
	const unsigned int LOG_N = 50;
	const real ONE = 1.0;
	const real DENOM = (long long)1 << LOG_N;
	real x = ONE + exponent / DENOM;
	for (unsigned int i = 0; i < LOG_N; i++) {
		x *= x;
	}
	return x;
}

void gaussian(real& holder, real x) {
	holder = fast_exp(-(x * x));
}

void sqrt_integrand(real& holder, real x) {
	holder = sqrt(x);
}

void test_fast_exp() {
	for (real x = 0.0; x > -10; x -= 0.1) {
		std::cout << (double)x << ":\t" << std::abs((double)fast_exp(x) - exp(x)) << "\t" << (double)fast_exp(x) << "\n";
	}
}

void test_quadratic() {
	const unsigned int NUM_INTERVALS = 2;
	std::cout << "Using " << NUM_INTERVALS << " intervals for the integral of x^2 + 3.\n";
	Simpson_Points sp(0, 3, NUM_INTERVALS);
	Simpson_Sums<real> sums{0., 0., 0.};
	//std::cout << std::fixed;
	std::cout.precision(dbl::digits10);
	real result = simpson_rule<real>(quadratic_integrand, sp, sums);
	std::cout << "The integral of x^2 + 3 from x = 0 to x = 3 is " << (double)result << "\n";
	real actual = 18.0;
	std::cout << "Error:\t" << std::abs((double)(result - actual)) << "\n\n";
}

void test_gaussian() {
	const unsigned long long NUM_INTERVALS = 1 << 7;
	std::cout << "Using " << NUM_INTERVALS << " intervals for the integral of e^(-x^2).\n";
	Simpson_Points sp(-5, 5, NUM_INTERVALS);
	Simpson_Sums<real> sums{0., 0., 0.};
	//std::cout << std::fixed;
	std::cout.precision(dbl::digits10);
	real result = simpson_rule<real>(gaussian, sp, sums);
	std::cout << "The integral of e^(-x^2) from x = -5 to x = 5 is " << (double)result << "\n";
	real actual = 1.772453850902790950764921109937813548789156376909461997943865086066573890495904715920494455420022794;
	std::cout << "Error:\t" << std::abs((double)(result - actual)) << "\n\n";
}

void test_sqrt() {
	const unsigned long long NUM_INTERVALS = 1 << 8;
	std::cout << "Using " << NUM_INTERVALS << " intervals for the integral of sqrt(x).\n";
	Simpson_Points sp(1, 101, NUM_INTERVALS);
	Simpson_Sums<real> sums{0., 0., 0.};
	std::cout.precision(dbl::digits10);
	real result = simpson_rule<real>(sqrt_integrand, sp, sums);
	std::cout << "The integral of sqrt(x) from x = 1 to x = 101 is " << (double)result << "\n";
	real actual = 676.0249584888066115280971707924781299209649136484427375652;
	std::cout << "Error:\t" << std::abs((double)(result - actual)) << "\n\n";
}

int main() {
	test_quadratic();
	test_gaussian();
	test_sqrt();
	return 0;
}

