#include "Graph.h"
#include "Read.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include <iostream>
#include <unordered_set>

int main() {
    Graph<Airport> airportGraph;
    std::unordered_set<Airline> airlines;
    std::unordered_set<Flight> flights;

    Read reader;
    std::string ref = "../dataset/";
    // Read data from files
    reader.readAirports(airportGraph, ref+"airports.csv");
    reader.readAirlines(airlines, ref+"airlines.csv");
    reader.readFlights(airportGraph, flights, ref+"flights.csv");

    // Test: Output the number of airports, airlines, and flights
    std::cout << "Number of airports: " << airportGraph.getNumVertex() << std::endl;
    std::cout << "Number of airlines: " << airlines.size() << std::endl;
    std::cout << "Number of flights: " << flights.size() << std::endl;

    // Additional test: Check for a specific airport or flight
    // Example: Check if a flight exists between two airports
    std::string sourceAirportCode = "JFK";
    std::string destAirportCode = "LAX";
    Edge<Airport>* edge = airportGraph.getEdge(Airport(sourceAirportCode), Airport(destAirportCode));

    if (edge != nullptr) {
        std::cout << "Number of flights from " << sourceAirportCode << " to " << destAirportCode
                  << ": " << edge->getWeight() << std::endl;
    } else {
        std::cout << "No flights from " << sourceAirportCode << " to " << destAirportCode << std::endl;
    }

    // ... Other tests can be added as needed

    return 0;
}
