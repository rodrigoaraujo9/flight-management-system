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





std::unordered_set<std::string> Statistics::getReachableAirports(const std::string& airportCode, int maxStops) const {
    std::unordered_set<std::string> reachableAirports;
    std::queue<std::pair<Vertex<Airport>*, int>> q;
    std::unordered_set<Vertex<Airport>*> visited;

    auto s = airportGraph.findVertex(Airport(airportCode));
    if (s != nullptr) {
        q.push({s, 0});
        visited.insert(s);

        while (!q.empty()) {
            auto [v, stops] = q.front();
            q.pop();

            if (stops <= maxStops) {
                reachableAirports.insert(v->getInfo().getCode());

                for (const auto& e : v->getAdj()) {
                    Vertex<Airport>* w = e.getDest();
                    if (visited.find(w) == visited.end()) {
                        q.push({w, stops + 1});
                        visited.insert(w);
                    }
                }
            }
        }
    }

    return reachableAirports;
}

std::unordered_set<std::string> Statistics::getReachableCities(const std::string& airportCode, int maxStops) const {
    std::unordered_set<std::string> reachableCities;
    std::queue<std::pair<Vertex<Airport>*, int>> q;
    std::unordered_set<Vertex<Airport>*> visited;

    auto s = airportGraph.findVertex(Airport(airportCode));
    if (s != nullptr) {
        q.push({s, 0});
        visited.insert(s);

        while (!q.empty()) {
            auto [v, stops] = q.front();
            q.pop();

            if (stops <= maxStops) {
                reachableCities.insert(v->getInfo().getCity());

                for (const auto& e : v->getAdj()) {
                    Vertex<Airport>* w = e.getDest();
                    if (visited.find(w) == visited.end()) {
                        q.push({w, stops + 1});
                        visited.insert(w);
                    }
                }
            }
        }
    }

    return reachableCities;
}

std::unordered_set<std::string> Statistics::getReachableCountries(const std::string& airportCode, int maxStops) const {
    std::unordered_set<std::string> reachableCountries;
    std::queue<std::pair<Vertex<Airport>*, int>> q;
    std::unordered_set<Vertex<Airport>*> visited;

    auto s = airportGraph.findVertex(Airport(airportCode));
    if (s != nullptr) {
        q.push({s, 0});
        visited.insert(s);

        while (!q.empty()) {
            auto [v, stops] = q.front();
            q.pop();

            if (stops <= maxStops) {
                reachableCountries.insert(v->getInfo().getCountry());

                for (const auto& e : v->getAdj()) {
                    Vertex<Airport>* w = e.getDest();
                    if (visited.find(w) == visited.end()) {
                        q.push({w, stops + 1});
                        visited.insert(w);
                    }
                }
            }
        }
    }

    return reachableCountries;
}





void Statistics::dfs(Vertex<Airport>* vertex, std::unordered_set<std::string>& visited, std::vector<Airport>& path, std::vector<std::vector<Airport>>& longestPaths, int& maxLength) {
    vertex->setProcessing(true);
    path.push_back(vertex->getInfo());

    bool isEndpoint = true;
    for (const auto& edge : vertex->getAdj()) {
        if (!edge.getDest()->isVisited() && !edge.getDest()->isProcessing()) {
            isEndpoint = false;
            edge.getDest()->setVisited(true);
            dfs(edge.getDest(), visited, path, longestPaths, maxLength);
        }
    }

    if (isEndpoint) {
        if (path.size() > maxLength) {
            maxLength = path.size();
            longestPaths.clear();
            longestPaths.push_back(path);
        } else if (path.size() == maxLength) {
            longestPaths.push_back(path);
        }
    }

    path.pop_back();
    vertex->setProcessing(false);
}

void Statistics::resetVisited(Graph<Airport>& graph) {
    for (auto* vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }
}


std::vector<std::vector<Airport>> Statistics::findLongestPath() {
    std::vector<std::vector<Airport>> longestPaths;
    int maxLength = 0;
    std::unordered_set<std::string> visited;

    for (auto* vertex : airportGraph.getVertexSet()) {
        std::vector<Airport> path;
        visited.clear();
        dfs(vertex, visited, path, longestPaths, maxLength);
    }

    return longestPaths;
}




std::vector<std::pair<Airport, int>> Statistics::getTopKAirportsByFlights(int k) {
    std::vector<std::pair<Airport, int>> airportFlightCounts;

    for (auto* vertex : airportGraph.getVertexSet()) {
        int flightCount = vertex->getAdj().size();
        airportFlightCounts.emplace_back(vertex->getInfo(), flightCount);
    }

    std::sort(airportFlightCounts.begin(), airportFlightCounts.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    if (k > airportFlightCounts.size()) {
        k = airportFlightCounts.size();
    }

    std::vector<std::pair<Airport, int>> topKAirports(airportFlightCounts.begin(), airportFlightCounts.begin() + k);
    return topKAirports;
}