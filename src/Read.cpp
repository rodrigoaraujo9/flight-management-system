#include "Read.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

void Read::readAirlines(std::unordered_set<Airline>& airlines, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string code, name, callsign, country;
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callsign, ',');
        getline(ss, country);

        Airline airline(code, name, callsign, country);
        airlines.insert(airline);
    }
}


void Read::readAirports(Graph<Airport>& airportGraph, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string code, name, city, country, lat, lon;
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        getline(ss, lat, ',');
        getline(ss, lon);

        Airport airport(code, name, city, country, stod(lat), stod(lon));
        airportGraph.addVertex(airport);
    }
}

void Read::readFlights(Graph<Airport>& airportGraph, std::unordered_set<Flight>& flights, const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string sourceCode, targetCode, airline;
        getline(ss, sourceCode, ',');
        getline(ss, targetCode, ',');
        getline(ss, airline);

        Flight flight(sourceCode, targetCode, airline);

        auto sourceVertex = airportGraph.findVertex(Airport(sourceCode));
        auto targetVertex = airportGraph.findVertex(Airport(targetCode));

        if (sourceVertex && targetVertex) {
            Edge<Airport>* edge = airportGraph.getEdge(Airport(sourceCode), Airport(targetCode));
            if (edge) {
                edge->addFlight(flight);
            } else {
                airportGraph.addEdge(Airport(sourceCode), Airport(targetCode), 1);
                edge = airportGraph.getEdge(Airport(sourceCode), Airport(targetCode));
                edge->addFlight(flight);
            }
        }
    }
}