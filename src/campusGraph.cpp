// Campus graph for buildings and connections.
#include "../include/campusGraph.h"

#include <algorithm>
#include <cctype>
#include <queue>

using namespace std;

// Removes whitespace around a value.
string CampusGraph::trim(const string& value) {
    size_t first = value.find_first_not_of(" \t\n\r\f\v");
    if (first == string::npos) {
        return "";
    }

    size_t last = value.find_last_not_of(" \t\n\r\f\v");
    return value.substr(first, last - first + 1);
}

// Makes names lowercase for matching.
string CampusGraph::normalize(const string& value) {
    string result = trim(value);
    for (char& character : result) {
        character = static_cast<char>(
            tolower(static_cast<unsigned char>(character)));
    }
    return result;
}

// Checks whether a line should be skipped.
bool CampusGraph::isCommentOrBlank(const string& line) {
    string value = trim(line);
    return value.empty() || value[0] == '#';
}

// Finds a building without regard to capitalization.
size_t CampusGraph::findBuilding(const string& name) const {
    string wanted = normalize(name);
    for (size_t i = 0; i < buildings.size(); ++i) {
        if (normalize(buildings[i].name) == wanted) {
            return i;
        }
    }
    return buildings.size();
}

// Loads buildings from a file.
void CampusGraph::loadBuildings(const string& fileName) {
    buildings.clear();
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << "\n";
        cout << fileName << ": 0 accepted, 0 rejected\n";
        return;
    }

    string line;
    size_t lineNumber = 0;
    int accepted = 0;
    int rejected = 0;
    while (getline(file, line)) {
        ++lineNumber;
        if (isCommentOrBlank(line)) {
            continue;
        }

        string name = trim(line);
        string reason;
        if (name.find('|') != string::npos) {
            reason = "expected one building name";
        } else if (findBuilding(name) != buildings.size()) {
            reason = "duplicate building name";
        }

        if (!reason.empty()) {
            cout << "Warning: " << fileName << " line " << lineNumber
                 << ": " << reason << "\n";
            ++rejected;
            continue;
        }

        buildings.push_back({name, {}});
        ++accepted;
    }

    cout << fileName << ": " << accepted << " accepted, "
         << rejected << " rejected\n";
}

// Loads undirected connections from a file.
void CampusGraph::loadConnections(const string& fileName) {
    for (Building& building : buildings) {
        building.neighbors.clear();
    }

    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error opening file: " << fileName << "\n";
        cout << fileName << ": 0 accepted, 0 rejected\n";
        return;
    }

    string line;
    size_t lineNumber = 0;
    int accepted = 0;
    int rejected = 0;
    while (getline(file, line)) {
        ++lineNumber;
        if (isCommentOrBlank(line)) {
            continue;
        }

        string reason;
        size_t separator = line.find('|');
        if (separator == string::npos ||
            line.find('|', separator + 1) != string::npos) {
            reason = "expected two building names";
        }

        string firstName;
        string secondName;
        if (reason.empty()) {
            firstName = trim(line.substr(0, separator));
            secondName = trim(line.substr(separator + 1));
            if (firstName.empty() || secondName.empty()) {
                reason = "empty building name";
            }
        }

        size_t first = buildings.size();
        size_t second = buildings.size();
        if (reason.empty()) {
            first = findBuilding(firstName);
            second = findBuilding(secondName);
            if (first == buildings.size()) {
                reason = "unknown building: " + firstName;
            } else if (second == buildings.size()) {
                reason = "unknown building: " + secondName;
            } else if (first == second) {
                reason = "self-connection";
            } else if (find(buildings[first].neighbors.begin(),
                            buildings[first].neighbors.end(), second) !=
                       buildings[first].neighbors.end()) {
                reason = "duplicate connection";
            }
        }

        if (!reason.empty()) {
            cout << "Warning: " << fileName << " line " << lineNumber
                 << ": " << reason << "\n";
            ++rejected;
            continue;
        }

        buildings[first].neighbors.push_back(second);
        buildings[second].neighbors.push_back(first);
        ++accepted;
    }

    cout << fileName << ": " << accepted << " accepted, "
         << rejected << " rejected\n";
}

// Displays all buildings and their neighbors.
void CampusGraph::display() const {
    if (buildings.empty()) {
        cout << "No buildings are available.\n";
        return;
    }

    for (const Building& building : buildings) {
        cout << building.name << ": ";
        if (building.neighbors.empty()) {
            cout << "(no connections)";
        } else {
            for (size_t i = 0; i < building.neighbors.size(); ++i) {
                if (i > 0) {
                    cout << ", ";
                }
                cout << buildings[building.neighbors[i]].name;
            }
        }
        cout << "\n";
    }
}

// Displays graph totals and the degree of each building.
void CampusGraph::displayCountsAndDegrees() const {
    if (buildings.empty()) {
        cout << "No buildings are available.\n";
    }

    size_t totalConnections = 0;
    for (const Building& building : buildings) {
        totalConnections += building.neighbors.size();
    }

    cout << "Total buildings: " << buildings.size() << "\n";
    cout << "Total connections: " << totalConnections / 2 << "\n";
    for (const Building& building : buildings) {
        cout << building.name << " degree: "
             << building.neighbors.size() << "\n";
    }
}

// Displays buildings reachable from the starting building using BFS.
void CampusGraph::displayReachable(const string& startName) const {
    size_t start = findBuilding(startName);
    if (start == buildings.size()) {
        cout << "Error: unknown building: " << trim(startName) << "\n";
        return;
    }

    vector<int> distance(buildings.size(), -1);
    queue<size_t> pending;
    distance[start] = 0;
    pending.push(start);
    size_t reachableCount = 0;

    cout << "Reachable buildings:\n";
    while (!pending.empty()) {
        size_t current = pending.front();
        pending.pop();
        cout << buildings[current].name << " (distance "
             << distance[current] << ")\n";
        ++reachableCount;

        for (size_t neighbor : buildings[current].neighbors) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[current] + 1;
                pending.push(neighbor);
            }
        }
    }

    cout << "Reachable count: " << reachableCount << " out of "
         << buildings.size() << "\n";
}
