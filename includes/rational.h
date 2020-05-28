#ifndef TUNL_RATIONAL_H
#define TUNL_RATIONAL_H
#include "number.h"
#include "integer.h"

namespace tunl {

class Rational : public Field<Rational> {
private:

public:
	Rational(const Integer numerator, const Integer denominator);
};

}
#endif
