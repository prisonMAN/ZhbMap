//
// Created by ZhouHB on 2023/9/8.
//

#ifndef ZHBMAP_MYMAP_H
#define ZHBMAP_MYMAP_H

#include <iostream>
#include <vector>
#include <queue>

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
            for (int i = 0; i < vexnum; i++) {
                this->Edge[vexnum][i] = INT_MAX;
                this->Edge[i][vexnum] = INT_MAX;
                if (this->Vex[i] == vertex) {
                    std::cerr << "请换一个名字" << std::endl;
                    return;
                }
            }
            this->Vex[vexnum] = vertex;
            vexnum += 1;
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
            if(Edge[x][y] == INT_MAX)
            {
                return 0;
            }
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
         * K算法实现
         */
    	void K()
        {
            auto sort = [](const int& a, const int& b) {
                return a > b;
            };
            std::priority_queue<int, std::vector<int>, decltype(sort)> pq(sort);

            std::vector<bool> visited(this->vexnum, false); // 用于标记是否已经读过该行

            for (int i = 0; i < this->vexnum; i++)
            {
                for (int j = 0; j < this->vexnum; j++)
                {
                    if (!visited[j]) // 未读过该行
                    {
                        pq.emplace(GetEdgeValue(i, j));
                    }
                }
                visited[i] = true; // 标记已读过该行
            }

            for (int i = 0; i < (this->vexnum - 1); i++)
            {
                std::cout << pq.top() << std::endl;
                pq.pop();
            }
        }

        /*
         * P算法实现
         */
        void P()
        {
	        
        }

        /*
         * Dijkstra算法实现
         */
        //FIXME:问题出现在最下面的while那里，需要将权跟节点在dist数组中的位置绑定，不然会有bug
        std::vector<std::pair<int, int>> Dijkstra(T source)
        {
            int num = FindVertexIndex(source);
            std::vector<int> dist(vexnum, INT_MAX); //距离数组
            dist[num] = 0;

            auto sort = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return a.first > b.first;
            };
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(sort)> pq(sort);

            //将起点的距离设置为0，将所有其他节点的距离设置为无穷大（或一个足够大的数），并将起点加入一个优先队列（或最小堆）中，按照距离从小到大排序。
			for(int i = 0; i < vexnum; i++)
			{
                pq.emplace(dist[i], i);
			}

            //从优先队列中取出距离最小的节点（当前最短路径的节点），遍历与其相邻的节点。对于每个相邻节点，计算通过当前最短路径节点到达它的距离，并与已知距离进行比较。
            //如果计算出的距离小于已知距离，则更新该节点的距离值，然后将其加入优先队列。
            while(!pq.empty())
            {
                int u = pq.top().second;
                pq.pop();


                for (int i = 0; i < this->vexnum; i++) {
                    if (i == u) {
                        continue;
                    }

                    int newDist = dist[u] + GetEdgeValue(u, i);
                    if (newDist < dist[i]) {
                        dist[i] = newDist;
                        pq.emplace(dist[i], i);
                    }
                }
            }

            //将结果送入result向量中
            std::vector<std::pair<int, int>> result;
            for (int i = 0; i < vexnum; i++)
            {
                result.emplace_back(dist[i], i);
            }


            return result;
        }

        void Floyd()
        {
            // 距离矩阵
            std::vector<std::vector<int>> W(this->vexnum, std::vector<int>(vexnum, INT_MAX));
            // 路由矩阵
            std::vector<std::vector<int>> R(this->vexnum, std::vector<int>(vexnum, -1));

            // 初始化距离矩阵和路由矩阵
            for (int i = 0; i < vexnum; i++)
            {
                W[i][i] = 0;
                for (int j = 0; j < vexnum; j++)
                {
                    if (i != j && Adjacent(i, j))
                    {
                        W[i][j] = GetEdgeValue(i, j);
                        R[i][j] = j;
                    }
                }
            }

            // 开始迭代矩阵
            for (int k = 0; k < vexnum; k++)
            {
                for (int i = 0; i < vexnum; i++)
                {
                    for (int j = 0; j < vexnum; j++)
                    {
                        if (W[i][k] + W[k][j] < W[i][j] && W[i][k] != INT_MAX && W[k][j] != INT_MAX)
                        {
                            W[i][j] = W[i][k] + W[k][j];
                            R[i][j] = R[i][k];
                        }
                    }
                }
            }
        }

    };


    class AdjListMap
    {
    private:

    };

} // myMap

#endif //ZHBMAP_MYMAP_H
