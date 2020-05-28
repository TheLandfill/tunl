#ifndef TUNL_COMPLEX_H
#define TUNL_COMPLEX_H
#include "algebraic_number.h"
#include "rational.h"
#include "float.h"
#include "integer.h"
#include "number.h"

#include <utility>

namespace tunl {

template<typename T>
struct Complex_Pair {
private:
	Complex_Pair();
public:
	T real, imag;
};

template<typename T>
class Complex : public Ring<Complex<T>>, Complex_Pair<T> {
private:
	Complex<T> add(const Complex<T>& n) const;
	Complex<T> subtract(const Complex<T>& n) const;
	Complex<T> multiply(const Complex<T>& n) const;

	Complex<T> & add_eq(const Complex<T>& n);
	Complex<T> & subtract_eq(const Complex<T>& n);
	Complex<T> & multiply_eq(const Complex<T>& n);
};

template<typename T>
Complex<T> Complex<T>::add(const Complex<T>& n) const {
	return Complex<T>{
		this->real + n.real,
		this->imag + n.imag
	};
}

template<typename T>
Complex<T> Complex<T>::subtract(const Complex<T>& n) const {
	return Complex<T>{
		this->real - n.real,
		this->imag - n.imag
	};
}

template<typename T>
Complex<T> Complex<T>::multiply(const Complex<T>& n) const {
	return Complex<T>{
		this->real * n.real - this->imag * n.imag,
		this->real * n.imag + this->imag * n.real
	};
}

template<typename T>
Complex<T>& Complex<T>::add_eq(const Complex<T>& n) {
	this->real += n.real;
	this->imag += n.imag;
	return *this;
}

template<typename T>
Complex<T>& Complex<T>::subtract_eq(const Complex<T>& n) {
	this->real -= n.real;
	this->imag -= n.imag;
	return *this;
}

template<typename T>
Complex<T>& Complex<T>::multiply_eq(const Complex<T>& n) {
	T temp_real = std::move(this->real);
	this->real = temp_real * n.real - this->imag * n.imag;
	this->imag = temp_real * n.imag + this->imag * n.real;
	return *this;
}

////////////////////////////////////////////////////////////////////////////////
//                         Template Specializations                           //
////////////////////////////////////////////////////////////////////////////////

class Complex_Algebraic_Magnitude {
public:
	Algebraic square_magnitude() const;
	Algebraic magnitude() const;
	Complex<Algebraic> normalized() const;
};

template<> class Complex<Integer> : public Ring<Complex<Integer>>, Complex_Algebraic_Magnitude, Complex_Pair<Integer> {
public:
//	Algebraic square_magnitude() const;
//	Algebraic magnitude() const;
//	Complex<Algebraic> normalized() const;
	Complex<Rational> operator/(const Complex<Integer>& n) const;
};

template<> class Complex<Rational> : public Field<Complex<Rational>>, Complex_Algebraic_Magnitude {
private:
	Complex<Rational> divide(const Complex<Rational>& n) const;
	void divide_eq(const Complex<Rational>& n) const;
};

template<> class Complex<Algebraic> : public Field<Complex<Algebraic>>, Complex_Algebraic_Magnitude {
private:
	Complex<Algebraic> divide(const Complex<Algebraic>& n) const;
	void divide_eq(const Complex<Algebraic>& n) const;
public:
	void normalize();
};

template<> class Complex<Floating_Point> : public Field<Complex<Floating_Point>> {
private:
	Complex<Floating_Point> divide(const Complex<Floating_Point>& n) const;
	void divide_eq(const Complex<Floating_Point>& n) const;
public:
	virtual Floating_Point magnitude() const = 0;
	virtual Floating_Point square_magnitude() const = 0;
	virtual Complex<Floating_Point> normalized() const = 0;
	void normalize();
};

}
#endif
