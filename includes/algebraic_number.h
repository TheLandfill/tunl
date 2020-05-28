#ifndef TUNL_ALGEBRAIC_NUMBER_H
#define TUNL_ALGEBRAIC_NUMBER_H
#include "number.h"
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

}

#endif
