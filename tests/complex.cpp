#include "complex.h"
#include <iostream>

using namespace tunl;

void test_initialization() {
	Complex<Integer> int_test(7, 3);
	std::cout << std::string(int_test) << "\n";
	Complex<Rational> rational_test(Rational(1, 2), Rational(3, 4));
	std::cout << std::string(rational_test) << "\n";
	Complex<Algebraic> algebraic_test(Rational(1, 2), power(Algebraic(12), Rational(7, 3)));
	std::cout << std::string(algebraic_test) << "\n";
	Complex<Floating_Point> floating_point_test(power(0.5, 0.5), 0.7);
	std::cout << std::string(floating_point_test) << "\n";
}

#define COMPLEX_OPS(TYPE)\
	auto TYPE##_add = TYPE##_test_a + TYPE##_test_b;\
	auto TYPE##_sub = TYPE##_test_a - TYPE##_test_b;\
	auto TYPE##_mul = TYPE##_test_a * TYPE##_test_b;\
	auto TYPE##_div = TYPE##_test_a / TYPE##_test_b;\
	std::cout << std::string(TYPE##_add) << "\n";\
	std::cout << std::string(TYPE##_sub) << "\n";\
	std::cout << std::string(TYPE##_mul) << "\n";\
	std::cout << std::string(TYPE##_div) << "\n";\


void test_complex_operations() {
	Complex<Integer> int_test_a(3, 4);
	Complex<Integer> int_test_b(5, 12);
	Complex<Rational> rational_test_a(Rational(3, 5), Rational(4, 5));
	Complex<Rational> rational_test_b(Rational(5, 13), Rational(12, 13));
	Complex<Algebraic> algebraic_test_a(Rational(1, 2), power(Algebraic(2), Rational(7, 3)));
	Complex<Algebraic> algebraic_test_b(power(Rational(1, 2), Rational(1, 2)),
		power(Algebraic(12), Rational(7, 3)));
	Complex<Floating_Point> floating_point_test_a(power(0.5, 0.5), power(0.5, 0.5));
	Complex<Floating_Point> floating_point_test_b(power(0.5, 0.5), 0.7);

	std::cout << std::string(int_test_a) << "\n";
	std::cout << std::string(int_test_b) << "\n";
	std::cout << std::string(rational_test_a) << "\n";
	std::cout << std::string(rational_test_b) << "\n";
	std::cout << std::string(algebraic_test_a) << "\n";
	std::cout << std::string(algebraic_test_b) << "\n";
	std::cout << std::string(floating_point_test_a) << "\n";
	std::cout << std::string(floating_point_test_b) << "\n";

	COMPLEX_OPS(int)
	COMPLEX_OPS(rational)
	COMPLEX_OPS(algebraic)
	COMPLEX_OPS(floating_point)
}

void test_real_operations() {
	Complex<Integer> int_test(3, 4);
	std::cout << std::string(int_test) << "\n";
	int_test += Integer(5);
	std::cout << std::string(int_test) << "\n";
	auto rational_addition = int_test + Rational(7, 4);
	std::cout << std::string(rational_addition) << "\n";
}
