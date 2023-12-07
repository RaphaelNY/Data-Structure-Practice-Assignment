#pragma once

using namespace std;

struct PathNode {
    int vA;
    int vB;
    int pathlen;
    PathNode* next;

    PathNode(int vA, int vB, int pathlen) : vA(vA), vB(vB), pathlen(pathlen), next(nullptr) {}
};

struct Pointinfo {
    string name;
    string info;
    int num;
    Pointinfo* next;
    Pointinfo(string name, string info, int num) : name(name), info(info), num(num), next(nullptr) {}
};

struct Pathinfo {
    int length;
    int* Path;
    int PathLength;
};

void buildingAdjoint_matrices(int numbers, PathNode* head);

int addPathNode(PathNode* head, int vA, int vB, int pathlen, int numbers);
int popPathNode(PathNode* head, int numbers);
void print_allPathNodes(PathNode* head);

int addPointinfo(Pointinfo* head, string name, string info, int num, int nums);
int popPointinfo(Pointinfo* head, int nums);
void print_allPointinfo(Pointinfo* head);


Pathinfo** Floyd_A(int number);
int** Floyd_B(int numbers);
void printPath(Pathinfo** paths, int start, int end);
void printinfo_ofPath(Pathinfo** paths, Pointinfo* infohead, int nums, int start, int end);
// int* Dijkstra(int numbers, int start, int end);

void searchinfo(Pointinfo* head, int nums);
