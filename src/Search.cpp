#include "Search.h"

/**
 * @brief Constructs a new Search object.
 * @param graph Reference to the graph of airports.
 */
Search::Search(const Graph<Airport>& graph) : graph(graph) {
    for (const auto& vertex : graph.getVertexSet()) {
        const Airport& airport = vertex->getInfo();
        airportsByCode[airport.getCode()] = airport;
        airportsByCity[airport.getCity()].push_back(airport);
    }
}

/**
 * @brief Finds the best flight path from the source to the destination.
 * @param source The source location, which can be an airport code, city name, or coordinates.
 * @param destination The destination location, similar to source.
 * @return A vector of Airports representing the best flight path. Empty if no path is found.
 * @note Time complexity: O(V + E) where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
std::vector<Airport> Search::findBestFlight(const std::string& source, const std::string& destination) {
    // Resolve source and destination to actual airports
    std::vector<Airport> sourceAirports = resolveInput(source);
    std::vector<Airport> destinationAirports = resolveInput(destination);

    std::vector<Airport> shortestPath;
    int minStops = std::numeric_limits<int>::max();

    for (const auto& srcAirport : sourceAirports) {
        for (const auto& destAirport : destinationAirports) {
            auto path = bfsFindPath(srcAirport, destAirport);
            int stops = path.size() - 1; // Number of stops is one less than the number of airports in the path

            if (stops < minStops) {
                shortestPath = path;
                minStops = stops;
            }
        }
    }

    return shortestPath;
}

/**
 * @brief Performs a BFS to find the shortest path (least stops) between two airports.
 * @param src Source airport.
 * @param dest Destination airport.
 * @return A vector of Airports representing the path from src to dest. Empty if no path is found.
 * @note Time complexity: O(E) where E is the number of edges in the graph.
 */
std::vector<Airport> Search::bfsFindPath(const Airport& src, const Airport& dest) {
    std::queue<Airport> queue;
    std::unordered_map<Airport, Airport, AirportHash, AirportEqual> predecessors;
    std::unordered_set<Airport, AirportHash, AirportEqual> visited;

    queue.push(src);
    visited.insert(src);

    while (!queue.empty()) {
        Airport current = queue.front();
        queue.pop();

        if (current == dest) {
            return reconstructPath(predecessors, src, dest);
        }

        for (const auto& edge : graph.findVertex(current)->getAdj()) {
            Airport neighbor = edge.getDest()->getInfo();
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                predecessors[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    return std::vector<Airport>(); // Return empty vector if no path is found
}

/**
 * @brief Reconstructs the flight path from source to destination using the predecessors map.
 * @param predecessors A map of Airport to its predecessor Airport on the path.
 * @param src Source airport.
 * @param dest Destination airport.
 * @return A vector of Airports representing the path from src to dest.
 */
std::vector<Airport> Search::reconstructPath(const std::unordered_map<Airport, Airport, AirportHash, AirportEqual>& predecessors,
                                             const Airport& src, const Airport& dest) {
    std::vector<Airport> path;
    for (Airport at = dest; !(at == src); at = predecessors.at(at)) {
        path.push_back(at);
    }
    path.push_back(src);
    std::reverse(path.begin(), path.end());
    return path;
}

/**
 * @brief Resolves the user input to a list of corresponding airports.
 * @param input User input which can be an airport code, a city name, or geographical coordinates.
 * @return A vector of Airports corresponding to the input.
 * @note Time complexity: O(N) where N is the number of airports (for city names or coordinates).
 */
std::vector<Airport> Search::resolveInput(const std::string& input) {
    std::vector<Airport> airports;

    // Check if input is an airport code
    if (airportsByCode.find(input) != airportsByCode.end()) {
        airports.push_back(airportsByCode[input]);
    }
        // Check if input is a city name
    else if (airportsByCity.find(input) != airportsByCity.end()) {
        airports.insert(airports.end(), airportsByCity[input].begin(), airportsByCity[input].end());
    }
        // Handle coordinates input
    else {
        double inputLat, inputLon;
        if (parseCoordinates(input, inputLat, inputLon)) {
            Airport nearestAirport = findNearestAirport(inputLat, inputLon);
            if (!nearestAirport.getCode().empty()) {
                airports.push_back(nearestAirport);
            }
        }
    }

    return airports;
}

/**
 * @brief Finds the nearest airport to the given geographical coordinates.
 * @param lat Latitude.
 * @param lon Longitude.
 * @return The nearest Airport object. Empty if none found.
 * @note Time complexity: O(N) where N is the number of airports.
 */
Airport Search::findNearestAirport(double lat, double lon) {
    double minDistance = std::numeric_limits<double>::max();
    Airport nearestAirport;

    for (const auto& pair : airportsByCode) {
        const Airport& airport = pair.second;
        double distance = Haversine::haversineDistance(lat, lon, airport.getLatitude(), airport.getLongitude());

        if (distance < minDistance) {
            minDistance = distance;
            nearestAirport = airport;
        }
    }

    return nearestAirport;
}

/**
 * @brief Parses a string input into geographical coordinates.
 * @param input The string containing coordinates.
 * @param lat Reference to store latitude.
 * @param lon Reference to store longitude.
 * @return True if parsing is successful, false otherwise.
 */
bool Search::parseCoordinates(const std::string& input, double& lat, double& lon) {
    std::istringstream iss(input);
    char delimiter;

    if (iss >> lat >> delimiter && delimiter == ',' && iss >> lon) {
        return true;
    }

    return false;
}