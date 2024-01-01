#include "Graph.h"
#include "Airport.h"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include <algorithm>
#include "Haversine.h"
#include <string>
#include <sstream>

class Search {
public:
    Search(const Graph<Airport>& graph);

    std::vector<Airport> findBestFlight(const std::string& source, const std::string& destination);

    std::vector<Airport> findBestFlight(const std::string& source,
                                                                        const std::string& destination,
                                                                        const std::unordered_set<std::string>& preferredAirlines,
                                                                        bool minimizeAirlineChanges);


private:
    const Graph<Airport>& graph;
    std::unordered_map<std::string, Airport> airportsByCode;
    std::unordered_map<std::string, std::vector<Airport>> airportsByCity;

    //AUX
    std::vector<Airport> bfsFindPath(const Airport& src, const Airport& dest);
    std::vector<Airport> reconstructPath(const std::unordered_map<Airport, Airport, AirportHash, AirportEqual>& predecessors,
                                                 const Airport& src, const Airport& dest);
    std::vector<Airport> resolveInput(const std::string& input);
    Airport findNearestAirport(double lat, double lon);
    bool parseCoordinates(const std::string& input, double& lat, double& lon);
    std::vector<Airport> bfsFindPathWithFilters(const Airport& src,
                                                const Airport& dest,
                                                const std::unordered_set<std::string>& preferredAirlines,
                                                bool minimizeAirlineChanges);

};


