#ifndef REAL_H
#define REAL_H

namespace tunl {

#if defined(__GNUC__) || defined(__GNUG__)
typedef __float128 builtin_real;
#else
typedef long double builtin_real;
#endif

}
#endif
