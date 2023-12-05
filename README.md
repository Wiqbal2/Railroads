# Railroads
This C++ project presents a sophisticated railroad simulation system, primarily leveraging a doubly linked list to model a dynamic and interconnected railroad network. The project exemplifies advanced object-oriented programming techniques, focusing on memory management, data structure utilization, and system design.
# Core features of Project 
* Doubly Linked List Implementation: At the heart of the simulation is a doubly linked list, where each node represents a station (Station class). This structure allows for efficient insertion and deletion of stations, as well as bidirectional traversal through the railroad network.
* Complex Network Modeling: Each station node is equipped with pointers in four directions (north, south, east, west), enabling the representation of a versatile and interconnected railway system.
* Dynamic Memory Management: The project demonstrates meticulous memory management, including constructors for resource allocation, destructors for resource deallocation, and a deep copy constructor for object duplication.
* Route Creation and Management: Functions like makeRoute and travel handle the logic for creating railway routes and calculating passenger totals.
* Robust Error Handling: The code includes checks for valid station codes, ensuring that the network maintains consistency and integrity during operations like adding or removing stations.
# Compiling 
Compile command for terminal: 
g++ -o RailroadSimulator railroad.cpp driver.cpp
# Run command 
./RailroadSimulator

