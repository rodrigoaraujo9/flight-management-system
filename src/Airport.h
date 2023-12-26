#ifndef AIRPORT_H
#define AIRPORT_H

#include <string>

class Airport {
public:
    // Constructor

    explicit Airport(const std::string& code);

    Airport(const std::string &code, const std::string &name, const std::string &city,
            const std::string &country, double latitude, double longitude);

    // Getters
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    double getLatitude() const;
    double getLongitude() const;

    // Setters
    void setCode(const std::string &code);
    void setName(const std::string &name);
    void setCity(const std::string &city);
    void setCountry(const std::string &country);
    void setLatitude(double latitude);
    void setLongitude(double longitude);

    bool operator==(const Airport& other) const {
        return m_code == other.m_code;
    }

private:
    std::string m_code;       // Airport code
    std::string m_name;       // Airport name
    std::string m_city;       // City where the airport is located
    std::string m_country;    // Country where the airport is located
    double m_latitude;        // Latitude
    double m_longitude;       // Longitude
};

#endif // AIRPORT_H
