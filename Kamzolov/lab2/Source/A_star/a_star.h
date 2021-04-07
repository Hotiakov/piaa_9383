#ifndef ASTAR_H
#define ASTAR_H

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>

#define INF 3.40282e+038

struct Node {
    std::vector<std::pair<Node*, float>> neighbours;
    char vertex;
    float priority;
    Node* prev = nullptr;
    Node(char vertex, float priority = INF) : vertex(vertex), priority(priority) {}
};

int customFind(std::vector<Node*>& graph, char& vertex);
void initGraph(std::vector<Node*>& graph, char& start, char& finish, std::istream& in);
std::string algo(std::vector<Node*>& graph, char& finish);
int heuristic(char& start, char& finish);
void freeMemory(std::vector<Node*>& vec);
std::string vecToString(std::vector<Node*>& vec);

#endif
