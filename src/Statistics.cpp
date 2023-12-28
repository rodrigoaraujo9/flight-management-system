#include "Statistics.h"

/**
 * @brief Constructs a Statistics object.
 * @param airportGraph Reference to the graph of airports.
 * @param airlines Set of airlines.
 */
Statistics::Statistics(Graph<Airport>& airportGraph, std::unordered_set<Airline>& airlines )
        : airportGraph(airportGraph), airlines(airlines) {}




/**
 * @brief Gets the total number of airports in the graph.
 * @return Total number of airports.
 * @note Time complexity: O(1)
 */
int Statistics::getTotalNumberOfAirports() const {
    return airportGraph.getNumVertex();
}

/**
 * @brief Calculates the total number of flights across all airports.
 * @return Total number of flights.
 * @note Time complexity: O(V + E) where V is the number of vertices (airports) and E is the number of edges (flights).
 */
int Statistics::getTotalNumberOfFlights() const {
    int totalFlights = 0;

    for (const auto* vertex : airportGraph.getVertexSet()) {
        for (const auto& edge : vertex->getAdj()) {
            totalFlights += edge.getFlights().size();
        }
    }

    return totalFlights;
}




/**
 * @brief Gets the number of unique airlines operating from a given airport.
 * @param airportCode The airport code.
 * @return The number of unique airlines.
 * @note Time complexity: O(E) where E is the number of edges (flights) from the given airport.
 */
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

/**
 * @brief Gets the number of flights departing from a given airport.
 * @param airportCode The airport code.
 * @return The number of flights from the airport.
 * @note Time complexity: O(E) where E is the number of edges (flights) from the given airport.
 */
long Statistics::getNumberOfFlightsFromAirport(const std::string &airportCode) const {
    const auto *airportVertex = airportGraph.findVertex(Airport(airportCode));
    if (!airportVertex) return -1;

    long count = 0;
    for (const auto &edge: airportVertex->getAdj()) {
        count += edge.getFlights().size();  // Assuming Edge class has getFlights method
    }
    return count;
}





/**
 * @brief Gets the number of flights per city and per airline.
 * @return A map where the key is a pair of city and airline, and the value is the number of flights.
 * @note Time complexity: O(V * E) where V is the number of vertices (airports) and E is the number of edges (flights).
 */
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

/**
 * @brief Gets the number of flights per city.
 * @return A map where the key is the city name and the value is the number of flights.
 * @note Time complexity: O(V * E) where V is the number of vertices (airports) and E is the number of edges (flights).
 */
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

/**
 * @brief Calculates the number of flights per airline in the airport graph.
 *
 * This function iterates through the airport graph's edges and flights to count the number of flights operated by each airline.
 *
 * @return A map associating airline names with the number of flights they operate.
 * @note This function assumes that the airport graph has been properly constructed.
 *       Time complexity: O(V*E*F) where V is the number of vertices, E is the number of edges, and F is the average number of flights per edge.
 */
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



/**
 * @brief Gets the number of different countries reachable from a given airport.
 * @param airportCode The airport code.
 * @return The number of different countries.
 * @note Time complexity: O(E) where E is the number of edges (flights) from the given airport.
 */
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

/**
 * @brief Gets the number of different countries reachable from a given city.
 * @param city The name of the city.
 * @return The number of different countries.
 * @note Time complexity: O(E) where E is the number of edges (flights) from the given city.
 */
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




/**
 * @brief Finds all reachable airports from a given airport within a maximum number of stops.
 * @param airportCode The airport code.
 * @param maxStops The maximum number of layovers/stops.
 * @return A set of airport codes that are reachable.
 * @note Time complexity: O(V + E) where V is the number of vertices (airports) and E is the number of edges (flights).
 */
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

/**
 * @brief Retrieves a set of reachable cities from the specified airport with a maximum number of stops.
 *
 * This function uses breadth-first search to find reachable cities within a certain number of stops from the given airport.
 *
 * @param airportCode The code of the starting airport.
 * @param maxStops The maximum number of stops allowed in the search.
 * @return An unordered set of reachable city names.
 * @note This function assumes that the airport graph has been properly constructed.
 *       Time complexity: O(V*(V+E)) where V is the number of vertices and E is the number of edges.
 */
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

/**
 * @brief Retrieves a set of reachable countries from the specified airport with a maximum number of stops.
 *
 * This function uses breadth-first search to find reachable countries within a certain number of stops from the given airport.
 *
 * @param airportCode The code of the starting airport.
 * @param maxStops The maximum number of stops allowed in the search.
 * @return An unordered set of reachable country names.
 * @note This function assumes that the airport graph has been properly constructed.
 *       Time complexity: O(V*(V+E)) where V is the number of vertices and E is the number of edges.
 */
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




/**
 * @brief Performs a depth-first search to identify the longest path in the graph.
 * @param vertex The current vertex being explored in the DFS.
 * @param visited A set to track visited airports during the DFS.
 * @param path The current path being explored.
 * @param longestPaths A reference to store all the longest paths found.
 * @param maxLength The length of the longest path found so far.
 * @note This is a helper function for findLongestPath().
 *       Time complexity: O(V*(V+E)) where V is the number of vertices and E is the number of edges.
 */
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

