#ifndef TUNL_INTEGER_H
#define TUNL_INTEGER_H
#include "number.h"

namespace tunl {

class Integer : public Field<Integer> {

public:
	Integer(const long long n);
};

}

#endif
