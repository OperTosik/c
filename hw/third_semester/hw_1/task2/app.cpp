#include "R3Graph.h"

R3Graph::R3Vector radiusVector(double lat, double lon);
void getAxis(R3Graph::R3Vector v, R3Graph::R3Vector& axisX, R3Graph::R3Vector& axisY);
void getSphericalCoordinates(R3Graph::R3Vector vector, double& lat, double& lon);

double EARTH_RADIUS = 6378000.0;
const double PI = 3.14159265358979323846;

int main() {
    double mlat, mlon;
    double x, y;
    // R3Graph::R3Point center = R3Graph::R3Point();
    double lat, lon;
    R3Graph::R3Vector mVectorToCenter;
    R3Graph::R3Vector axisX, axisY;
    R3Graph::R3Vector resVectorToCenter;
    R3Graph::R3Vector mVector; //(x,y)

    std::cout << "Enter the mlat: " << std::endl;
    std::cin >> mlat;
    std::cout << "Enter the mlon: " << std::endl;
    std::cin >> mlon;
    std::cout << "Enter the x: " << std::endl;
    std::cin >> x;
    std::cout << "Enter the y: " << std::endl;
    std::cin >> y;

    mVectorToCenter = radiusVector(mlat, mlon);
    getAxis(mVectorToCenter, axisX, axisY);
    axisX.normalized();
    axisY.normalized();
    mVector = mVectorToCenter + (axisX * x + axisY * y); //radius-vector (x, y)
    getSphericalCoordinates(mVector, lat, lon);

    std::cout << "lat: " << lat << "\t" << "lon: " << lon << std::endl;
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

void getAxis(R3Graph::R3Vector vector, R3Graph::R3Vector& axisX, R3Graph::R3Vector& axisY) {
    R3Graph::R3Vector vectorProjectionAxisZ = R3Graph::R3Vector(0., 0., vector.z);
    R3Graph::R3Vector hToAxisZ = vector - vectorProjectionAxisZ;
    R3Graph::R3Vector vectorToAxisZ = R3Graph::R3Vector(0., 0., hToAxisZ.length2());
    axisY = vectorToAxisZ - vector;
    axisX = axisY.vectorProduct(hToAxisZ);
    return;
}

void getSphericalCoordinates(R3Graph::R3Vector vector, double& lat, double& lon) {
    vector.normalized();
    R3Graph::R3Vector vectorProjectionToXY = R3Graph::R3Vector(vector.x, vector.y, 0.).normalized();
    lat = vectorProjectionToXY.angle(R3Graph::R3Vector(1., 0., 0.));
    lon = vector.angle(R3Graph::R3Vector(0., 0., 1.));
    return;
}