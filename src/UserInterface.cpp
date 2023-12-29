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






//HANDLER FUNCTIONS
void UserInterface::handleMainMenu(bool& running) {
    int choice;

    while (true) {
        displayMainMenu();
        std::cout << "Enter your choice: ";
        if (std::cin >> choice) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline character

            switch (choice) {
                case 1:
                    handleFlightSearch();
                    break;
                case 2:
                    handleStatistics();
                    break;
                case 3:
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

void UserInterface::handleFlightSearch() {
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
    // Implementation for handling statistics display
}





//DISPLAY FUNCTIONS
void UserInterface::displayMainMenu() {
    Title();
    std::cout << "1. Search for Flights" << std::endl;
    std::cout << "2. View Statistics" << std::endl;
    std::cout << "3. Quit" << std::endl;
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
