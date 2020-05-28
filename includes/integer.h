#ifndef TUNL_INTEGER_H
#define TUNL_INTEGER_H
#include "algebraic_structure.h"
#include "real.h"

namespace tunl {

class Integer : public Ring<Integer> {

public:
	Integer(const long long n);
};

Integer operator*(const Integer& i, const Integer& r);

}

#endif
