#ifndef READ_H
#define READ_H

#include "Graph.h"
#include <string>
#include <unordered_set>

class Airport;
class Airline;
class Flight;

class Read {
public:
    Read() = default;

    void readAirports(Graph<Airport>& airportGraph, const std::string& filename);
    void readAirlines(std::unordered_set<Airline>& airlines, const std::string& filename);
    void readFlights(Graph<Airport>& airportGraph, std::unordered_set<Flight>& flights, const std::string& filename);
};

#endif // READ_H
