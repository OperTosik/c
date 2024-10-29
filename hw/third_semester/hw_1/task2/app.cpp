#include "R3Graph.h"

R3Graph::R3Vector radiusVector(
    double lat, double lon
);

void map2earth(
    double x, double y,
    double mlat, double mlon,
    double& lat, double& lon
);

void getSphericalCoordinates(
    const R3Graph::R3Vector& vector,
    double& lat, double& lon
);

double EARTH_RADIUS = 6378000.0;
const double PI = 3.14159265358979323846;

int main() {
    while (true) {
        std::cout << "Enter coordinates of map center: " << std::endl;
        double mlat, mlon;
        std::cin >> mlat >> mlon;
        if (!std::cin) break;
        std::cout << "Enter coordinates of a point on map: " << std::endl;
        double x, y;
        std::cin >> x >> y;
        double lat, lon;
        map2earth(x, y, mlat, mlon, lat, lon);
        std::cout << "Coordinates on the Earth: ";
        std::cout << lat << "\t" << lon << std::endl;
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

void map2earth(
    double x, double y,
    double mlat, double mlon,
    double& lat, double& lon
) {
    R3Graph::R3Vector nord(0., 0., 1.);
    R3Graph::R3Vector n = radiusVector(mlat, mlon);
    R3Graph::R3Vector ex = nord.vectorProduct(n);
    ex.normalize();
    R3Graph::R3Vector ey = n.vectorProduct(ex);
    ey.normalize();
    R3Graph::R3Point origin(0., 0., 0.);
    R3Graph::R3Point mapCenter = origin + n * EARTH_RADIUS;
    R3Graph::R3Point pointOnMap = mapCenter + ex * x + ey * y;
    R3Graph::R3Vector vectorToPoint = pointOnMap - origin;
    vectorToPoint.normalize();
    vectorToPoint *= EARTH_RADIUS;
    getSphericalCoordinates(
        vectorToPoint,
        lat, lon
    );

}

void getSphericalCoordinates(
    const R3Graph::R3Vector& vector,
    double& lat, double& lon
) {
    // double theta = atan2(sqrt(vector.x * vector.x + vector.y * vector.y), vector.z);
    double theta = PI/2. - R3Graph::R3Vector(0., 0., 1.).angle(vector);

    double phi = atan2(vector.y, vector.x);
    lat = theta * 180. / PI;
    lon = phi * 180. / PI;
}