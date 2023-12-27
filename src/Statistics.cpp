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






std::map<std::pair<std::string, std::string>, long> Statistics::getNumberOfFlightsPerCityAirline() const {
    std::map<std::pair<std::string, std::string>, long> cityAirlineFlights;

    for (const auto* vertex : airportGraph.getVertexSet()) {
        std::string city = vertex->getInfo().getCity();
        for (const auto& edge : vertex->getAdj()) {
            for (const auto& flight : edge.getFlights()) {
                std::string airline = flight.getAirline();
                std::pair<std::string, std::string> cityAirlinePair = std::make_pair(city, airline);
                cityAirlineFlights[cityAirlinePair]++;
            }
        }
    }

    return cityAirlineFlights;
}

std::map<std::string, long> Statistics::getNumberOfFlightsPerCity() const {
    std::map<std::string, long> cityFlights;

    for (const auto* vertex : airportGraph.getVertexSet()) {
        std::string city = vertex->getInfo().getCity();
        for (const auto& edge : vertex->getAdj()) {
            for (const auto& flight : edge.getFlights()) {
                cityFlights[city]++;
            }
        }
    }

    return cityFlights;
}

std::map<std::string, long> Statistics::getNumberOfFlightsPerAirline() const {
    std::map<std::string, long> airlineFlights;

    for (const auto* vertex : airportGraph.getVertexSet()) {
        for (const auto& edge : vertex->getAdj()) {
            for (const auto& flight : edge.getFlights()) {
                std::string airline = flight.getAirline();
                airlineFlights[airline]++;
            }
        }
    }

    return airlineFlights;
}




long Statistics::getNumberOfDiffCountriesByAirport(const std::string& airportCode) const{

    const auto* airportVertex = airportGraph.findVertex(Airport(airportCode));
    if (!airportVertex) return -1;

    std::unordered_set<std::string> uniqueCountries;
    for (const auto& edge : airportVertex->getAdj()) {
        const auto* destAirportVertex = edge.getDest();
        uniqueCountries.insert(destAirportVertex->getInfo().getCountry());
    }

    return uniqueCountries.size();
}

long Statistics::getNumberOfDiffCountriesByCity(const std::string& city) const{
    std::unordered_set<std::string> uniqueCountries;
    for(const auto* airportVertex : airportGraph.getVertexSet()){
        if(airportVertex->getInfo().getCity()==city){
            for (const auto& edge : airportVertex->getAdj()) {
                const auto* destAirportVertex = edge.getDest();
                uniqueCountries.insert(destAirportVertex->getInfo().getCountry());
            }
        }

    }
    return uniqueCountries.size();
}