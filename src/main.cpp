#include <iostream>
#include "algorithms.h"

int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    std::vector<std::vector<int>> capacity(n, std::vector<int>(n));
    std::vector<std::pair<int, int>> locations;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> graph[i][j];

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            std::cin >> capacity[i][j];

    for (int i = 0; i < n; ++i) {
        std::string input;
        std::cin >> input;
        locations.push_back(parseCoordinates(input));
    }

    std::string newHouseInput;
    std::cin >> newHouseInput;
    auto newHouse = parseCoordinates(newHouseInput);

    auto mst = kruskal(n, graph);
    std::cout << "1. Forma de cablear las colonias:\n";
    for (const auto& edge : mst)
        std::cout << "(" << char('A' + edge.u) << ", " << char('A' + edge.v) << ")\n";

    auto [tspCost, tspPath] = travelingSalesman(graph);
    std::cout << "2. Ruta para correspondencia:\n";
    for (int node : tspPath)
        std::cout << char('A' + node) << " ";
    std::cout << "\n";

    int maxFlow = fordFulkerson(capacity, 0, n - 1);
    std::cout << "3. Flujo máximo de información: " << maxFlow << "\n";

    auto [nearestCentral, distance] = findNearestCentral(locations, newHouse);
    std::cout << "4. Central más cercana: (" << locations[nearestCentral].first << ", " << locations[nearestCentral].second << ")\n";

    return 0;
}