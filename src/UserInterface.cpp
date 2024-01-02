#include "UserInterface.h"

UserInterface::UserInterface() {
    Read reader;
    std::string datasetPath = "../dataset/";
    reader.readAirports(airportGraph, datasetPath + "airports.csv");
    reader.readAirlines(airlines, datasetPath + "airlines.csv");
    reader.readFlights(airportGraph, datasetPath + "flights.csv");
}

//UTILITY
std::string UserInterface::getUserInput(const std::string& prompt) {
    std::cout << prompt;

    // Clear any errors and ignore leftover characters only if necessary
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string input;
    getline(std::cin, input);
    return input;
}


void UserInterface::pauseScreen() {
    std::cout << "Press enter to continue...";
    std::cin.get();
}

void UserInterface::Title() {
    std::cout << "===== Airport Management System =====" << std::endl;
}

void UserInterface::clear() {
        std::cout << std::endl << std::endl << std::endl;
}






//HANDLER FUNCTIONS
void UserInterface::handleMainMenu(bool& running) {
    int choice;

    while (true) {
        clear();
        displayMainMenu();
        std::cout << "Enter your choice: ";
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character

            switch (choice) {
                case 1:
                    handleFlightSearch();
                    break;
                case 2:
                    handleFilteredFlightSearch();
                    break;
                case 3:
                    handleStatistics();
                    break;
                case 4:
                    std::cout << "Exiting...\n";
                    running = false;
                    return;
                default:
                    std::cout << "Invalid option. Please try again.\n";
            }
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        }
    }

}

void UserInterface::handleFilteredFlightSearch() {
    clear();

    // Get source and destination from the user
    std::string source = getUserInput("Enter source (airport code, city name, or coordinates('latitude,longitude')): ");
    std::string destination = getUserInput("Enter destination (airport code, city name, or coordinates('latitude,longitude')): ");

    // Get preferred airlines from the user
    std::unordered_set<std::string> preferredAirlines;
    std::string airlineInput = getUserInput("Enter preferred airlines (comma-separated, leave empty for no preference): ");
    if (!airlineInput.empty()) {
        // Split the comma-separated input into individual airline codes
        std::istringstream ss(airlineInput);
        std::string airlineCode;
        while (std::getline(ss, airlineCode, ',')) {
            preferredAirlines.insert(airlineCode);
        }
    }

    // Get user preference for minimizing airline changes
    bool minimizeAirlineChanges;
    std::string minimizeInput = getUserInput("Minimize airline changes? (y/n): ");
    minimizeAirlineChanges = (minimizeInput == "y" || minimizeInput == "Y");

    // Create a Search object
    Search search(airportGraph); // Assuming airportGraph is accessible in UserInterface

    // Find the best flight with filters
    auto bestFlights = search.findBestFlight(source, destination, preferredAirlines, minimizeAirlineChanges);

    if (bestFlights.empty()) {
        std::cout << "No flights found from " << source << " to " << destination << " with the specified filters." << std::endl;
        return;
    }

    // Display the best flight path
    std::cout << "Best flight path from " << source << " to " << destination << " with filters:" << std::endl;
    std::cout << bestFlights[0].first.getName()<< " (" << bestFlights[0].first.getCode() << ") -> ";
    for (size_t i = 1; i < bestFlights.size(); ++i) {
        const auto& airport = bestFlights[i];
        std::cout << airport.second << " -> " << airport.first.getName() << " (" << airport.first.getCode() << ") -> ";
    }
    std::cout << "End" << std::endl;
}


void UserInterface::handleFlightSearch() {
    clear();
    // Get source and destination from the user
    std::string source = getUserInput("Enter source (airport code, city name, or coordinates('latitude,longitude')): ");
    std::string destination = getUserInput("Enter destination (airport code, city name, or coordinates('latitude,longitude')): ");

    // Create a Search object
    Search search(airportGraph); // Assuming airportGraph is accessible in UserInterface

    // Find the best flight
    auto bestFlights = search.findBestFlight(source, destination);
    if (bestFlights.empty()) {
        std::cout << "No flights found from " << source << " to " << destination << std::endl;
        return;
    }
    // Display the best flight path
    std::cout << "Best flight path from " << source << " to " << destination << ":" << std::endl;
    for (const auto& airport : bestFlights) {
        std::cout << airport.getName() << " (" << airport.getCode() << ") -> ";
    }
    std::cout << "End" << std::endl;

}



