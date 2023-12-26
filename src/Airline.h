#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <functional>

class Airline {
public:
    // Constructor
    Airline(const std::string &code, const std::string &name, const std::string &callsign, const std::string &country);

    // Getters
    std::string getCode() const;
    std::string getName() const;
    std::string getCallsign() const;
    std::string getCountry() const;

    // Setters
    void setCode(const std::string &code);
    void setName(const std::string &name);
    void setCallsign(const std::string &callsign);
    void setCountry(const std::string &country);

    bool operator<(const Airline& other) const {
        return m_code < other.m_code;  // Compare based on airline code
    }

    bool operator==(const Airline& other) const {
        return m_code == other.m_code;
    }

private:
    std::string m_code;       // IATA airline code
    std::string m_name;       // Airline name
    std::string m_callsign;   // Airline callsign
    std::string m_country;    // Country of origin
};

namespace std {
    template<>
    struct hash<Airline> {
        size_t operator()(const Airline& airline) const {
            // Hash based on the unique airline code
            return std::hash<std::string>()(airline.getCode());
        }
    };
}

#endif // AIRLINE_H

