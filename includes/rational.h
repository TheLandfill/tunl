#ifndef TUNL_RATIONAL_H
#define TUNL_RATIONAL_H
#include "algebraic_structure.h"
#include "integer.h"

namespace tunl {

class Rational : public Field<Rational> {
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
public:
	Rational(const Integer numerator, const Integer denominator);
	Rational(const Integer n);
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
