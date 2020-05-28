#ifndef TUNL_ALGEBRAIC_NUMBER_H
#define TUNL_ALGEBRAIC_NUMBER_H
#include "algebraic_structure.h"
#include "integer.h"
#include "rational.h"

namespace tunl {

class Algebraic : public Field<Algebraic> {
private:

public:
	Algebraic(const Integer n);
	Algebraic(const Rational n);
};

Algebraic root(const Algebraic& x, Rational r);

Algebraic operator*(const Rational& i, const Algebraic& r);
Algebraic operator*(const Algebraic& r, const Rational& i);

Algebraic operator/(const Rational& i, const Algebraic& r);
Algebraic operator/(const Algebraic& r, const Rational& i);

}

#endif
