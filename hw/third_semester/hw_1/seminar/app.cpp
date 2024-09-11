#include "R3Graph.h"

R3Graph::R3Vector radiusVector(double lat, double lon);
// void getAxis(R3Graph::R3Vector v, R3Graph::R3Vector& axisX, R3Graph::R3Vector& axisY);
void earth2map(
    double lat, double lon,
    double mlat, double mlon,
    double& x, double& y
);

constexpr double EARTH_RADIUS = 6378000.0;
constexpr double PI = 3.14159265358979323846;

int main() {
    while (true) {
        std::cout << "Enter coordinates of map center: " << std::endl;
        double mlat, mlon;
        std::cin >> mlat >> mlon;
        if (!std::cin) break;
        std::cout << "Enter coordinates of  a point on Earth: " << std::endl;
        double lat, lon;
        double x, y;
        std::cin >> lat >> lon;
        earth2map(lat, lon, mlat, mlon, x, y);
        std::cout << "Coordinates on map in meters: " << x << "\t" << y << std::endl;
    }
    
    return 0;
}


R3Graph::R3Vector radiusVector(double lat, double lon) {
    double phi = lon*PI/180.;   // Convert to radians
    double theta = lat*PI/180.;
    // Rotate ex around ez by angle phi: v0 = (cos(phi), sin(phi), 0.)
    // Rotate v0 in meridional plane by angle theta:
    // v1 = (cos(phi)*cos(theta), sin(phi)*cos(theta), sin(theta))
    double cosTheta = cos(theta);
    return R3Graph::R3Vector(cos(phi)*cosTheta, sin(phi)*cosTheta, sin(theta));
}

void earth2map(
    double lat, double lon,
    double mlat, double mlon,
    double& x, double& y
) {
    R3Graph::R3Vector nord(0., 0., 1.);
    R3Graph::R3Vector n = radiusVector(mlat, mlon);
    R3Graph::R3Vector ex = nord.vectorProduct(n);
    ex.normalize();

    R3Graph::R3Vector ey = n.vectorProduct(ex);
    ey.normalize();
    R3Graph::R3Point origin(0., 0., 0.);
    R3Graph::R3Point mapCenter = origin + n * EARTH_RADIUS;
    R3Graph::R3Point pointOnMap;
    R3Graph::intersectPlaneAndLine(
        mapCenter, n,
        origin, radiusVector(lat, lon),
        pointOnMap
    );
    R3Graph::R3Vector w = pointOnMap - mapCenter;
    x = w * ex;
    y = w * ey;
}
