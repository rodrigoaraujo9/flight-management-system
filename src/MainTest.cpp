#include "Graph.h"
#include "Search.h"
#include "Read.h"
#include <iostream>
#include <unordered_set>

int main() {
    Graph<Airport> airportGraph;
    Read reader;

    // Read data from the dataset
    reader.readAirports(airportGraph, "../dataset/airports.csv");
    reader.readFlights(airportGraph, "../dataset/flights.csv");

    // Create a Search object
    Search search(airportGraph);

    // Define the test parameters
    std::string source = "CDG"; // Paris Charles de Gaulle Airport
    std::string destination = "LAX"; // Los Angeles International Airport
    std::unordered_set<std::string> preferredAirlines = {"AFR", "DAL"}; // Air France and Delta Air Lines
    bool minimizeAirlineChanges = true;

    // Find the best flight
    auto bestFlights = search.findBestFlight(source, destination, preferredAirlines, minimizeAirlineChanges);

    // Display the results
    std::cout << "Best flight path from " << source << " to " << destination << " with preferred airlines and minimized airline changes:" << std::endl;
    if (bestFlights.empty()) {
        std::cout << "No suitable flights found." << std::endl;
    } else {
        for (const auto& airport : bestFlights) {
            std::cout << airport.getName() << " (" << airport.getCode() << ") -> ";
        }
        std::cout << "End" << std::endl;
    }

    return 0;
}


