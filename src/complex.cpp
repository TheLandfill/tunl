#include "complex.h"

namespace tunl {

#define GEN_COMPLEX_ALG_SQR_MAG(TYPE) \
TYPE Complex<TYPE>::square_magnitude() const {\
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

#define GEN_COMPLEX_CONSTRUCTOR(TYPE)\
Complex<TYPE>::Complex(const TYPE r, const TYPE i) : Complex_Base<TYPE>(r, i) {}

#define GEN_COMPLEX_ALG_ALL(TYPE) \
GEN_COMPLEX_ALG_SQR_MAG(TYPE)\
\
GEN_COMPLEX_ALG_MAG(TYPE)\
\
GEN_COMPLEX_ALG_NORM(TYPE)\

GEN_COMPLEX_ALG_ALL(Integer)
GEN_COMPLEX_ALG_ALL(Rational)
GEN_COMPLEX_ALG_ALL(Algebraic)

Complex<Integer>& Complex<Integer>::operator*=(const Integer& n){
	this->real *= n;
	this->imag *= n;
	return *this;
}

Complex<Integer> operator*(const Complex<Integer>& c, const Integer& n) {
	return Complex<Integer>(c.real * n, c.imag * n);
}

Complex<Integer> operator*(const Integer& n, const Complex<Integer>& c) {
	return c * n;
}

Complex<Rational> operator*(const Complex<Integer>& c, const Rational& n){
	return Complex<Rational>(c.real * n, c.imag * n);
}

Complex<Rational> operator*(const Rational& n, const Complex<Integer>& c){
	return c * n;
}

Complex<Rational> operator/(const Complex<Integer>& c, const Integer& n) {
	return Complex<Rational>(c.real / n, c.imag / n);
}

Complex<Rational> operator/(const Complex<Integer>& numerator, const Complex<Integer>& denominator) {
	return numerator * denominator.conj() / denominator.square_magnitude();
}



Complex<Rational> operator*(const Complex<Rational>& c, const Rational& n) {
	return Complex<Rational>(c.real * n, c.imag * n);
}

Complex<Rational> operator/(const Complex<Rational>& c, const Rational& n) {
	return Complex<Rational>(c.real / n, c.imag / n);
}

Complex<Rational> operator*(const Rational& n, const Complex<Rational>& c) {
	return c * n;
}

Complex<Rational> operator/(const Rational& n, const Complex<Rational>& c) {
	return n * c.conj() / c.square_magnitude();
}


Complex<Algebraic> operator*(const Complex<Algebraic>& c, const Algebraic& n) {
	return Complex<Algebraic>(c.real * n, c.imag * n);
}

Complex<Algebraic> operator/(const Complex<Algebraic>& c, const Algebraic& n) {
	return Complex<Algebraic>(c.real / n, c.imag / n);
}

Complex<Algebraic> operator*(const Algebraic& n, const Complex<Algebraic>& c) {
	return c * n;
}

Complex<Algebraic> operator/(const Algebraic& n, const Complex<Algebraic>& c) {
	return n * c.conj() / c.square_magnitude();
}

}
