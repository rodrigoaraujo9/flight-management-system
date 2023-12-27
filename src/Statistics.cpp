#include "Statistics.h"

Statistics::Statistics(Graph<Airport>& airportGraph, std::unordered_set<Airline>& airlines )
        : airportGraph(airportGraph), airlines(airlines) {}

int Statistics::getTotalNumberOfAirports() const {
    return airportGraph.getNumVertex();
}

int Statistics::getTotalNumberOfFlights() const {
    int totalFlights = 0;

    // Iterate through all vertices in the graph
    for (const auto* vertex : airportGraph.getVertexSet()) {
        // Iterate through all edges (adjacent vertices) of each vertex
        for (const auto& edge : vertex->getAdj()) {
            // Add the number of flights in the edge's flight set to the total
            totalFlights += edge.getFlights().size();
        }
    }

    return totalFlights;
}


long Statistics::getNumberOfUniqueAirlinesFromAirport(const std::string &airportCode) const {
    const auto *airportVertex = airportGraph.findVertex(Airport(airportCode));
    if (!airportVertex) return -1;

    std::unordered_set<std::string> uniqueAirlines;
    for (const auto &edge: airportVertex->getAdj()) {
        for (const auto &flight: edge.getFlights()) {  // Assuming Edge class has getFlights method
            uniqueAirlines.insert(flight.getAirline());
        }
    }
    return uniqueAirlines.size();
}

long Statistics::getNumberOfFlightsFromAirport(const std::string &airportCode) const {
    const auto *airportVertex = airportGraph.findVertex(Airport(airportCode));
    if (!airportVertex) return -1;

    long count = 0;
    for (const auto &edge: airportVertex->getAdj()) {
        count += edge.getFlights().size();  // Assuming Edge class has getFlights method
    }
    return count;
}

