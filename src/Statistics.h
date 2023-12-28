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

    //AUX FUNCTIONS
    void resetVisited(Graph<Airport>& graph);
    void dfs(Vertex<Airport>* vertex, std::unordered_set<std::string>& visited, std::vector<Airport>& path, std::vector<std::vector<Airport>>& longestPaths, int& maxLength);
    void findArticulationPoints(Vertex<Airport>* v, int& time,
                                std::unordered_map<Airport, int, AirportHash, AirportEqual>& disc,
                                std::unordered_map<Airport, int, AirportHash, AirportEqual>& low,
                                std::unordered_map<Airport, Vertex<Airport>*, AirportHash, AirportEqual>& parent,
                                std::unordered_set<Airport, AirportHash, AirportEqual>& articulationPoints);
    Graph<Airport> createUndirectedCopy(const Graph<Airport>& directedGraph);


public:
    Statistics(Graph<Airport>& airportGraph, std::unordered_set<Airline>& airlines);

    // Method declarations
    //I
    int getTotalNumberOfAirports() const;
    int getTotalNumberOfFlights() const;
    //II
    long getNumberOfFlightsFromAirport(const std::string& airportCode) const;
    long getNumberOfUniqueAirlinesFromAirport(const std::string& airportCode) const;
    //III
    std::map<std::pair<std::string, std::string>, long> getNumberOfFlightsPerCityAirline() const;
    std::map<std::string, long> getNumberOfFlightsPerCity() const;
    std::map<std::string, long> getNumberOfFlightsPerAirline() const;
    //IV
    long getNumberOfDiffCountriesByAirport(const std::string& airportCode) const;
    long getNumberOfDiffCountriesByCity(const std::string& city) const;
    //V
    std::unordered_set<std::string> getReachableAirports(const std::string& airportCode, int maxStops) const;
    std::unordered_set<std::string> getReachableCities(const std::string& airportCode, int maxStops) const;
    std::unordered_set<std::string> getReachableCountries(const std::string& airportCode, int maxStops) const;
    //VI
    std::vector<std::vector<Airport>> findLongestPath();
    //VII
    std::vector<std::pair<Airport, int>> getTopKAirportsByFlights(int k);
    //VIII
    std::unordered_set<Airport, AirportHash, AirportEqual> findEssentialAirports();

};

#endif // STATISTICS_H