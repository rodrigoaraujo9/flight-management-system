#ifndef STATISTICS_H
#define STATISTICS_H

#include "Graph.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include <unordered_set>
#include <string>
#include <map>

class Statistics {

private:
    Graph<Airport>& airportGraph;
    std::unordered_set<Airline>& airlines;

public:
    Statistics(Graph<Airport>& airportGraph, std::unordered_set<Airline>& airlines);

    // Method declarations
    //I
    int getTotalNumberOfAirports() const;
    int getTotalNumberOfFlights() const;
    //II
    long getNumberOfFlightsFromAirport(const std::string& airportCode) const;
    long getNumberOfUniqueAirlinesFromAirport(const std::string& airportCode) const;
    //III
    std::map<std::pair<std::string, std::string>, long> getNumberOfFlightsPerCityAirline() const;
    std::map<std::string, long> getNumberOfFlightsPerCity() const;
    std::map<std::string, long> getNumberOfFlightsPerAirline() const;
};

#endif // STATISTICS_H