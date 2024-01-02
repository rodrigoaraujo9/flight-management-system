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
    void run();

private:
    Graph<Airport> airportGraph;
    std::unordered_set<Airline> airlines;

    //HANDLE FUNCTIONS
    void handleStatistics();
    void handleMainMenu(bool& running);
    void handleFilteredFlightSearch();
    void handleFlightSearch();
    //DISPLAY FUNCTIONS
    void displayMainMenu();
    void displayStatisticsOptions();
    //UTILITY
    std::string getUserInput(const std::string& prompt);
    void Title();
    void clear();
};

#endif // USERINTERFACE_H
