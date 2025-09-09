# Flight Management System

A comprehensive C++ flight management system that provides intelligent flight routing, network analysis, and airline statistics using graph algorithms and data structures.

## Technologies

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![Graph Algorithms](https://img.shields.io/badge/Graph_Algorithms-FF6B35?style=flat)
![Data Structures](https://img.shields.io/badge/Data_Structures-4CAF50?style=flat)
![STL](https://img.shields.io/badge/STL-2196F3?style=flat)

**Core Technologies:**
- **C++17**: Modern C++ with template programming and STL containers
- **Graph Theory**: BFS, DFS, articulation points, and pathfinding algorithms
- **Data Structures**: Hash tables, adjacency lists, priority queues
- **Geographic Computing**: Haversine distance calculations
- **File I/O**: CSV parsing and data loading
- **Object-Oriented Design**: Encapsulation, inheritance, and polymorphism

## Overview

This system models the global airline network as a directed graph where airports are vertices and flights are edges. It implements sophisticated algorithms for flight path optimization, network analysis, and statistical insights into airline operations.

## Key Features

### 🛫 Flight Search & Routing
- **Multi-input Support**: Search by airport code, city name, or GPS coordinates
- **Optimal Path Finding**: BFS-based algorithm to find routes with minimum stops
- **Filtered Search**: Advanced filtering by preferred airlines and minimizing airline changes
- **Coordinate-based Search**: Find nearest airports using Haversine distance calculation

### 📊 Network Analytics
- **Reachability Analysis**: Find all destinations within X stops from any airport
- **Network Statistics**: Comprehensive metrics on flights, airlines, and routes
- **Essential Airport Detection**: Identify critical airports using articulation point algorithms
- **Longest Path Analysis**: Discover maximum possible flight sequences

### 🏢 Airline Intelligence
- **Traffic Analysis**: Flight volume by city, airline, and route
- **Market Insights**: Top-performing airports and airline distribution
- **Geographic Coverage**: Country reachability analysis per airport/city

## Technical Architecture

### Core Components

```
├── Graph System
│   ├── Graph.h/cpp          # Template-based graph implementation
│   ├── Vertex & Edge        # Graph structure with flight data
│   └── Flight.h/cpp         # Flight model with airline information
├── Data Models
│   ├── Airport.h/cpp        # Airport with coordinates and metadata
│   ├── Airline.h/cpp        # Airline information and operators
│   └── Flight.h/cpp         # Flight connections and airline codes
├── Core Algorithms
│   ├── Search.h/cpp         # BFS pathfinding and input resolution
│   ├── FilteredSearch.cpp   # Advanced search with constraints
│   ├── Statistics.h/cpp     # Network analysis algorithms
│   └── Haversine.h/cpp      # Geographic distance calculations
├── System Interface
│   ├── UserInterface.h/cpp  # Interactive console interface
│   ├── Read.h/cpp          # CSV data loading and parsing
│   └── Main.cpp            # Application entry point
```

### Algorithm Complexity

| Operation | Time Complexity | Description |
|-----------|----------------|-------------|
| Flight Search | O(V + E) | BFS traversal of airport network |
| Filtered Search | O(V + E) | BFS with airline/change constraints |
| Reachability | O(V + E) | Multi-level BFS with stop limits |
| Essential Airports | O(V + E) | Tarjan's articulation points algorithm |
| Longest Path | O(V × (V + E)) | DFS from each vertex |
| Nearest Airport | O(N) | Linear search with Haversine distance |

## Data Structure Design

### Graph Implementation
- **Template-based**: Generic graph supporting any vertex type
- **Adjacency List**: Efficient storage for sparse airline networks
- **Multiple Flights**: Edges store sets of flights between airports
- **Weighted Edges**: Flight count as edge weight

### Hash-based Lookups
- **Airport Hashing**: Custom hash functions for efficient airport lookup
- **Airline Comparison**: Optimized operators for airline matching
- **Flight Deduplication**: Unordered sets prevent duplicate flight entries

## Installation & Usage

### Prerequisites
- C++17 compatible compiler (GCC 7+ or equivalent)
- Standard library support

### Building the Project
```bash
# Clone the repository
git clone https://github.com/yourusername/flight-management-system.git
cd flight-management-system

# Compile the project
g++ -std=c++17 -O2 *.cpp -o flight_manager

# Run the application
./flight_manager
```

### Data Format
Place CSV files in the `dataset/` directory:
- `airports.csv`: Airport code, name, city, country, latitude, longitude
- `airlines.csv`: Airline code, name, callsign, country
- `flights.csv`: Source airport, destination airport, airline code

### Example Usage

#### Basic Flight Search
```
Enter source: JFK
Enter destination: LAX
Result: John F. Kennedy International (JFK) -> Los Angeles International (LAX)
```

#### Coordinate-based Search
```
Enter source: 40.7128,-74.0060
Enter destination: London
Result: [Nearest airport to coordinates] -> London Heathrow (LHR)
```

#### Filtered Search
```
Enter source: NYC
Enter destination: Tokyo
Preferred airlines: AA,BA,JL
Minimize changes: y
Result: Optimized route with preferred airlines and minimal changes
```

## System Capabilities

### Search Functionality
- **Input Flexibility**: Airport codes, city names, or GPS coordinates
- **Multi-airport Cities**: Handles cities with multiple airports
- **Intelligent Routing**: Finds optimal paths considering constraints
- **Real-time Filtering**: Dynamic airline and route preferences

### Statistical Analysis
- **Network Metrics**: Total airports, flights, and connectivity
- **Performance Analytics**: Flights per airport, airline, and city
- **Geographic Analysis**: Country reachability and coverage
- **Critical Infrastructure**: Essential airports for network connectivity

### Advanced Features
- **Articulation Points**: Identify airports critical for network connectivity
- **Distance Calculations**: Haversine formula for geographic distance
- **Longest Paths**: Maximum flight sequences possible in the network
- **Top-K Analysis**: Highest performing airports by flight volume

## Contributing

This project demonstrates advanced C++ concepts including:
- Template programming and generic data structures
- Graph algorithms and network analysis
- Geographic computations and coordinate systems
- Object-oriented design with proper encapsulation
- Efficient hash-based data structures

## License

This project is available under the MIT License. See LICENSE file for details.

---

**Note**: This system is designed for educational and research purposes, demonstrating complex algorithms and data structures in a real-world domain.
