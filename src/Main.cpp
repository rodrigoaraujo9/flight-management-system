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

    //airport code is JFK
    int maxStops = 2; // Maximum number of stops
    // Test reachable airports from JFK within 2 stops
    auto reachableAirports = stats.getReachableAirports(airportCode, maxStops);
    std::cout << "Reachable airports from " << airportCode << " within " << maxStops << " stops: " << reachableAirports.size() << std::endl;

    // Test reachable cities from JFK within 2 stops
    auto reachableCities = stats.getReachableCities(airportCode, maxStops);
    std::cout << "Reachable cities from " << airportCode << " within " << maxStops << " stops: " << reachableCities.size() << std::endl;

    // Test reachable countries from JFK within 2 stops
    auto reachableCountries = stats.getReachableCountries(airportCode, maxStops);
    std::cout << "Reachable countries from " << airportCode << " within " << maxStops << " stops: " << reachableCountries.size() << std::endl;


    auto longestPaths = stats.findLongestPath();

    for (const auto& path : longestPaths) {
        for (const auto& airport : path) {
            std::cout << airport.getCode() << " -> ";
        }
        std::cout << "End\n";
    }

    int k = 10; // Example: find top 10 airports
    auto topKAirports = stats.getTopKAirportsByFlights(k);

    for (const auto& [airport, flightCount] : topKAirports) {
        std::cout << airport.getCode() << " has " << flightCount << " flights." << std::endl;
    }

    auto essentialAirports = stats.findEssentialAirports();

    std::cout << "Essential Airports:" << std::endl;
    for (const auto& airport : essentialAirports) {
        std::cout << airport.getCode() << std::endl;
    }

    return 0;
}