void UserInterface::handleStatistics() {

    int choice;
    bool done = false;
    std::string input;
    int maxStops, k;
    Statistics statistics(airportGraph, airlines);
    while (!done) {
        clear();
        displayStatisticsOptions();
        std::cout << "Enter your choice: ";
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character

        switch (choice) {
            case 1:
                std::cout << "Total number of airports: " << statistics.getTotalNumberOfAirports() << std::endl;
                break;
            case 2:
                std::cout << "Total number of flights: " << statistics.getTotalNumberOfFlights() << std::endl;
                break;
            case 3:
                std::cout << "Enter airport code: ";
                getline(std::cin, input);
                std::cout << "Number of flights from " << input << ": " << statistics.getNumberOfFlightsFromAirport(input) << std::endl;
                break;
            case 4:
                std::cout << "Enter airport code: ";
                getline(std::cin, input);
                std::cout << "Number of unique airlines from " << input << ": " << statistics.getNumberOfUniqueAirlinesFromAirport(input) << std::endl;
                break;
            case 5:
                // Assuming this function returns a map and you want to display the contents
                for (const auto& pair : statistics.getNumberOfFlightsPerCityAirline()) {
                    std::cout << "City: " << pair.first.first << ", Airline: " << pair.first.second << ", Flights: " << pair.second << std::endl;
                }
            case 6:
                std::cout << "Number of flights per city:" << std::endl;
                for (const auto& pair : statistics.getNumberOfFlightsPerCity()) {
                    std::cout << "City: " << pair.first << ", Flights: " << pair.second << std::endl;
                }
                break;
            case 7:
                std::cout << "Number of flights per airline:" << std::endl;
                for (const auto& pair : statistics.getNumberOfFlightsPerAirline()) {
                    std::cout << "Airline: " << pair.first << ", Flights: " << pair.second << std::endl;
                }
                break;
            case 8:
                std::cout << "Enter airport code: ";
                getline(std::cin, input);
                std::cout << "Number of different countries reachable from " << input << ": " << statistics.getNumberOfDiffCountriesByAirport(input) << std::endl;
                break;
            case 9:
                std::cout << "Enter city name: ";
                getline(std::cin, input);
                std::cout << "Number of different countries reachable from " << input << ": " << statistics.getNumberOfDiffCountriesByCity(input) << std::endl;
                break;
            case 10: {
                std::cout << "Enter airport code: ";
                getline(std::cin, input);
                std::cout << "Enter maximum number of stops: ";
                std::cin >> maxStops;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                auto reachableAirports = statistics.getReachableAirports(input, maxStops); // Store result in a variable
                for (const auto& airport : reachableAirports) {
                    std::cout << airport << std::endl;
                }
                std::cout << "Number of reachable airports: " << reachableAirports.size() << std::endl;
                break;
            }
            case 11: {
                std::cout << "Enter airport code: ";
                getline(std::cin, input);
                std::cout << "Enter maximum number of stops: ";
                std::cin >> maxStops;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                auto reachableCities = statistics.getReachableCities(input, maxStops); // Store result in a variable
                for (const auto& city : reachableCities) {
                    std::cout << city << std::endl;
                }
                std::cout << "Number of reachable cities: " << reachableCities.size() << std::endl;
                break;
            }
            case 12: {
                std::cout << "Enter airport code: ";
                getline(std::cin, input);
                std::cout << "Enter maximum number of stops: ";
                std::cin >> maxStops;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                auto reachableCountries = statistics.getReachableCountries(input, maxStops); // Store result in a variable
                for (const auto& country : reachableCountries) {
                    std::cout << country << std::endl;
                }
                std::cout << "Number of reachable countries: " << reachableCountries.size() << std::endl;
                break;
            }
            case 13: {
                auto longestPath = statistics.findLongestPath(); // Store result in a variable
                for (const auto& path : longestPath) {
                    for (const auto& airport : path) {
                        std::cout << airport.getCode() << " -> ";
                    }
                    std::cout << std::endl;
                }
                std::cout << "Path length: " << longestPath.size() << std::endl;
                break;
            }
            case 14:
                std::cout << "Enter the number K: ";
                std::cin >> k;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                for (const auto& pair : statistics.getTopKAirportsByFlights(k)) {
                    std::cout << "Airport: " << pair.first.getCode() << ", Flights: " << pair.second << std::endl;
                }
                break;
            case 15: {
                auto essentialAirports = statistics.findEssentialAirports(); // Store result in a variable
                for (const auto& airport : essentialAirports) {
                    std::cout << airport.getCode() << std::endl;
                }
                std::cout << "Number of essential airports: " << essentialAirports.size() << std::endl;
                break;
            }
            case 16:
                done = true;
                break;
            case 17:
                exit(0);
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}





//DISPLAY FUNCTIONS
void UserInterface::displayMainMenu() {
    Title();
    std::cout << "1. Search for Flights" << std::endl;
    std::cout << "2. Search For Flights with Filters" << std::endl;
    std::cout << "3. View Statistics" << std::endl;
    std::cout << "4. Quit" << std::endl;
}

void UserInterface::displayFlightOptions(const std::vector<Airport>& path) {
    Title();
    if (path.empty()) {
        std::cout << "No flight path available." << std::endl;
        return;
    }
    for (size_t i = 0; i < path.size(); ++i) {
        const Airport& airport = path[i];
        std::cout << airport.getName() << " (" << airport.getCode() << ")";
        if (i < path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

void UserInterface::displayStatisticsOptions() {
    Title();
    std::cout << "1. Total number of airports" << std::endl;
    std::cout << "2. Total number of flights" << std::endl;
    std::cout << "3. Number of flights from a specific airport" << std::endl;
    std::cout << "4. Number of unique airlines from a specific airport" << std::endl;
    std::cout << "5. Number of flights per city/airline" << std::endl;
    std::cout << "6. Number of flights per city" << std::endl;
    std::cout << "7. Number of flights per airline" << std::endl;
    std::cout << "8. Number of different countries reachable from a specific airport" << std::endl;
    std::cout << "9. Number of different countries reachable from a specific city" << std::endl;
    std::cout << "10. Reachable airports from a specific airport within X stops" << std::endl;
    std::cout << "11. Reachable cities from a specific airport within X stops" << std::endl;
    std::cout << "12. Reachable countries from a specific airport within X stops" << std::endl;
    std::cout << "13. Find the longest flight path" << std::endl;
    std::cout << "14. Top K airports with the most flights" << std::endl;
    std::cout << "15. Find essential airports for network circulation" << std::endl;
    std::cout << "16. Return" << std::endl;
    std::cout << "17. Quit" << std::endl;
}





//INTERFACE LOOP
void UserInterface::run() {
    bool running = true;
    while (running) {
        handleMainMenu(running);

    }
}
