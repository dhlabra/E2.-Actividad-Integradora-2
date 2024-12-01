#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <string>
#include <utility>

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const;
};

int findParent(std::vector<int>& parent, int node);
void unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v);
std::vector<Edge> kruskal(int n, const std::vector<std::vector<int>>& graph);
std::pair<int, std::vector<int>> travelingSalesman(const std::vector<std::vector<int>>& graph);
bool bfs(const std::vector<std::vector<int>>& residualGraph, std::vector<int>& parent, int source, int sink);
int fordFulkerson(std::vector<std::vector<int>> graph, int source, int sink);
std::pair<int, double> findNearestCentral(const std::vector<std::pair<int, int>>& centrals, std::pair<int, int> newHouse);
std::pair<int, int> parseCoordinates(const std::string& input);

#endif//ALGORITHMS_H