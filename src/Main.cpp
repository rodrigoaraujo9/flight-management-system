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


    // Test: Number of different countries from a specific airport
    std::string airportCode = "JFK"; // Example airport code
    long countriesFromAirport = stats.getNumberOfDiffCountriesByAirport(airportCode);
    std::cout << "Number of different countries from " << airportCode << ": " << countriesFromAirport << std::endl;

    // Test: Number of different countries from a specific city
    std::string city = "Paris"; // Example city name
    long countriesFromCity = stats.getNumberOfDiffCountriesByCity(city);
    std::cout << "Number of different countries from " << city << ": " << countriesFromCity << std::endl;


    // Add more tests as needed for other functionalities

    return 0;
}
