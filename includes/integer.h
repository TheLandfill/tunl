#ifndef TUNL_INTEGER_H
#define TUNL_INTEGER_H
#include "algebraic_structure.h"

namespace tunl {

class Integer : public Ring<Integer> {
public:
	Integer add(const Integer& n) const;
	Integer & add_eq(const Integer& n);

	Integer neg() const;
	Integer sub(const Integer& n) const;
	Integer & sub_eq(const Integer& n);

	Integer mul(const Integer& n) const;
	Integer & mul_eq(const Integer& n);
public:
	Integer(const long long n);
};

Integer operator*(const Integer& i, const Integer& r);

}

#endif
