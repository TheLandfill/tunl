#include "integration.h"
#include "real.h"

namespace tunl {

Simpson_Points::Simpson_Points(builtin_real a, builtin_real b, size_t n) :
start(a),
dx((b - a)/((builtin_real)n)),
n(n) {}

}
