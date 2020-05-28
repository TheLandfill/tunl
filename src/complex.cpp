#include "complex.h"

using namespace tunl;

#define GEN_COMPLEX_ALG_SQR_MAG(TYPE) \
Algebraic Complex<TYPE>::square_magnitude() const {\
	return real * real + imag * imag;\
}

#define GEN_COMPLEX_ALG_MAG(TYPE) \
Algebraic Complex<TYPE>::magnitude() const {\
	return root(real * real + imag * imag, Rational(1, 2));\
}

#define GEN_COMPLEX_ALG_NORM(TYPE) \
Complex<Algebraic> Complex<TYPE>::normalized() const {\
	return Complex<Algebraic>{real, imag} / magnitude();\
}

#define GEN_COMPLEX_ALG_MAG_ALL(TYPE) \
GEN_COMPLEX_ALG_SQR_MAG(TYPE)\
\
GEN_COMPLEX_ALG_MAG(TYPE)\
\
GEN_COMPLEX_ALG_NORM(TYPE)
GEN_COMPLEX_ALG_SQR_MAG(Integer)

GEN_COMPLEX_ALG_MAG(Integer)

GEN_COMPLEX_ALG_NORM(Integer)

//GEN_COMPLEX_ALG_MAG_ALL(Integer)

Algebraic Complex<Integer>::square_magnitude() const {
	return real * real + imag * imag;
}

Algebraic Complex<Integer>::magnitude() const {
	return root(real * real + imag * imag, Rational(1, 2));
}

Complex<Algebraic> Complex<Integer>::normalized() const {\
	return Complex<Algebraic>{real, imag} / magnitude();\
}
