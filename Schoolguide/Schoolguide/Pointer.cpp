#include <iostream>
#include <string>
#include <cstring>

#define MAXSIZE 100

#define DEBUG 0
#if (DEBUG != 0)
#define Arrary_INFO 1
#endif

using namespace std;

int Adjacency_matrix[MAXSIZE][MAXSIZE];

struct PathNode {
	int  vA;
	int vB;
	int pathlen;
	PathNode* next;

	PathNode(int vA, int vB, int pathlen): vA(vA), vB(vB), pathlen(pathlen), next(nullptr) {}
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
	int* path;
	int pathLength;
};

int addPathNode(PathNode* head, int vA, int vB, int pathlen, int numbers) {
	PathNode* node = new PathNode(vA, vB, pathlen);
	node->next = head->next;
	head->next = node;
	return numbers++;
}

// add to head->next
int addPointinfo(Pointinfo* head, string name, string info, int num, int nums) {
	Pointinfo* node = new Pointinfo(name, info, num);
	node->next = head->next;
	head->next = node;
	return nums++;
}

// pop nead->next
int popPathNode(PathNode* head, int numbers) {
	PathNode* p = head->next;
	head->next = p->next;
	delete p;
	return numbers--;
}

int FnpopPAthNode(PathNode* Pathhead, int numbers, int vA,int vB, int pathlength) {
	PathNode* p = Pathhead;
	while (!(p->next->vA == vA && p->next->vB == vB && p->next->pathlen == pathlength)) {
		p = p->next;
	}
	numbers = popPathNode(p, numbers);
	return numbers;
}
// pop nead->next
int popPointinfo(Pointinfo* head, int nums) {
	Pointinfo* p = head->next;
	head->next = p->next;
	delete p;
	return nums--;
}

// print all sides
void print_allPathNodes(PathNode* head) {
	PathNode* p = head->next;
	while (p != nullptr) {
		cout << p->vA << " " << p->vB << " " << p->pathlen << endl;
		p = p->next;
	}
}

// print all pointinfo
void print_allPointinfo(Pointinfo* head) {
	Pointinfo* p = head->next;
	while (p != nullptr) {
		cout << p->name << endl << p->num << endl << p->info << endl;
		p = p->next;
	}
}

/* build the Adjacency matrix correct
	input: numbers of vertices, head of the linked list
	output: Adjacency matrix
*/
void buildingAdjoint_matrices(int numbers, PathNode* head) {
	PathNode* p = head->next;
	while (p) {
		Adjacency_matrix[p->vA][p->vB] = p->pathlen;
		Adjacency_matrix[p->vB][p->vA] = p->pathlen;
		p = p->next;
	}
#ifndef Arrary_INFO
	for (int i = 0; i < numbers; i++) {
		for (int j = 0; j < numbers; j++) {
			cout << Adjacency_matrix[i][j] << "\t";
		}
		cout << endl;
	}
#endif
}

/* Floyd algorithm
	input: numbers of vertices
	output: Adjacency matrix
 */
Pathinfo** Floyd_A(int numbers) {
	// init Adjacency and paths
	int** Adjacency = new int* [numbers];
	Pathinfo** paths = new Pathinfo*[numbers];
	for (int i = 0; i < numbers; i++) {
		Adjacency[i] = new int[numbers];
		paths[i] = new Pathinfo[numbers];
		memcpy(Adjacency[i], Adjacency_matrix[i], numbers * sizeof(int));
		for (int j = 0; j < numbers; j++) {
			paths[i][j].length = Adjacency_matrix[i][j];
			paths[i][j].path = new int[numbers];
			paths[i][j].path[0] = i;
			paths[i][j].path[1] = j;
			paths[i][j].pathLength = 2;
		}
	}
	for (int k = 0; k < numbers; k++) {
		for (int i = 0; i < numbers; i++) {
			for (int j = 0; j < numbers; j++) {
				if ((Adjacency[i][k] + Adjacency[k][j] < Adjacency[i][j] || (Adjacency[i][j] == 0 && Adjacency[i][k] !=0 && Adjacency[k][j] != 0)) && (i != j)) {
					Adjacency[i][j] = Adjacency[i][k] + Adjacency[k][j];

					paths[i][j].length = Adjacency[i][j];
					delete[] paths[i][j].path;
					paths[i][j].path = new int[paths[i][k].pathLength + paths[k][j].pathLength - 1];
					copy(paths[i][k].path, paths[i][k].path + paths[i][k].pathLength, paths[i][j].path);
					copy(paths[k][j].path + 1, paths[k][j].path + paths[k][j].pathLength, paths[i][j].path + paths[i][k].pathLength);
					paths[i][j].pathLength = paths[i][k].pathLength + paths[k][j].pathLength - 1;
				}
			}
		}
	}
	return paths;
}

