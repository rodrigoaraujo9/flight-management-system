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
    int getTotalNumberOfAirports() const;
    int getTotalNumberOfFlights() const;
    long getNumberOfFlightsFromAirport(const std::string& airportCode) const;
    long getNumberOfUniqueAirlinesFromAirport(const std::string& airportCode) const;
    // ... other methods for ii. to ix. ...
};

#endif // STATISTICS_H