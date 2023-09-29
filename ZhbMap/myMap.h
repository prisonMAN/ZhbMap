//
// Created by ZhouHB on 2023/9/8.
//

#ifndef ZHBMAP_MYMAP_H
#define ZHBMAP_MYMAP_H

#include <iostream>

namespace myMap {

    template <typename T>
    class AdjMatrixMap
	{
    private:
        int MaxVertexNum; // ���������Ŀ
        T* Vex; // �����
        int** Edge; // �ڽӾ��󣬱߱�
        int vexnum;
        int arcnum; // ͼ�ĵ�ǰ�������ͱ���

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

            this->Vex = new T[MaxVertexNum + 1];

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

        bool Adjacent(int x, int y) const
        {
            if (this->Edge[x][y] != 0) {
                return false;
            }
            else {
                return true;
            }
        }

        int FindVertexIndex(T vertex)
        {
            for (int i = 0; i < this->vexnum; i++) {
                if (this->Vex[i] == vertex) {
                    return i;
                }
            }
            return -1;
        }

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

        void InsertVertex(T vertex)
        {
            vexnum += 1;
            for (int i = 0; i < vexnum; i++) {
                this->Edge[vexnum][i] = 0;
                this->Edge[i][vexnum] = 0;
                if (this->Vex[i] == vertex) {
                    std::cerr << "�뻻һ������" << std::endl;
                    return;
                }
            }
            this->Vex[vexnum] = vertex;
        }

        void DeleteVertex(T vertex)
        {
            int num = FindVertexIndex(vertex);
            for (int i = 0; i < this->vexnum; i++) {
                this->Edge[num][i] = INT_MAX;
                this->Edge[i][num] = INT_MAX;
            }
            vexnum -= 1;
        }

        void AddEdge(int x, int y)
        {
            if (x > this->vexnum || y > this->vexnum) {
                std::cout << "�ñ߲��ڿ���ӷ�Χ��" << std::endl;
                return;
            }
            if (Edge[x][y] == INT_MAX) {
                Edge[x][y] = 0;
            }
            Edge[x][y] += 1;
        }

        void RemoveEdge(int x, int y)
        {
            if (x > this->vexnum || y > this->vexnum) {
                std::cout << "�ñ߲��ڿ�ɾ����Χ��" << std::endl;
                return;
            }
            if (Edge[x][y] == 0) {
                return;
            }
            Edge[x][y] -= 1;
        }

        int FirstNeighbor(T vertex)
        {
            int num = FindVertexIndex(vertex);

            for (int i = 0; i < num; i++)
            {
                if (Edge[num][i] != 0 || Edge[i][num] != 0) {
                    num = i;
                    break;
                }
            }
            std::cout << num << std::endl;
            return num;
        }

        int NextNeighbor(int x, int y)
        {
            return 0;
        }

        int GetEdgeValue(int x, int y) const
        {
            return Edge[x][y];
        }

        int SetEdgeValue(int x, int y, int v)
        {
            Edge[x][y] = v;

            return 0;
        }
    };

    class AdjListMap
    {
    private:

    };

} // myMap

#endif //ZHBMAP_MYMAP_H
