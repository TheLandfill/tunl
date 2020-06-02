#ifndef TUNL_NUMBER_H
#define TUNL_NUMBER_H

namespace tunl {

template<typename T>
class Group {
public:
	T operator+(const T& n) const {
		return static_cast<const T*>(this)->add(n);
	}
	T operator-(const T& n) const {
		return static_cast<const T*>(this)->sub(n);
	}
	T operator-() const {
		return static_cast<const T*>(this)->neg();
	}
	T & operator+=(const T& n) {
		return static_cast<T*>(this)->add_eq(n);
	}
	T & operator-=(const T& n) {
		return static_cast<T*>(this)->sub_eq(n);
	}
};

template<typename T>
class Ring : public Group<T> {
public:
	T operator*(const T& n) const {
		return static_cast<const T*>(this)->mul(n);
	}
	T & operator*=(const T& n) {
		return static_cast<T*>(this)->mul_eq(n);
	}
};

template<typename T>
class Field : public Ring<T> {
public:
	T operator/(const T& n) const {
		return static_cast<const T*>(this)->div(n);
	}
	T & operator/=(const T& n) {
		return static_cast<T*>(this)->div_eq(n);
	}
};

template<typename T>
class Comparable {
public:
	bool operator==(const T& n) const {
		return static_cast<const T*>(this)->equals(n);
	}

	bool operator!=(const T& n) const {
		return !(*this == n);
	}

	bool operator<(const T& n) const {
		return static_cast<const T*>(this)->less_than(n);
	}

	bool operator>(const T& n) const {
		return !(*this < n || *this == n);
	}

	bool operator<=(const T& n) const {
		return (*this < n || *this == n);
	}

	bool operator>=(const T& n) const {
		return !(*this < n);
	}
};

}
#endif
