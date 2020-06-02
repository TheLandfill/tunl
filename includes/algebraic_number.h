#ifndef TUNL_ALGEBRAIC_NUMBER_H
#define TUNL_ALGEBRAIC_NUMBER_H
#include "algebraic_structure.h"
#include "integer.h"
#include "rational.h"

#include <string>

namespace tunl {

class Algebraic :
	public Field<Algebraic>,
	public Comparable<Algebraic>
{
public:
	Algebraic add(const Algebraic& n) const;
	Algebraic & add_eq(const Algebraic& n);

	Algebraic neg() const;
	Algebraic sub(const Algebraic& n) const;
	Algebraic & sub_eq(const Algebraic& n);

	Algebraic mul(const Algebraic& n) const;
	Algebraic & mul_eq(const Algebraic& n);

	Algebraic div(const Algebraic& n) const;
	Algebraic & div_eq(const Algebraic& n);

	bool equals(const Algebraic& n) const;
	bool less_than(const Algebraic& n) const;
public:
	Algebraic(const Integer n);
	Algebraic(const Rational n);

	operator std::string();
};

Algebraic power(const Algebraic& x, Rational r);

Algebraic operator*(const Rational& i, const Algebraic& r);
Algebraic operator*(const Algebraic& r, const Rational& i);

Algebraic operator/(const Rational& i, const Algebraic& r);
Algebraic operator/(const Algebraic& r, const Rational& i);

}

#endif
