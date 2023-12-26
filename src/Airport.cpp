#include "Airport.h"

// Constructor for search purposes
Airport::Airport(const std::string& code) : m_code(code) {}

// Constructor
Airport::Airport(const std::string &code, const std::string &name, const std::string &city,
                 const std::string &country, double latitude, double longitude)
        : m_code(code), m_name(name), m_city(city), m_country(country),
          m_latitude(latitude), m_longitude(longitude) {}

// Getters
std::string Airport::getCode() const {
    return m_code;
}

std::string Airport::getName() const {
    return m_name;
}

std::string Airport::getCity() const {
    return m_city;
}

std::string Airport::getCountry() const {
    return m_country;
}

double Airport::getLatitude() const {
    return m_latitude;
}

double Airport::getLongitude() const {
    return m_longitude;
}

// Setters
void Airport::setCode(const std::string &code) {
    m_code = code;
}

void Airport::setName(const std::string &name) {
    m_name = name;
}

void Airport::setCity(const std::string &city) {
    m_city = city;
}

void Airport::setCountry(const std::string &country) {
    m_country = country;
}

void Airport::setLatitude(double latitude) {
    m_latitude = latitude;
}

void Airport::setLongitude(double longitude) {
    m_longitude = longitude;
}
