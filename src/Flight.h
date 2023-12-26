#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <functional>

class Flight {
public:
    // Constructor
    explicit Flight(const std::string& airlineCode);
    Flight(const std::string &source, const std::string &target, const std::string &airline);

    // Getters
    std::string getSource() const;
    std::string getTarget() const;
    std::string getAirline() const;

    // Setters
    void setSource(const std::string &source);
    void setTarget(const std::string &target);
    void setAirline(const std::string &airline);

    bool operator<(const Flight& other) const {
        return (m_source < other.m_source);  // Compare based on airline code
    }

    bool operator==(const Flight& other) const {
        return m_source == other.m_source && m_target == other.m_target && m_airline == other.m_airline;
    }

private:
    std::string m_source; // Source airport code
    std::string m_target; // Target airport code
    std::string m_airline; // Airline code
};

namespace std {
    template<>
    struct hash<Flight> {
        size_t operator()(const Flight& flight) const {
            return hash<string>()(flight.getSource() + flight.getTarget() + flight.getAirline());
        }
    };
}
#endif // FLIGHT_H

