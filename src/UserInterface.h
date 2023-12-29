#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Graph.h"
#include "Search.h"
#include "Statistics.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include <iostream>
#include <limits>
#include <string>
#include "Read.h"

class UserInterface {
public:
    UserInterface( );
    void handleFlightSearch();

    void run();

private:
    Graph<Airport> airportGraph;
    std::unordered_set<Airline> airlines;

    //HANDLE FUNCTIONS
    void clear();
    void handleStatistics();
    //DISPLAY FUNCTIONS
    void displayMainMenu();
    void displayFlightOptions(const std::vector<Airport>& path);
    void displayStatisticsOptions();
    //UTILITY
    std::string getUserInput(const std::string& prompt);
    void pauseScreen();
    void Title();
    void handleMainMenu(bool& running);
};

#endif // USERINTERFACE_H
