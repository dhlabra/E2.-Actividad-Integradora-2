#include "algorithms.h"
#include <algorithm>
#include <cmath>
#include <climits>
#include <cfloat>
#include <queue>
#include <sstream>
#include <stack>

bool Edge::operator<(const Edge& other) const {
    return weight < other.weight;
}

int findParent(std::vector<int>& parent, int node) {
    if (parent[node] != node)
        parent[node] = findParent(parent, parent[node]);
    return parent[node];
}

void unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v) {
    int rootU = findParent(parent, u);
    int rootV = findParent(parent, v);
    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

std::vector<Edge> kruskal(int n, const std::vector<std::vector<int>>& graph) {
    std::vector<Edge> edges, mst;
    std::vector<int> parent(n), rank(n, 0);
    for (int i = 0; i < n; ++i)
        parent[i] = i;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (graph[i][j] != 0)
                edges.push_back({i, j, graph[i][j]});

    std::sort(edges.begin(), edges.end());
    for (const auto& edge : edges) {
        if (findParent(parent, edge.u) != findParent(parent, edge.v)) {
            mst.push_back(edge);
            unionSets(parent, rank, edge.u, edge.v);
        }
    }
    return mst;
}

std::pair<int, std::vector<int>> travelingSalesman(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> nodes(n - 1), bestPath;
    for (int i = 1; i < n; ++i) nodes[i - 1] = i;

    int minCost = INT_MAX;
    do {
        int currentCost = 0, currentNode = 0;
        for (int next : nodes) {
            currentCost += graph[currentNode][next];
            currentNode = next;
        }
        currentCost += graph[currentNode][0];
        if (currentCost < minCost) {
            minCost = currentCost;
            bestPath = nodes;
        }
    } while (std::next_permutation(nodes.begin(), nodes.end()));

    bestPath.insert(bestPath.begin(), 0);
    bestPath.push_back(0);
    return {minCost, bestPath};
}

bool bfs(const std::vector<std::vector<int>>& residualGraph, std::vector<int>& parent, int source, int sink) {
    int n = residualGraph.size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                if (v == sink) return true;
                q.push(v);
            }
        }
    }
    return false;
}

int fordFulkerson(std::vector<std::vector<int>> graph, int source, int sink) {
    int n = graph.size(), maxFlow = 0;
    std::vector<int> parent(n);
    std::vector<std::vector<int>> residualGraph = graph;

    while (bfs(residualGraph, parent, source, sink)) {
        int pathFlow = INT_MAX, v = sink;
        while (v != source) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residualGraph[u][v]);
            v = u;
        }
        v = sink;
        while (v != source) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
            v = u;
        }
        maxFlow += pathFlow;
    }
    return maxFlow;
}

std::pair<int, double> findNearestCentral(const std::vector<std::pair<int, int>>& centrals, std::pair<int, int> newHouse) {
    int nearestCentral = -1;
    double minDistance = DBL_MAX;
    for (int i = 0; i < centrals.size(); ++i) {
        double distance = std::sqrt(std::pow(centrals[i].first - newHouse.first, 2) + std::pow(centrals[i].second - newHouse.second, 2));
        if (distance < minDistance) {
            minDistance = distance;
            nearestCentral = i;
        }
    }
    return {nearestCentral, minDistance};
}

std::pair<int, int> parseCoordinates(const std::string& input) {
    int x, y;
    char ignore;
    std::stringstream ss(input);
    ss >> ignore >> x >> ignore >> y >> ignore;
    return{x,y};
}