#include "R3Graph.h"

R3Graph::R3Vector radiusVector(double lat, double lon);
// void getAxis(R3Graph::R3Vector v, R3Graph::R3Vector& axisX, R3Graph::R3Vector& axisY);

double EARTH_RADIUS = 6378000.0;
const double PI = 3.14159265358979323846;

int main() {
    double mlat, mlon;
    double lat, lon;
    // R3Graph::R3Point center = R3Graph::R3Point();
    R3Graph::R3Point resPoint;
    R3Graph::R3Vector mVectorToCenter;
    // R3Graph::R3Vector axisX, axisY;
    R3Graph::R3Vector resVectorToCenter;

    std::cout << "Enter the mlat: " << std::endl;
    std::cin >> mlat;
    std::cout << "Enter the mlon: " << std::endl;
    std::cin >> mlon;
    std::cout << "Enter the lat: " << std::endl;
    std::cin >> lat;
    std::cout << "Enter the lon: " << std::endl;
    std::cin >> lon;

    mVectorToCenter = radiusVector(mlat, mlon);
    resVectorToCenter = radiusVector(lat, lon);
    // getAxis(mVectorToCenter, axisX, axisY);
    R3Graph::intersectPlaneAndLine(
        R3Graph::R3Point() + mVectorToCenter,
        mVectorToCenter,
        R3Graph::R3Point(),
        resVectorToCenter,
        resPoint
    );
    std::cout << "result: " << resPoint << std::endl;
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



// void getAxis(R3Graph::R3Vector vector, R3Graph::R3Vector& axisX, R3Graph::R3Vector& axisY) {
//     R3Graph::R3Vector vectorProjectionAxisZ = R3Graph::R3Vector(0., 0., vector.z);
//     R3Graph::R3Vector hToAxisZ = vector - vectorProjectionAxisZ;
//     R3Graph::R3Vector vectorToAxisZ = R3Graph::R3Vector(0., 0., hToAxisZ.length2());
//     axisY = vectorToAxisZ - vector;
//     axisX = axisY.vectorProduct(hToAxisZ);
//     return;
// }