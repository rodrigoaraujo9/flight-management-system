cmake_minimum_required(VERSION 3.26)
project(Project_2_AED)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Project_2_AED
        src/Airline.cpp
        src/Airline.h
        src/Airport.h
        src/Flight.h
        src/Airport.cpp
        src/Flight.cpp
        src/Read.h
        src/Read.cpp
        src/Graph.h
        src/Statistics.h
        src/Statistics.cpp
        src/Search.h
        src/Search.cpp
        src/Haversine.h
        src/Haversine.cpp
        src/UserInterface.h
        src/UserInterface.cpp
        src/FilteredSearch.cpp
        src/MainTest.cpp
)
