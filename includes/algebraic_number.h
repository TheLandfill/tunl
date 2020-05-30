#ifndef TUNL_ALGEBRAIC_NUMBER_H
#define TUNL_ALGEBRAIC_NUMBER_H
#include "algebraic_structure.h"
#include "integer.h"
#include "rational.h"

namespace tunl {

class Algebraic : public Field<Algebraic> {
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
public:
	Algebraic(const Integer n);
	Algebraic(const Rational n);
};

Algebraic power(const Algebraic& x, Rational r);

Algebraic operator*(const Rational& i, const Algebraic& r);
Algebraic operator*(const Algebraic& r, const Rational& i);

Algebraic operator/(const Rational& i, const Algebraic& r);
Algebraic operator/(const Algebraic& r, const Rational& i);

}

#endif
