#include "Airline.h"

// Constructor
Airline::Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country)
        : m_code(code), m_name(name), m_callsign(callsign), m_country(country) {}

// Getters
std::string Airline::getCode() const {
    return m_code;
}

std::string Airline::getName() const {
    return m_name;
}

std::string Airline::getCallsign() const {
    return m_callsign;
}

std::string Airline::getCountry() const {
    return m_country;
}

// Setters
void Airline::setCode(const std::string &code) {
    m_code = code;
}

void Airline::setName(const std::string &name) {
    m_name = name;
}

void Airline::setCallsign(const std::string &callsign) {
    m_callsign = callsign;
}

void Airline::setCountry(const std::string &country) {
    m_country = country;
}
