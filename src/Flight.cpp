#include "Flight.h"

Flight::Flight(const std::string& airlineCode) : m_airline(airlineCode) {}

// Constructor
Flight::Flight(const std::string &source, const std::string &target, const std::string &airline)
        : m_source(source), m_target(target), m_airline(airline) {}

// Getters
std::string Flight::getSource() const {
    return m_source;
}

std::string Flight::getTarget() const {
    return m_target;
}

std::string Flight::getAirline() const {
    return m_airline;
}

// Setters
void Flight::setSource(const std::string &source) {
    m_source = source;
}

void Flight::setTarget(const std::string &target) {
    m_target = target;
}

void Flight::setAirline(const std::string &airline) {
    m_airline = airline;
}
