#include "Graph.h"
#include "Read.h"
#include "Statistics.h"
#include "Search.h"
#include "Airport.h"
#include "Airline.h"
#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    Graph<Airport> airportGraph;
    std::unordered_set<Airline> airlines;

    Read reader;
    std::string ref = "../dataset/";
    reader.readAirports(airportGraph, ref + "airports.csv");
    reader.readAirlines(airlines, ref + "airlines.csv");
    reader.readFlights(airportGraph, ref + "flights.csv");

    Statistics stats(airportGraph, airlines);
    Search search(airportGraph);

    std::cout << "Number of airports: " << airportGraph.getNumVertex() << std::endl;
    std::cout << "Number of airlines: " << airlines.size() << std::endl;
    std::cout << "Total number of flights: " << stats.getTotalNumberOfFlights() << std::endl;

    // Test: Find best flight using airport codes
    std::string source = "JFK";
    std::string destination = "THU";
    std::cout << "Best flight path from " << source << " to " << destination << " using codes:" << std::endl;
    auto bestFlights = search.findBestFlight(source, destination);
    for (const auto& airport : bestFlights) {
        std::cout << airport.getName() << " (" << airport.getCode() << ") -> ";
    }
    std::cout << "End\n";

    // Test: Find best flight using city name
    source = "New York";
    destination = "Pituffik";
    std::cout << "Best flight path from " << source << " to " << destination << " using city names:" << std::endl;
    bestFlights = search.findBestFlight(source, destination);
    for (const auto& airport : bestFlights) {
        std::cout << airport.getName() << " (" << airport.getCode() << ") -> ";
    }
    std::cout << "End\n";

    // Test: Find best flight using geographical coordinates
    std::string sourceCoords = "40.6413111,-73.7781391";  // Coordinates for JFK
    std::string destCoords = "76.531203,-68.703161";     // Coordinates for THU
    std::cout << "Best flight path from " << sourceCoords << " to " << destCoords << " using coordinates:" << std::endl;
    bestFlights = search.findBestFlight(sourceCoords, destCoords);
    for (const auto& airport : bestFlights) {
        std::cout << airport.getName() << " (" << airport.getCode() << ") -> ";
    }
    std::cout << "End\n";

    return 0;
}
