//
// Created by ZhouHB on 2023/9/8.
//

#ifndef ZHBMAP_MYMAP_H
#define ZHBMAP_MYMAP_H

#include <iostream>
#include <vector>

namespace myMap {

    template <typename T>
    class AdjMatrixMap
	{
    private:
        int MaxVertexNum; //顶点最大数目
        T* Vex; //顶点表
        int** Edge; //邻接矩阵，边表
        int vexnum; //图的当前顶点数
        int arcnum; //图的当前边数

    public:
        AdjMatrixMap(int num) :
            MaxVertexNum(num)
        {
            Edge = new int* [MaxVertexNum];
            for (int i = 0; i < MaxVertexNum; i++) {
                Edge[i] = new int[MaxVertexNum];
            }
            for (int i = 0; i < MaxVertexNum; i++) {
                for (int j = 0; j < MaxVertexNum; j++) {
                    Edge[i][j] = INT_MAX;
                }
            }

            this->Vex = new T[MaxVertexNum];

            this->vexnum = 0;
            this->arcnum = 0;
        }

        ~AdjMatrixMap()
        {
            for (int i = 0; i < this->MaxVertexNum; i++) {
                delete[] this->Edge[i];
            }
            delete[] Edge;
            delete[] Vex;
        }

        /*
         * 判断图G是否存在边<x,y>或者(x,y)
         */
        bool Adjacent(int x, int y) const
        {
            if (this->Edge[x][y] != INT_MAX) {
                return false;
            }
            else {
                return true;
            }
        }

        /*
         * 找到并返回该结点在图中的索引位置
         */
        int FindVertexIndex(T vertex)
        {
            for (int i = 0; i < this->vexnum; i++) {
                if (this->Vex[i] == vertex) {
                    return i;
                }
            }
            return -1;
        }

        /*
         * 列出图G中与结点Vex邻接的边
         */
        void Neighbors(T vertex)
        {
            int vertexIndex = FindVertexIndex(vertex);
            if (vertexIndex == -1) {
                return;  // 无效节点，直接返回
            }

            for (int i = 0; i < this->MaxVertexNum; i++) {
                if (Edge[vertexIndex][i] != INT_MAX) {
                    std::cout << i << "与该节点相连" << std::endl;
                }
            }
        }

        /*
         * 在图中插入顶点Vex
         */
        void InsertVertex(T vertex)
        {
            vexnum += 1;
            for (int i = 0; i < vexnum; i++) {
                this->Edge[vexnum][i] = INT_MAX;
                this->Edge[i][vexnum] = INT_MAX;
                if (this->Vex[i] == vertex) {
                    std::cerr << "请换一个名字" << std::endl;
                    return;
                }
            }
            this->Vex[vexnum] = vertex;
        }

        /*
         * 从图中删除顶点Vex
         */
        void DeleteVertex(T vertex)
        {
            int num = FindVertexIndex(vertex);
            for (int i = 0; i < this->vexnum; i++) {
                this->Edge[num][i] = INT_MAX;
                this->Edge[i][num] = INT_MAX;
            }
            vexnum -= 1;
        }

        /*
         * 若无向边(x,y)或有向边<x,y>不存在，则从图中添加该边
         */
        void AddEdge(int x, int y)
        {
            if (x > this->vexnum || y > this->vexnum) {
                std::cerr << "该边不在可添加范围内" << std::endl;
                return;
            }
            if (Edge[x][y] == INT_MAX) {
                Edge[x][y] = 0;
            }
            Edge[x][y] += 1;
        }

        /*
         * 若无向边(x,y)或有向边<x,y>存在，则从图中删除该边
         */
        void RemoveEdge(int x, int y)
        {
            if (x > this->vexnum || y > this->vexnum) {
                std::cerr << "该边不在可删除范围内" << std::endl;
                return;
            }
            if (Edge[x][y] == 0) {
                return;
            }
            Edge[x][y] -= 1;
        }

        /*
         * 求图中顶点x的第一个邻接点，若有则返回顶点号。若x没有邻接点或图中不存在x，则返回-1
         */
        int FirstNeighbor(T vertex)
        {
            int num = FindVertexIndex(vertex);

            for (int i = 0; i < num; i++)
            {
                if (Edge[num][i] != 0 || Edge[i][num] != 0) {
                    return num;
                }
            }
        }

        /*
         * 假设图中顶点y是顶点x的一个邻接点，返回除y之外顶点x的下一个邻接点的顶点号，若y是x的最后一个邻接点，则返回-1
         */
        int NextNeighbor(int x, int y)
        {
            return 0;
        }

        /*
         * 获取图中边(x,y)或<x,y>对应的权值
         */
        int GetEdgeValue(int x, int y) const
        {
            return Edge[x][y];
        }

        /*
         * 设置图中边(x,y)或<x,y>对应的权值
         */
        int SetEdgeValue(int x, int y, int v)
        {
            Edge[x][y] = v;

            return 0;
        }

        /*
         * 打印出来当前的图
         */
        void PrintMap()
        {
            for (int i = 0; i < vexnum; i++) {
                for (int j = 0; j < vexnum; j++) {
                    int edgeValue = GetEdgeValue(i, j);
                    if (edgeValue != INT_MAX) {
                        std::cout << edgeValue << " ";
                    }
                    else {
                        std::cout << "0 "; 
                    }
                }
                std::cout << std::endl;
            }
        }

        /*
         * Dijkstra算法实现
         */
        std::vector<int> Dijkstra(T source)
        {
            std::vector<int> dist(vexnum, std::numeric_limits<int>::max());
            dist[FindVertexIndex(source)] = 0;


            


        }

    };



    class AdjListMap
    {
    private:

    };

} // myMap

#endif //ZHBMAP_MYMAP_H
