#include "utils.h"
#include "utils.hpp"

#include <cmath>

int grid_round(float n) {
    int dec = int(floorf(n * 10)) % 10;
    if (dec < 5) {
        return int(floorf(n));
    }
    return int(ceilf(n));
}

PointI grid_round(const PointF& p) {
    return PointI(grid_round(p.x()), grid_round(p.y()));
}
