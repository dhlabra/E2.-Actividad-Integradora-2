// algorithms_test.cpp
#include <gtest/gtest.h>
#include "algorithms.h"
#include <vector>
#include <utility>
#include <string>

// Prueba para parseCoordinates
TEST(AlgorithmsTest, ParseCoordinates) {
    std::string input = "(3,4)";
    auto coordinates = parseCoordinates(input);

    EXPECT_EQ(coordinates.first, 3);  // Verificar x
    EXPECT_EQ(coordinates.second, 4);  // Verificar y
}

// Prueba para findNearestCentral
TEST(AlgorithmsTest, FindNearestCentral) {
    std::vector<std::pair<int, int>> centrals = {{0, 0}, {5, 5}, {10, 10}};
    std::pair<int, int> newHouse = {2, 3};

    auto [nearestCentral, distance] = findNearestCentral(centrals, newHouse);

    EXPECT_EQ(nearestCentral, 0);  // La central más cercana es la que está en (0, 0)
    EXPECT_NEAR(distance, std::sqrt(13), 1e-6);  // Distancia esperada
}

// Prueba para Kruskal
TEST(AlgorithmsTest, Kruskal) {
    int n = 4;
    std::vector<std::vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 0, 3},
        {2, 0, 0, 4},
        {0, 3, 4, 0},
    };

    auto mst = kruskal(n, graph);

    EXPECT_EQ(mst.size(), 3);  // El MST debe tener n-1 aristas para un grafo de n nodos
    EXPECT_EQ(mst[0].weight, 1);  // Peso de la primera arista en el MST
}

// Prueba para Traveling Salesman Problem (TSP)
TEST(AlgorithmsTest, TravelingSalesman) {
    std::vector<std::vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0},
    };

    auto [minCost, bestPath] = travelingSalesman(graph);

    EXPECT_EQ(minCost, 80);  // Costo mínimo esperado
    EXPECT_EQ(bestPath.front(), 0);  // El primer nodo debe ser 0
    EXPECT_EQ(bestPath.back(), 0);  // El último nodo debe ser 0
}

// Prueba para Ford-Fulkerson
TEST(AlgorithmsTest, FordFulkerson) {
    std::vector<std::vector<int>> capacity = {
        {0, 16, 13, 0, 0, 0},
        {0, 0, 10, 12, 0, 0},
        {0, 4, 0, 0, 14, 0},
        {0, 0, 9, 0, 0, 20},
        {0, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 0, 0},
    };

    int maxFlow = fordFulkerson(capacity, 0, 5);

    EXPECT_EQ(maxFlow, 23);  // Flujo máximo esperado
}