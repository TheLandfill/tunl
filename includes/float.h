#ifndef TUNL_FLOAT_H
#define TUNL_FLOAT_H
#include "algebraic_structure.h"
#include "algebraic_number.h"

namespace tunl {

class Floating_Point : public Field<Floating_Point> {
public:
	Floating_Point add(const Floating_Point& n) const;
	Floating_Point & add_eq(const Floating_Point& n);

	Floating_Point neg() const;
	Floating_Point sub(const Floating_Point& n) const;
	Floating_Point & sub_eq(const Floating_Point& n);

	Floating_Point mul(const Floating_Point& n) const;
	Floating_Point & mul_eq(const Floating_Point& n);

	Floating_Point div(const Floating_Point& n) const;
	Floating_Point & div_eq(const Floating_Point& n);
public:
	Floating_Point(const float n);
	Floating_Point(const double n);
	Floating_Point(const Integer n);
	Floating_Point(const Rational n);
	Floating_Point(const Algebraic n);
};

Floating_Point power(const Floating_Point& x, const Floating_Point& p);

}

#endif
