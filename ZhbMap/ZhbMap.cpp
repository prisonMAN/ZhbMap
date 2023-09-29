#include <iostream>
#include "myMap.hpp"


int main()
{
    myMap::AdjMatrixMap<int> map(10);
    map.InsertVertex(0);
    map.InsertVertex(1);
    map.InsertVertex(2);
    map.InsertVertex(3);
    map.AddEdge(1, 1);
    std::cout << map.GetEdgeValue(0, 1) << std::endl;
    std::cout << map.FindVertexIndex(0) << std::endl;
    map.PrintMap();
    std::cout << std::numeric_limits<int>::max() << std::endl;

    return 0;
}