/**
 * @brief Resets the visited status of all vertices in a graph.
 * @param graph The graph whose vertices will have their visited status reset.
 * @note Time complexity: O(V) where V is the number of vertices.
 */
void Statistics::resetVisited(Graph<Airport>& graph) {
    for (auto* vertex : graph.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }
}

/**
 * @brief Finds the longest path in the graph representing the maximum number of stops in a flight trip.
 * @return A vector of vectors, each representing a path with the maximum length.
 * @note Time complexity: O(V*(V+E)) where V is the number of vertices and E is the number of edges.
 */
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



/**
 * @brief Finds the top-k airports based on the number of flights.
 * @param k The number of top airports to identify.
 * @return A vector of pairs (Airport, int), where each pair contains an airport and its flight count.
 * @note Time complexity: O(V log V + E) where V is the number of vertices (airports) and E is the number of edges (flights).
 */
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


/**
 * @brief Finds articulation points (essential airports) in the airport graph.
 * @param v The current vertex being explored.
 * @param time The discovery time counter used in the DFS.
 * @param disc Discovery times of vertices.
 * @param low Earliest visited vertex (lowest discovery time) that can be reached from the subtree rooted at the current vertex.
 * @param parent Parent vertices in the DFS tree.
 * @param articulationPoints Set to store the articulation points found.
 * @note This is a helper function for findEssentialAirports().
 *       Time complexity: O(V + E) where V is the number of vertices and E is the number of edges.
 */
void Statistics::findArticulationPoints(Vertex<Airport>* v, int& time,
                                        std::unordered_map<Airport, int, AirportHash, AirportEqual>& disc,
                                        std::unordered_map<Airport, int, AirportHash, AirportEqual>& low,
                                        std::unordered_map<Airport, Vertex<Airport>*, AirportHash, AirportEqual>& parent,
                                        std::unordered_set<Airport, AirportHash, AirportEqual>& articulationPoints) {
    int children = 0;
    v->setVisited(true);
    disc[v->getInfo()] = low[v->getInfo()] = ++time;


    for (auto& edge : v->getAdj()) {
        Vertex<Airport>* child = edge.getDest();
        if (!child->isVisited()) {
            children++;
            parent[child->getInfo()] = v;
            findArticulationPoints(child, time, disc, low, parent, articulationPoints);
            low[v->getInfo()] = std::min(low[v->getInfo()], low[child->getInfo()]);
            if (parent[v->getInfo()] == nullptr && children > 1) {
                articulationPoints.insert(v->getInfo());
            }
            }
            if (parent[v->getInfo()] != nullptr && low[child->getInfo()] >= disc[v->getInfo()]) {
                articulationPoints.insert(v->getInfo());
            }
            else if (child != parent[v->getInfo()]) {
            low[v->getInfo()] = std::min(low[v->getInfo()], disc[child->getInfo()]);

        }
    }
}

/**
 * @brief Identifies articulation points (essential airports) in the graph.
 * @return A set of essential airports.
 * @note Time complexity: O(V + E) where V is the number of vertices and E is the number of edges.
 */
std::unordered_set<Airport, AirportHash, AirportEqual> Statistics::findEssentialAirports() {
    Graph<Airport> undirectedGraph = createUndirectedCopy(airportGraph);
    std::unordered_set<Airport, AirportHash, AirportEqual> articulationPoints;
    std::unordered_map<Airport, int, AirportHash, AirportEqual> disc, low;
    std::unordered_map<Airport, Vertex<Airport>*, AirportHash, AirportEqual> parent;
    int time = 0;

    for (auto* vertex : undirectedGraph.getVertexSet()) {
        disc[vertex->getInfo()] = -1;
        low[vertex->getInfo()] = -1;
        parent[vertex->getInfo()] = nullptr;
    }

    for (auto* vertex : undirectedGraph.getVertexSet()) {
        if (disc[vertex->getInfo()] == -1) {
            findArticulationPoints(vertex, time, disc, low, parent, articulationPoints);
        }
    }

    for (auto* vertex : undirectedGraph.getVertexSet()) {
        vertex->setVisited(false);
    }
    return articulationPoints;
}

/**
 * @brief Creates an undirected copy of a directed graph.
 * @param directedGraph The directed graph to copy.
 * @return An undirected copy of the input graph.
 * @note Time complexity: O(V + E) where V is the number of vertices and E is the number of edges.
 */
Graph<Airport> Statistics::createUndirectedCopy(const Graph<Airport>& directedGraph) {
    Graph<Airport> undirectedGraph;

    for (auto* vertex : directedGraph.getVertexSet()) {
        undirectedGraph.addVertex(vertex->getInfo());
        for (auto& edge : vertex->getAdj()) {
            Vertex<Airport>* dest = edge.getDest();
            undirectedGraph.addEdge(vertex->getInfo(), dest->getInfo(), 1);
            undirectedGraph.addEdge(dest->getInfo(), vertex->getInfo(), 1); // Add the reciprocal edge
        }
    }

    return undirectedGraph;
}

