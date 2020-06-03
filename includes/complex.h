#ifndef TUNL_COMPLEX_H
#define TUNL_COMPLEX_H
#include "algebraic_number.h"
#include "rational.h"
#include "float.h"
#include "integer.h"
#include "algebraic_structure.h"

#include <string>
#include <utility>

namespace tunl {

template<typename T> class Complex;

template<typename T>
class Complex_Base {
public:
	Complex<T> add(const Complex<T>& n) const;
	Complex<T> sub(const Complex<T>& n) const;
	Complex<T> mul(const Complex<T>& n) const;

	Complex<T> & add_eq(const Complex<T>& n);
	Complex<T> & sub_eq(const Complex<T>& n);
	Complex<T> & mul_eq(const Complex<T>& n);
public:
	T real, imag;
	bool use_j;
	Complex_Base(const T real, const T imag, const bool use_j = false);

	Complex<T> conj() const;
	Complex<T> neg() const;

	operator std::string();
};

template<typename T>
Complex<T> Complex_Base<T>::add(const Complex<T>& n) const {
	return Complex<T>{
		this->real + n.real,
		this->imag + n.imag
	};
}

template<typename T>
Complex<T> Complex_Base<T>::sub(const Complex<T>& n) const {
	return Complex<T>{
		this->real - n.real,
		this->imag - n.imag
	};
}

template<typename T>
Complex<T> Complex_Base<T>::mul(const Complex<T>& n) const {
	return Complex<T>{
		this->real * n.real - this->imag * n.imag,
		this->real * n.imag + this->imag * n.real
	};
}

template<typename T>
Complex<T>& Complex_Base<T>::add_eq(const Complex<T>& n) {
	this->real += n.real;
	this->imag += n.imag;
	return *static_cast<Complex<T>*>(this);
}

template<typename T>
Complex<T>& Complex_Base<T>::sub_eq(const Complex<T>& n) {
	this->real -= n.real;
	this->imag -= n.imag;
	return *static_cast<Complex<T>*>(this);
}

template<typename T>
Complex<T>& Complex_Base<T>::mul_eq(const Complex<T>& n) {
	T temp_real = std::move(this->real);
	this->real = temp_real * n.real - this->imag * n.imag;
	this->imag = temp_real * n.imag + this->imag * n.real;
	return *static_cast<Complex<T>*>(this);
}

template<typename T>
Complex_Base<T>::Complex_Base(const T r, const T i, bool use_j) : real(r), imag(i), use_j(use_j) {}

template<typename T>
Complex<T> Complex_Base<T>::conj() const {
	return Complex<T>(this->real, -this->imag);
}

template<typename T>
Complex<T> Complex_Base<T>::neg() const {
	return Complex<T>(-this->real, -this->imag);
}

template<typename T>
Complex_Base<T>::operator std::string() {
	char sign[] = " + ";
	char imaginary_unit = 'i' + use_j;
	if (imag < T(0)) {
		sign[1] = '-';
	}
	return std::string(real) + sign + std::string(imag) + imaginary_unit;
}

template<typename T>
class Complex : public Complex_Base<T> {
public:
	Complex(const T real, const T imag, const bool use_j = false);
	Complex(const Complex_Base<T>& c);
	Complex(const Complex_Base<T> c);
};

template<typename T>
Complex<T>::Complex(const T r, const T i, const bool use_j) : Complex_Base<T>(r, i, use_j) {}

template<typename T>
Complex<T>::Complex(const Complex_Base<T>& c) : Complex_Base<T>(c.real, c.imag, c.use_j) {}

template<typename T>
Complex<T>::Complex(const Complex_Base<T> c) : Complex_Base<T>(c.real, c.imag, c.use_j) {}

////////////////////////////////////////////////////////////////////////////////
//                         Template Specializations                           //
////////////////////////////////////////////////////////////////////////////////

template<> class Complex<Integer> :
	public Complex_Base<Integer>,
	public Ring<Complex<Integer>>
{
public:
	Complex(const Integer real, const Integer imag = 0, const bool use_j = false);

	Integer square_magnitude() const;
	Algebraic magnitude() const;
	Complex<Algebraic> normalized() const;

	Complex<Integer>& operator*=(const Integer& n);
};

Complex<Integer> operator*(const Complex<Integer>& c, const Integer& n);
Complex<Integer> operator*(const Integer& n, const Complex<Integer>& c);
Complex<Rational> operator/(const Complex<Integer>& c, const Integer& n);
Complex<Rational> operator/(const Complex<Integer>& numerator, const Complex<Integer>& denominator);

Complex<Rational> operator+(const Complex<Rational>& c, const Rational& n);
Complex<Rational> operator-(const Complex<Rational>& c, const Rational& n);
Complex<Algebraic> operator+(const Complex<Algebraic>& c, const Algebraic& n);
Complex<Algebraic> operator-(const Complex<Algebraic>& c, const Algebraic& n);

template<> class Complex<Rational> :
	public Complex_Base<Rational>,
	public Field<Complex<Rational>>
{
public:
	Complex<Rational> div(const Complex<Rational>& n) const;
	void divide_eq(const Complex<Rational>& n) const;
public:
	Complex(const Rational real, const Rational imag = Rational(0, 1), const bool use_j = false);
	Complex(const Complex<Integer> c);

	Rational square_magnitude() const;
	Algebraic magnitude() const;
	Complex<Algebraic> normalized() const;

	Complex<Rational>& operator*=(const Rational& n);
	Complex<Rational>& operator/=(const Rational& n);
};

Complex<Rational> operator*(const Complex<Rational>& c, const Rational& n);
Complex<Rational> operator/(const Complex<Rational>& c, const Rational& n);
Complex<Rational> operator*(const Rational& n, const Complex<Rational>& c);
Complex<Rational> operator/(const Rational& n, const Complex<Rational>& c);

template<> class Complex<Algebraic> :
	public Complex_Base<Algebraic>,
	public Field<Complex<Algebraic>>
{
public:
	Complex<Algebraic> div(const Complex<Algebraic>& n) const;
	void divide_eq(const Complex<Algebraic>& n) const;
public:
	Complex(const Algebraic real, const Algebraic imag, const bool use_j = false);
	Complex(const Complex<Integer> c);
	Complex(const Complex<Rational> c);

	Algebraic square_magnitude() const;
	Algebraic magnitude() const;
	Complex<Algebraic> normalized() const;

	Complex<Algebraic>& normalize();

	Complex<Algebraic>& operator*=(const Algebraic& n);
	Complex<Algebraic>& operator/=(const Algebraic& n);
};

Complex<Algebraic> operator*(const Complex<Algebraic>& c, const Algebraic& n);
Complex<Algebraic> operator/(const Complex<Algebraic>& c, const Algebraic& n);
Complex<Algebraic> operator*(const Algebraic& n, const Complex<Algebraic>& c);
Complex<Algebraic> operator/(const Algebraic& n, const Complex<Algebraic>& c);

template<> class Complex<Floating_Point> :
	public Complex_Base<Floating_Point>,
	public Field<Complex<Floating_Point>>
{
public:
	Complex<Floating_Point> div(const Complex<Floating_Point>& n) const;
	void divide_eq(const Complex<Floating_Point>& n) const;
public:
	Complex(const Floating_Point real, const Floating_Point imag, const bool use_j = false);
	Complex(const Complex<Integer> c);
	Complex(const Complex<Rational> c);
	Complex(const Complex<Algebraic> c);

	Floating_Point magnitude() const;
	Floating_Point square_magnitude() const;
	Complex<Floating_Point> normalized() const;
	Complex<Floating_Point>& normalize();

	Complex<Floating_Point>& operator*=(const Floating_Point& n);
	Complex<Floating_Point>& operator/=(const Floating_Point& n);
};

Complex<Floating_Point> operator*(const Complex<Floating_Point>& c, const Floating_Point& n);
Complex<Floating_Point> operator/(const Complex<Floating_Point>& c, const Floating_Point& n);
Complex<Floating_Point> operator*(const Floating_Point& n, const Complex<Floating_Point>& c);
Complex<Floating_Point> operator/(const Floating_Point& n, const Complex<Floating_Point>& c);

}
#endif
