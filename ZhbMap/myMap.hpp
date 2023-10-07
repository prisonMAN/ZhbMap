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
        int MaxVertexNum; //���������Ŀ
        T* Vex; //�����
        int** Edge; //�ڽӾ��󣬱߱�
        int vexnum; //ͼ�ĵ�ǰ������
        int arcnum; //ͼ�ĵ�ǰ����

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
         * �ж�ͼG�Ƿ���ڱ�<x,y>����(x,y)
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
         * �ҵ������ظý����ͼ�е�����λ��
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
         * �г�ͼG������Vex�ڽӵı�
         */
        void Neighbors(T vertex)
        {
            
            int vertexIndex = FindVertexIndex(vertex);
            if (vertexIndex == -1) {
                return;  // ��Ч�ڵ㣬ֱ�ӷ���
            }

            for (int i = 0; i < this->MaxVertexNum; i++) {
                if (Edge[vertexIndex][i] != INT_MAX) {
                    std::cout << i << "��ýڵ�����" << std::endl;
                }
            }
        }

        /*
         * ��ͼ�в��붥��Vex
         */
        void InsertVertex(T vertex)
        {
            for (int i = 0; i < vexnum; i++) {
                this->Edge[vexnum][i] = INT_MAX;
                this->Edge[i][vexnum] = INT_MAX;
                if (this->Vex[i] == vertex) {
                    std::cerr << "�뻻һ������" << std::endl;
                    return;
                }
            }
            this->Vex[vexnum] = vertex;
            vexnum += 1;
        }

        /*
         * ��ͼ��ɾ������Vex
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
         * �������(x,y)�������<x,y>�����ڣ����ͼ����Ӹñ�
         */
        void AddEdge(int x, int y)
        {
            if (x > this->vexnum || y > this->vexnum) {
                std::cerr << "�ñ߲��ڿ���ӷ�Χ��" << std::endl;
                return;
            }
            if (Edge[x][y] == INT_MAX) {
                Edge[x][y] = 0;
            }
            Edge[x][y] += 1;
        }

        /*
         * �������(x,y)�������<x,y>���ڣ����ͼ��ɾ���ñ�
         */
        void RemoveEdge(int x, int y)
        {
            if (x > this->vexnum || y > this->vexnum) {
                std::cerr << "�ñ߲��ڿ�ɾ����Χ��" << std::endl;
                return;
            }
            if (Edge[x][y] == 0) {
                return;
            }
            Edge[x][y] -= 1;
        }

        /*
         * ��ͼ�ж���x�ĵ�һ���ڽӵ㣬�����򷵻ض���š���xû���ڽӵ��ͼ�в�����x���򷵻�-1
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
         * ����ͼ�ж���y�Ƕ���x��һ���ڽӵ㣬���س�y֮�ⶥ��x����һ���ڽӵ�Ķ���ţ���y��x�����һ���ڽӵ㣬�򷵻�-1
         */
        int NextNeighbor(int x, int y)
        {
            return 0;
        }

        /*
         * ��ȡͼ�б�(x,y)��<x,y>��Ӧ��Ȩֵ
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
         * ����ͼ�б�(x,y)��<x,y>��Ӧ��Ȩֵ
         */
        int SetEdgeValue(int x, int y, int v)
        {
            Edge[x][y] = v;

            return 0;
        }

        /*
         * ��ӡ������ǰ��ͼ
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
         * K�㷨ʵ��
         */
    	void K()
        {
            auto sort = [](const int& a, const int& b) {
                return a > b;
            };
            std::priority_queue<int, std::vector<int>, decltype(sort)> pq(sort);

            std::vector<bool> visited(this->vexnum, false); // ���ڱ���Ƿ��Ѿ���������

            for (int i = 0; i < this->vexnum; i++)
            {
                for (int j = 0; j < this->vexnum; j++)
                {
                    if (!visited[j]) // δ��������
                    {
                        pq.emplace(GetEdgeValue(i, j));
                    }
                }
                visited[i] = true; // ����Ѷ�������
            }

            for (int i = 0; i < (this->vexnum - 1); i++)
            {
                std::cout << pq.top() << std::endl;
                pq.pop();
            }
        }

        /*
         * P�㷨ʵ��
         */
        void P()
        {
	        
        }

        /*
         * Dijkstra�㷨ʵ��
         */
        //FIXME:����������������while�����Ҫ��Ȩ���ڵ���dist�����е�λ�ð󶨣���Ȼ����bug
        std::vector<std::pair<int, int>> Dijkstra(T source)
        {
            int num = FindVertexIndex(source);
            std::vector<int> dist(vexnum, INT_MAX); //��������
            dist[num] = 0;

            auto sort = [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                return a.first > b.first;
            };
            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(sort)> pq(sort);

            //�����ľ�������Ϊ0�������������ڵ�ľ�������Ϊ����󣨻�һ���㹻�������������������һ�����ȶ��У�����С�ѣ��У����վ����С��������
			for(int i = 0; i < vexnum; i++)
			{
                pq.emplace(dist[i], i);
			}

            //�����ȶ�����ȡ��������С�Ľڵ㣨��ǰ���·���Ľڵ㣩�������������ڵĽڵ㡣����ÿ�����ڽڵ㣬����ͨ����ǰ���·���ڵ㵽�����ľ��룬������֪������бȽϡ�
            //���������ľ���С����֪���룬����¸ýڵ�ľ���ֵ��Ȼ����������ȶ��С�
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

            //���������result������
            std::vector<std::pair<int, int>> result;
            for (int i = 0; i < vexnum; i++)
            {
                result.emplace_back(dist[i], i);
            }


            return result;
        }

        void Floyd()
        {
            // �������
            std::vector<std::vector<int>> W(this->vexnum, std::vector<int>(vexnum, INT_MAX));
            // ·�ɾ���
            std::vector<std::vector<int>> R(this->vexnum, std::vector<int>(vexnum, -1));

            // ��ʼ����������·�ɾ���
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

            // ��ʼ��������
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
