#ifndef REAL_H
#define REAL_H

#if defined(__GNUC__) || defined(__GNUG__)
typedef __float128 real;
#else
typedef long double real;
#endif

#endif
