#include "Graph.h"
#include "Search.h"
#include "Read.h"
#include <iostream>
#include <unordered_set>
#include "Airline.h"

int main() {
    // Initialize the graph and read data
    Graph<Airport> airportGraph;
    std::unordered_set<Airline> airlines;
    Read reader;
    std::string path = "../dataset/"; // Adjust the path according to your file structure

    reader.readAirports(airportGraph, path + "airports.csv");
    reader.readAirlines(airlines, path + "airlines.csv");
    reader.readFlights(airportGraph, path + "flights.csv");

    // Create a Search object
    Search search(airportGraph);

    // Define test cases
    std::string source = "LIS";
    std::string destination = "JFK"; // Assuming JFK is a possible destination from LIS

    // Test 1: Preferred airlines
    std::unordered_set<std::string> preferredAirlines = {"TAP", "AAL"}; // Assuming TAP and AAL operate flights from LIS
    auto bestFlights = search.findBestFlight(source, destination, preferredAirlines, false);
    std::cout << "Best flights from LIS to JFK with preferred airlines (TAP, AAL):\n";
    for (const auto& [airport, airline] : bestFlights) {
        std::cout << airport.getName() << " (" << airport.getCode() << ") via " << airline << " -> ";
    }
    std::cout << "End\n\n";

    // Test 2: Minimize airline changes
    bestFlights = search.findBestFlight(source, destination, {}, true);
    std::cout << "Best flights from LIS to JFK minimizing airline changes:\n";

    for (const auto& [airport, airline] : bestFlights) {
        std::cout << airport.getName() << " (" << airport.getCode() << ") via " << airline << " -> ";
    }
    std::cout << "End\n\n";

    // Test 3: No preferences
    bestFlights = search.findBestFlight(source, destination, {}, false);
    std::cout << "Best flights from LIS to JFK with no preferences:\n";
    for (const auto& [airport, airline] : bestFlights) {
        std::cout << airport.getName() << " (" << airport.getCode() << ") via " << airline << " -> ";
    }
    std::cout << "End\n";

    return 0;
}
