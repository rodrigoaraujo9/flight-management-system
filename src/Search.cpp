#include "Search.h"

Search::Search(const Graph<Airport>& graph) : graph(graph) {
    for (const auto& vertex : graph.getVertexSet()) {
        const Airport& airport = vertex->getInfo();
        airportsByCode[airport.getCode()] = airport;
        airportsByCity[airport.getCity()].push_back(airport);
    }
}


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


bool Search::parseCoordinates(const std::string& input, double& lat, double& lon) {
    std::istringstream iss(input);
    char delimiter;

    if (iss >> lat >> delimiter && delimiter == ',' && iss >> lon) {
        return true;
    }

    return false;
}