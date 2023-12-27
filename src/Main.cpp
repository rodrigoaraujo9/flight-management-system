#include "Graph.h"
#include "Read.h"
#include "Statistics.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include <iostream>
#include <unordered_set>

int main() {
    Graph<Airport> airportGraph;
    std::unordered_set<Airline> airlines;

    Read reader;
    std::string ref = "../dataset/";
    // Read data from files
    reader.readAirports(airportGraph, ref + "airports.csv");
    reader.readAirlines(airlines, ref + "airlines.csv");
    reader.readFlights(airportGraph, ref + "flights.csv");

    // Initialize Statistics instance
    Statistics stats(airportGraph, airlines);

    // Output the number of airports, airlines, and total flights
    std::cout << "Number of airports: " << airportGraph.getNumVertex() << std::endl;
    std::cout << "Number of airlines: " << airlines.size() << std::endl;
    std::cout << "Total number of flights: " << stats.getTotalNumberOfFlights() << std::endl;

    // Test: Number of flights from a specific airport
    std::string airportCode = "JFK";
    long numberOfFlightsFromAirport = stats.getNumberOfFlightsFromAirport(airportCode);
    if (numberOfFlightsFromAirport != -1) {
        std::cout << "Number of flights from " << airportCode << ": " << numberOfFlightsFromAirport << std::endl;
    } else {
        std::cout << "Airport " << airportCode << " not found." << std::endl;
    }

    // Test: Number of unique airlines from a specific airport
    long numberOfUniqueAirlinesFromAirport = stats.getNumberOfUniqueAirlinesFromAirport(airportCode);
    if (numberOfUniqueAirlinesFromAirport != -1) {
        std::cout << "Number of unique airlines from " << airportCode << ": " << numberOfUniqueAirlinesFromAirport << std::endl;
    } else {
        std::cout << "Airport " << airportCode << " not found." << std::endl;
    }

    // Add more tests as needed for other functionalities

    return 0;
}
