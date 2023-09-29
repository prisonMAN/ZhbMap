#include <iostream>
#include "myMap.h"


int main()
{
    myMap::AdjMatrixMap<int> map(10);
    map.InsertVertex(0);
    map.InsertVertex(1);
    map.AddEdge(0, 1);
    std::cout << map.FindVertexIndex(0) << std::endl;

    return 0;
}
