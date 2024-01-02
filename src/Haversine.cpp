#include "Haversine.h"
#include <cmath>

constexpr double EARTH_RADIUS_KM = 6371.0;
/**
 * @brief Calculate the Haversine distance between two geographic coordinates.
 *
 * The Haversine formula calculates the distance between two points on the surface of a sphere
 * (in this case, Earth) given their latitude and longitude coordinates.
 *
 * @param lat1 The latitude of the first point in degrees.
 * @param lon1 The longitude of the first point in degrees.
 * @param lat2 The latitude of the second point in degrees.
 * @param lon2 The longitude of the second point in degrees.
 * @return The Haversine distance between the two points in kilometers.
 *
 * @note The Earth's radius is assumed to be constant (EARTH_RADIUS_KM) for the calculation.
 * @note Input coordinates are expected to be in degrees, and the result is in kilometers.
 * @note Time complexity: O(1) (constant time complexity).
 */
double Haversine::haversineDistance(double lat1, double lon1, double lat2, double lon2) {
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    double a = std::pow(std::sin(dLat / 2), 2) +
               std::pow(std::sin(dLon / 2), 2) *
               std::cos(lat1) * std::cos(lat2);
    double c = 2 * std::asin(std::sqrt(a));
    return EARTH_RADIUS_KM * c;
}

