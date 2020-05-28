#ifndef TUNL_RATIONAL_H
#define TUNL_RATIONAL_H
#include "algebraic_structure.h"
#include "integer.h"

namespace tunl {

class Rational : public Field<Rational> {
private:

public:
	Rational(const Integer numerator, const Integer denominator);
	Rational(const Integer n);
};

Rational operator*(const Rational& i, const Rational& r);

Rational operator*(const Integer& i, const Rational& r);
Rational operator*(const Rational& r, const Integer& i);

Rational operator/(const Integer& i, const Rational& r);
Rational operator/(const Rational& r, const Integer& i);

Rational operator/(const Integer& i, const Integer& r);
}
#endif
