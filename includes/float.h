#ifndef TUNL_FLOAT_H
#define TUNL_FLOAT_H
#include "algebraic_structure.h"
#include "algebraic_number.h"

namespace tunl {

class Floating_Point : public Field<Floating_Point> {
private:

public:
	Floating_Point(const float n);
	Floating_Point(const double n);
	Floating_Point(const Integer n);
	Floating_Point(const Rational n);
	Floating_Point(const Algebraic n);
};

}

#endif
