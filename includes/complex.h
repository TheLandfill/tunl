#ifndef TUNL_COMPLEX_H
#define TUNL_COMPLEX_H
#include "algebraic_number.h"
#include "rational.h"
#include "float.h"
#include "integer.h"
#include "algebraic_structure.h"

#include <utility>

namespace tunl {

template<typename T> class Complex;

template<typename T>
class Complex_Base : public Ring<Complex<T>> {
private:
	Complex<T> add(const Complex<T>& n) const;
	Complex<T> subtract(const Complex<T>& n) const;
	Complex<T> multiply(const Complex<T>& n) const;

	Complex<T> & add_eq(const Complex<T>& n);
	Complex<T> & subtract_eq(const Complex<T>& n);
	Complex<T> & multiply_eq(const Complex<T>& n);
public:
	T real, imag;
	Complex_Base(T real, T imag);

	Complex<T> conj() const;
	Complex<T> operator-() const;
};

template<typename T>
Complex<T> Complex_Base<T>::add(const Complex<T>& n) const {
	return Complex<T>{
		this->real + n.real,
		this->imag + n.imag
	};
}

template<typename T>
Complex<T> Complex_Base<T>::subtract(const Complex<T>& n) const {
	return Complex<T>{
		this->real - n.real,
		this->imag - n.imag
	};
}

template<typename T>
Complex<T> Complex_Base<T>::multiply(const Complex<T>& n) const {
	return Complex<T>{
		this->real * n.real - this->imag * n.imag,
		this->real * n.imag + this->imag * n.real
	};
}

template<typename T>
Complex<T>& Complex_Base<T>::add_eq(const Complex<T>& n) {
	this->real += n.real;
	this->imag += n.imag;
	return *this;
}

template<typename T>
Complex<T>& Complex_Base<T>::subtract_eq(const Complex<T>& n) {
	this->real -= n.real;
	this->imag -= n.imag;
	return *this;
}

template<typename T>
Complex<T>& Complex_Base<T>::multiply_eq(const Complex<T>& n) {
	T temp_real = std::move(this->real);
	this->real = temp_real * n.real - this->imag * n.imag;
	this->imag = temp_real * n.imag + this->imag * n.real;
	return *this;
}

template<typename T>
Complex_Base<T>::Complex_Base(T r, T i) : real(r), imag(i) {}

template<typename T>
Complex<T> Complex_Base<T>::conj() const {
	return Complex<T>(this->real, -this->imag);
}

template<typename T>
Complex<T> Complex_Base<T>::operator-() const {
	return Complex<T>(-this->real, -this->imag);
}

template<typename T>
class Complex : public Complex_Base<T> {
public:
	Complex(const T real, const T imag);
	Complex(const Complex_Base<T>& c);
	Complex(Complex_Base<T> c);
};

template<typename T>
Complex<T>::Complex(const T r, const T i) : Complex_Base<T>(r, i) {}

template<typename T>
Complex<T>::Complex(const Complex_Base<T>& c) : Complex_Base<T>(c.real, c.imag) {}

template<typename T>
Complex<T>::Complex(Complex_Base<T> c) : Complex_Base<T>(c.real, c.imag) {}

////////////////////////////////////////////////////////////////////////////////
//                         Template Specializations                           //
////////////////////////////////////////////////////////////////////////////////

template<> class Complex<Integer> : public Complex_Base<Integer> {
public:
	Complex(const Integer real, const Integer imag);

	Integer square_magnitude() const;
	Algebraic magnitude() const;
	Complex<Algebraic> normalized() const;

	Complex<Integer>& operator*=(const Integer& n);
};

Complex<Integer> operator*(const Complex<Integer>& c, const Integer& n);
Complex<Integer> operator*(const Integer& n, const Complex<Integer>& c);

Complex<Rational> operator/(const Complex<Integer>& c, const Integer& n);

Complex<Rational> operator*(const Complex<Integer>& c, const Rational& n);
Complex<Rational> operator*(const Rational& n, const Complex<Integer>& c);
Complex<Rational> operator/(const Complex<Integer>& c, const Rational& n);

Complex<Algebraic> operator*(const Complex<Integer>& c, const Algebraic& n);
Complex<Algebraic> operator/(const Complex<Integer>& c, const Algebraic& n);

Complex<Rational> operator/(const Complex<Integer>& numerator, const Complex<Integer>& denominator);

template<> class Complex<Rational> : public Complex_Base<Rational>, Field<Complex<Rational>> {
private:
	Complex<Rational> divide(const Complex<Rational>& n) const;
	void divide_eq(const Complex<Rational>& n) const;
public:
	Complex(const Rational real, const Rational imag);

	Rational square_magnitude() const;
	Algebraic magnitude() const;
	Complex<Algebraic> normalized() const;

	void operator*=(const Rational& n);
	void operator/=(const Rational& n);

	Complex<Rational> operator*(const Rational& n) const;
	Complex<Rational> operator/(const Rational& n) const;

	Complex<Algebraic> operator*(const Algebraic& n) const;
	Complex<Algebraic> operator/(const Algebraic& n) const;
};

template<> class Complex<Algebraic> : public Complex_Base<Algebraic>, Field<Complex<Algebraic>> {
private:
	Complex<Algebraic> divide(const Complex<Algebraic>& n) const;
	void divide_eq(const Complex<Algebraic>& n) const;
public:
	Complex(const Algebraic real, const Algebraic imag);

	Algebraic square_magnitude() const;
	Algebraic magnitude() const;
	Complex<Algebraic> normalized() const;

	void normalize();

	void operator*=(const Algebraic& n);
	void operator/=(const Algebraic& n);
};

Complex<Algebraic> operator*(const Complex<Algebraic>& c, const Algebraic& n);
Complex<Algebraic> operator/(const Complex<Algebraic>& c, const Algebraic& n);

template<> class Complex<Floating_Point> : public Field<Complex<Floating_Point>> {
public:
	Floating_Point real, imag;
private:
	Complex<Floating_Point> divide(const Complex<Floating_Point>& n) const;
	void divide_eq(const Complex<Floating_Point>& n) const;
public:
	Complex(Floating_Point real, Floating_Point imag);

	Floating_Point magnitude() const;
	Floating_Point square_magnitude() const;
	Complex<Floating_Point> normalized() const;
	void normalize();
};

}
#endif
