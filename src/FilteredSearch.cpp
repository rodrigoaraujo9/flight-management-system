#include "Search.h"
/**
 * @brief Finds the best flight path from the source to the destination.
 *
 * This function searches for the best flight path from the source location
 * to the destination location, considering optional filters such as preferred
 * airlines and minimizing airline changes.
 *
 * @param source The source location, which can be an airport code, city name, or coordinates.
 * @param destination The destination location, similar to source.
 * @param preferredAirlines A set of preferred airline codes. Flights operated by these airlines are favored.
 * @param minimizeAirlineChanges If true, the algorithm attempts to minimize airline changes in the path.
 * @return A vector of pairs, where each pair consists of an Airport and a corresponding airline code,
 *         representing the best flight path. The path starts with the source location and ends at the destination.
 *         Returns an empty vector if no path is found.
 *
 * @note Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
std::vector<std::pair<Airport, std::string>> Search::findBestFlight(
        const std::string& source,
        const std::string& destination,
        const std::unordered_set<std::string>& preferredAirlines,
        bool minimizeAirlineChanges)
{
    std::vector<Airport> sourceAirports = resolveInput(source);
    std::vector<Airport> destinationAirports = resolveInput(destination);

    std::vector<std::pair<Airport, std::string>> bestPath;
    int minStops = std::numeric_limits<int>::max();

    for (const auto& srcAirport : sourceAirports) {
        for (const auto& destAirport : destinationAirports) {
            auto pathWithAirlines = bfsFindPathWithFilters(srcAirport, destAirport, preferredAirlines, minimizeAirlineChanges);
            int stops = pathWithAirlines.size() - 1; // Number of stops is one less than the number of airports in the path

            if (stops < minStops) {
                bestPath = std::move(pathWithAirlines);
                minStops = stops;
            }
        }
    }

    return bestPath;
}

/**
 * @brief Breadth-First Search (BFS) to find a flight path with optional filters.
 *
 * This function performs a BFS to find a flight path from the source airport to the destination airport,
 * considering optional filters such as preferred airlines and minimizing airline changes.
 *
 * @param src The source airport.
 * @param dest The destination airport.
 * @param preferredAirlines A set of preferred airline codes. Flights operated by these airlines are favored.
 * @param minimizeAirlineChanges If true, the algorithm attempts to minimize airline changes in the path.
 * @return A vector of pairs, where each pair consists of an Airport and a corresponding airline code,
 *         representing the flight path from the source to the destination. The path includes both airports and airlines.
 *         Returns an empty vector if no path is found.
 *
 * @note Time complexity: O(V + E), where V is the number of vertices (airports) and E is the number of edges (flights) in the graph.
 */
std::vector<std::pair<Airport, std::string>> Search::bfsFindPathWithFilters(
        const Airport& src,
        const Airport& dest,
        const std::unordered_set<std::string>& preferredAirlines,
        bool minimizeAirlineChanges)
{
    struct QueueNode {
        Airport airport;
        std::vector<std::pair<Airport, std::string>> path;  // Path including airports and airlines
        std::string lastAirline;
        int airlineChanges;
    };

    std::queue<QueueNode> queue;
    std::unordered_set<Airport, AirportHash, AirportEqual> visited;

    // Initialize the path with the source airport and an empty string
    std::vector<std::pair<Airport, std::string>> initialPath = {{src, ""}};

    queue.push({src, initialPath, "", 0});  // Push the source airport with the initial path
    visited.insert(src);

    while (!queue.empty()) {
        QueueNode currentNode = queue.front();
        queue.pop();
        Airport currentAirport = currentNode.airport;
        std::string currentAirline = currentNode.lastAirline;
        int currentChanges = currentNode.airlineChanges;

        if (currentAirport == dest) {
            // No need to remove the initial dummy airline entry for the source airport
            return currentNode.path;
        }

        for (const auto& edge : graph.findVertex(currentAirport)->getAdj()) {
            for (const auto& flight : edge.getFlights()) {
                Airport nextAirport = edge.getDest()->getInfo();
                std::string nextAirline = flight.getAirline();

                if ((preferredAirlines.empty() || preferredAirlines.count(nextAirline)) &&
                    !visited.count(nextAirport)) {
                    int nextChanges = currentChanges + (currentAirline != nextAirline && !currentAirline.empty() ? 1 : 0);

                    if (!minimizeAirlineChanges || nextChanges <= currentChanges) {
                        visited.insert(nextAirport);

                        // Prepare a new path with the current flight
                        auto newPath = currentNode.path;
                        newPath.emplace_back(nextAirport, nextAirline); // Record the next airport with its corresponding airline

                        // Push the new state to the queue
                        queue.push({nextAirport, newPath, nextAirline, nextChanges});
                    }
                }
            }
        }
    }

    return std::vector<std::pair<Airport, std::string>>();  // Return empty path if no path is found
}

