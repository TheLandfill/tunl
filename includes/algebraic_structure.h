#ifndef TUNL_NUMBER_H
#define TUNL_NUMBER_H

namespace tunl {

template<typename T>
class Group {
public:
	T operator+(const T& n) const {
		return this->add(n);
	}
	T operator-(const T& n) const {
		return this->subtract(n);
	}
	T operator-() const {
		return this->invert();
	}
	T & operator+=(const T& n) {
		return this->add_eq(n);
	}
	T & operator-=(const T& n) {
		return this->subtract_eq(n);
	}
};

template<typename T>
class Ring : public Group<T> {
public:
	T operator*(const T& n) const {
		return this->multiply(n);
	}
	T & operator*=(const T& n) {
		return this->multiply_eq(n);
	}
};

template<typename T>
class Field : public Ring<T> {
public:
	T operator/(const T& n) const {
		return this->divide(n);
	}
	T & operator/=(const T& n) {
		return this->divide_eq(n);
	}
};

}
#endif
