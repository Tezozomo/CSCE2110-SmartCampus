// Campus graph for buildings and connections.
#ifndef CAMPUS_GRAPH_H
#define CAMPUS_GRAPH_H

#include "libraries.h"

class CampusGraph {
public:
    void loadBuildings(const std::string& fileName);
    void loadConnections(const std::string& fileName);
    void display() const;
    void displayCountsAndDegrees() const;
    void displayReachable(const std::string& startName) const;

private:
    struct Building {
        std::string name;
        std::vector<std::size_t> neighbors;
    };

    std::vector<Building> buildings;

    static std::string trim(const std::string& value);
    static std::string normalize(const std::string& value);
    static bool isCommentOrBlank(const std::string& line);
    std::size_t findBuilding(const std::string& name) const;
};

#endif
