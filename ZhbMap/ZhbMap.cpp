#include <iostream>
#include "myMap.hpp"


int main()
{
    myMap::AdjMatrixMap<int> map(10);
    map.InsertVertex(0);
    map.InsertVertex(1);
    map.InsertVertex(2);
    map.InsertVertex(3);
    map.AddEdge(0, 1);
    map.AddEdge(0, 1);
    map.AddEdge(0, 1);
    map.AddEdge(0, 3);
    map.AddEdge(0, 4);
    map.AddEdge(1, 0);
    map.AddEdge(1, 0);
    map.AddEdge(1, 0);
    map.AddEdge(2, 0);
    map.AddEdge(3, 0);
    map.AddEdge(3, 0);
    map.AddEdge(2, 1);
    map.AddEdge(1, 4);
    map.AddEdge(1, 2);
    map.AddEdge(1, 4);
    map.AddEdge(2, 3);
    map.AddEdge(3, 1);
    map.AddEdge(1, 2);
    map.AddEdge(1, 4);
    map.AddEdge(1, 3);
    map.AddEdge(1, 2);
    map.AddEdge(1, 4);
    map.AddEdge(1, 3);
    map.AddEdge(3, 2);
    //std::cout << map.GetEdgeValue(0, 1) << std::endl;
    //std::cout << map.FindVertexIndex(0) << std::endl;
    std::cout << INT_MAX << std::endl;
    map.PrintMap();
    map.Dijkstra(1);

    return 0;
}
