#include "Search.h"

std::vector<Airport> Search::findBestFlight(const std::string& source,
                                    const std::string& destination,
                                    const std::unordered_set<std::string>& preferredAirlines,
                                    bool minimizeAirlineChanges){
    std::vector<Airport> sourceAirports = resolveInput(source);
    std::vector<Airport> destinationAirports = resolveInput(destination);

    std::vector<Airport> shortestPath;
    int minStops = std::numeric_limits<int>::max();

    for (const auto& srcAirport : sourceAirports) {
        for (const auto& destAirport : destinationAirports) {
            auto path = bfsFindPathWithFilters(srcAirport, destAirport,preferredAirlines, minimizeAirlineChanges);
            int stops = path.size() - 1; // Num of stops is one less than the num of airports in the path

            if (stops < minStops) {
                shortestPath = path;
                minStops = stops;
            }
        }
    }

    return shortestPath;

}

//implement filters
std::vector<Airport> Search::bfsFindPathWithFilters(const Airport& src,
                                                    const Airport& dest,
                                                    const std::unordered_set<std::string>& preferredAirlines,
                                                    bool minimizeAirlineChanges) {
    struct QueueNode {
        Airport airport;
        std::string lastAirline;
        int airlineChanges;
    };

    std::queue<QueueNode> queue;
    std::unordered_map<Airport, Airport, AirportHash, AirportEqual> predecessors;
    std::unordered_map<Airport, std::string, AirportHash, AirportEqual> lastAirlines;
    std::unordered_map<Airport, int, AirportHash, AirportEqual> airlineChangesMap;
    std::unordered_set<Airport, AirportHash, AirportEqual> visited;

    queue.push({src, "", 0});
    visited.insert(src);
    airlineChangesMap[src] = 0;

    while (!queue.empty()) {
        QueueNode currentNode = queue.front();
        queue.pop();
        Airport current = currentNode.airport;
        std::string currentAirline = currentNode.lastAirline;
        int currentChanges = currentNode.airlineChanges;

        if (current == dest) {
            return reconstructPath(predecessors, src, dest);
        }

        for (const auto& edge : graph.findVertex(current)->getAdj()) {
            for (const auto& flight : edge.getFlights()) {  // Iterate over all flights on the edge
                Airport neighbor = edge.getDest()->getInfo();
                std::string nextAirline = flight.getAirline();
                int nextChanges = currentChanges + (currentAirline != nextAirline && !currentAirline.empty() ? 1 : 0);

                bool shouldConsiderFlight = (preferredAirlines.empty() || preferredAirlines.count(nextAirline)) &&
                                            (!visited.count(neighbor) ||
                                             (minimizeAirlineChanges && nextChanges < airlineChangesMap[neighbor]));

                if (shouldConsiderFlight) {
                    visited.insert(neighbor);
                    predecessors[neighbor] = current;
                    lastAirlines[neighbor] = nextAirline;
                    airlineChangesMap[neighbor] = nextChanges;
                    queue.push({neighbor, nextAirline, nextChanges});
                }
            }
        }
    }

    return std::vector<Airport>();
}


