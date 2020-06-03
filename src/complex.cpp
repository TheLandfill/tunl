#include "complex.h"

namespace tunl {

////////////////////////////////////////////////////////////////////////////////
//                     Complex Constructor and Conversion                     //
////////////////////////////////////////////////////////////////////////////////

#define GEN_COMPLEX_CONSTRUCTOR(TYPE)\
Complex<TYPE>::Complex(const TYPE r, const TYPE i, const bool use_j) :\
	Complex_Base<TYPE>(r, i, use_j) {}

#define GEN_COMPLEX_CONVERSION(TYPE1, TYPE2)\
Complex<TYPE1>::Complex(const Complex<TYPE2> c) :\
	Complex<TYPE1>(c.real, c.imag) {}\

////////////////////////////////////////////////////////////////////////////////
//                   Complex Algebraic Magnitude Operations                   //
////////////////////////////////////////////////////////////////////////////////

#define GEN_COMPLEX_SQR_MAG(TYPE) \
TYPE Complex<TYPE>::square_magnitude() const {\
	return real * real + imag * imag;\
}

#define GEN_COMPLEX_ALG_MAG(TYPE) \
Algebraic Complex<TYPE>::magnitude() const {\
	return power(square_magnitude(), Rational(1, 2));\
}

#define GEN_COMPLEX_ALG_NORM(TYPE) \
Complex<Algebraic> Complex<TYPE>::normalized() const {\
	return Complex<Algebraic>{real, imag} / magnitude();\
}

#define GEN_COMPLEX_ALG_ALL(TYPE) \
GEN_COMPLEX_SQR_MAG(TYPE)\
\
GEN_COMPLEX_ALG_MAG(TYPE)\
\
GEN_COMPLEX_ALG_NORM(TYPE)\

////////////////////////////////////////////////////////////////////////////////
//                Real and Complex Multiplication and Division                //
////////////////////////////////////////////////////////////////////////////////

#define GEN_COMPLEX_MUL(TYPE)\
Complex<TYPE> operator*(const Complex<TYPE>&c, const TYPE& n) {\
	return Complex<TYPE>(c.real * n, c.imag * n);\
}\
\
Complex<TYPE> operator*(const TYPE& n, const Complex<TYPE>& c) {\
	return c * n;\
}\

#define GEN_COMPLEX_MUL_EQ(TYPE)\
Complex<TYPE>& Complex<TYPE>::operator*=(const TYPE& n) {\
	this->real *= n;\
	this->imag *= n;\
	return *this;\
}\

#define GEN_COMPLEX_DIV(TYPE)\
Complex<TYPE> operator/(const Complex<TYPE>& c, const TYPE& n) {\
	return Complex<TYPE>(c.real / n, c.imag / n);\
}\
\
Complex<TYPE> operator/(const TYPE& n, const Complex<TYPE>& c) {\
	return n * c.conj() / c.square_magnitude();\
}\

#define GEN_COMPLEX_DIV_EQ(TYPE)\
Complex<TYPE>& Complex<TYPE>::operator/=(const TYPE& n) {\
	this->real /= n;\
	this->imag /= n;\
	return *this;\
}\

////////////////////////////////////////////////////////////////////////////////
//                                normalize()                                 //
////////////////////////////////////////////////////////////////////////////////

#define GEN_NORMALIZE(TYPE)\
Complex<TYPE>& Complex<TYPE>::normalize() {\
	TYPE mag = magnitude();\
	this->real /= mag;\
	this->imag /= mag;\
	return *this;\
}\


////////////////////////////////////////////////////////////////////////////////
//                          Integer Specializations                           //
////////////////////////////////////////////////////////////////////////////////

GEN_COMPLEX_CONSTRUCTOR(Integer)
GEN_COMPLEX_MUL(Integer)
GEN_COMPLEX_MUL_EQ(Integer)

GEN_COMPLEX_ALG_ALL(Integer)

Complex<Rational> operator/(const Complex<Integer>& c, const Integer& n) {
	return Complex<Rational>(c.real / n, c.imag / n);
}

Complex<Rational> operator/(const Complex<Integer>& numerator, const Complex<Integer>& denominator) {
	return numerator * denominator.conj() / denominator.square_magnitude();
}

////////////////////////////////////////////////////////////////////////////////
//                         Rational Specializations                           //
////////////////////////////////////////////////////////////////////////////////

GEN_COMPLEX_CONSTRUCTOR(Rational)
GEN_COMPLEX_CONVERSION(Rational, Integer)

GEN_COMPLEX_ALG_ALL(Rational)

GEN_COMPLEX_MUL(Rational)
GEN_COMPLEX_DIV(Rational)
GEN_COMPLEX_MUL_EQ(Rational)
GEN_COMPLEX_DIV_EQ(Rational)

////////////////////////////////////////////////////////////////////////////////
//                        Algebraic Specializations                           //
////////////////////////////////////////////////////////////////////////////////

GEN_COMPLEX_CONSTRUCTOR(Algebraic)
GEN_COMPLEX_CONVERSION(Algebraic, Integer)
GEN_COMPLEX_CONVERSION(Algebraic, Rational)

GEN_COMPLEX_ALG_ALL(Algebraic)

GEN_NORMALIZE(Algebraic)

GEN_COMPLEX_MUL(Algebraic)
GEN_COMPLEX_DIV(Algebraic)
GEN_COMPLEX_MUL_EQ(Algebraic)
GEN_COMPLEX_DIV_EQ(Algebraic)

////////////////////////////////////////////////////////////////////////////////
//                      Floating Point Specializations                        //
////////////////////////////////////////////////////////////////////////////////

GEN_COMPLEX_CONSTRUCTOR(Floating_Point)
GEN_COMPLEX_CONVERSION(Floating_Point, Integer)
GEN_COMPLEX_CONVERSION(Floating_Point, Rational)
GEN_COMPLEX_CONVERSION(Floating_Point, Algebraic)

GEN_COMPLEX_SQR_MAG(Floating_Point)

Floating_Point Complex<Floating_Point>::magnitude() const {
	return power(square_magnitude(), 0.5);
}

Complex<Floating_Point> Complex<Floating_Point>::normalized() const {
	return *this / magnitude();
}

GEN_NORMALIZE(Floating_Point)

GEN_COMPLEX_MUL(Floating_Point)
GEN_COMPLEX_DIV(Floating_Point)
GEN_COMPLEX_MUL_EQ(Floating_Point)
GEN_COMPLEX_DIV_EQ(Floating_Point)

}
