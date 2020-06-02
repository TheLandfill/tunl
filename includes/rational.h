#ifndef TUNL_RATIONAL_H
#define TUNL_RATIONAL_H
#include "algebraic_structure.h"
#include "integer.h"

#include <string>

namespace tunl {

class Rational :
	public Field<Rational>,
	public Comparable<Rational>
{
public:
	Rational add(const Rational& n) const;
	Rational & add_eq(const Rational& n);

	Rational neg() const;
	Rational sub(const Rational& n) const;
	Rational & sub_eq(const Rational& n);

	Rational mul(const Rational& n) const;
	Rational & mul_eq(const Rational& n);

	Rational div(const Rational& n) const;
	Rational & div_eq(const Rational& n);

	bool equals(const Rational& n) const;
	bool less_than(const Rational& n) const;
public:
	Rational(const Integer numerator, const Integer denominator);
	Rational(const Integer n);

	operator std::string();
};

Rational operator*(const Rational& i, const Rational& r);
Rational operator/(const Rational& i, const Rational& r);

Rational operator*(const Integer& i, const Rational& r);
Rational operator*(const Rational& r, const Integer& i);

Rational operator/(const Integer& i, const Rational& r);
Rational operator/(const Rational& r, const Integer& i);

Rational operator/(const Integer& i, const Integer& r);
}
#endif