int** Floyd_B(int numbers) {
	 int** Adjacency = new int*[numbers];
	for (int i = 0; i < numbers; i++) {
		Adjacency[i] = new int[numbers];
		memcpy(Adjacency[i], Adjacency_matrix[i], numbers * sizeof(int));
	}
	for (int k = 0; k < numbers; k++) {
		for (int i = 0; i < numbers; i++) {
			for (int j = 0; j < numbers; j++) {
				if ((Adjacency[i][k] + Adjacency[k][j] < Adjacency[i][j] || Adjacency[i][j] == 0) && (i != j)) {
					Adjacency[i][j] = Adjacency[i][k] + Adjacency[k][j];
				}
			}
		}
	}
	return Adjacency;
}

void printPath(Pathinfo** paths, int start,int end) {
	cout << "from " << start << " to " << end << " is: " << paths[start][end].length << endl;
	cout << "path: ";
	for (int i = 0; i < paths[start][end].pathLength; i++) {
		cout << paths[start][end].path[i] << "->";
	}
	cout << "end" << endl;
}

void printinfo_ofPath(Pathinfo** paths, Pointinfo* infohead, int nums, int start, int end) {
	Pointinfo* p = infohead->next;
	cout << "from " << start << " to " << end << " is: " << paths[start][end].length << endl;
	cout << "path: ";
	for (int i = 0; i < paths[start][end].pathLength; i++) {
		for (int j = 0; j < nums; j++) {
			if(p->num == paths[start][end].path[i])
				break;
			p = p->next; 
		}
		cout << paths[start][end].path[i] << ":" << p->name << "->";
		p = infohead->next;
	}
	cout << "end" << endl;
}

void searchinfo(Pointinfo* head, int nums) {
	Pointinfo* p = head->next;
	cout << "enter \":q\" can quit\n";
	string name="";
	while (1) {
		p = head->next;
		cout << "enter the name:";
		cin >> name;
		if (!abs(name.compare(":q")))
			break;
		for (int i = 0; i < nums; i++) {
			if (!abs(p->name.compare(name))) {
				cout << p->name << endl << p->num << endl << p->info << endl;
			}
			p = p->next;
		}
		if (p == nullptr) {
			cout << "cannot found.";
		}
	}
}
/* Dijkstra algorithm
	input: numbers of vertices, start vertex
		print the road path like: v1->v2->v3...
		visited: 0 means not visited, 1 means visited
		path: the path from start vertex to other vertices
	output: distance from start vertex to other vertices
*/
 /* un corrected
 int* Dijkstra(int numbers, int start, int end) {
    int* distance = new int[numbers];
	int* visited = new int[numbers];
	int* path = new int[numbers];
	int min, v;
	for (int i = 0; i < numbers; i++) {
		distance[i] = Adjacency_matrix[start][i];
		visited[i] = 0;
		if (distance[i] != 0) {
			path[i] = start;
		}
		else {
			path[i] = -1;
		}
	}
	visited[start] = 1;
	for (int i = 0; i < numbers; i++) {
		min = INT_MAX;
		for (int j = 0; j < numbers; j++) {
			if (visited[j] == 0 && distance[j] < min) {
				min = distance[j];
				v = j;
			}
		}
		visited[v] = 1;
		for (int j = 0; j < numbers; j++) {
			if (visited[j] == 0 && Adjacency_matrix[v][j] != 0 && distance[v] + Adjacency_matrix[v][j] < distance[j]) {
				distance[j] = distance[v] + Adjacency_matrix[v][j];
				path[j] = v;
			}
		}
	}
	int* road = new int[numbers];
	int i = 0;
	int j = end;
	while (j != start) {
		road[i] = j;
		j = path[j];
		i++;
	}
	road[i] = start;
	for (int j = i; j >= 0; j--) {
		cout << road[j] << "->";
	}
	cout << endl;
	return distance;
}*/