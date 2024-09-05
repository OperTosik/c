#ifdef CONVEX_HULL_H 
#define CONVEX_HULL_H

#include <vector>
#include "R2Graph.h"

void computeConvexHull (
    const std::vector<R2Point>& points,
    std::vector<R2Point>& polygon
);

#endif