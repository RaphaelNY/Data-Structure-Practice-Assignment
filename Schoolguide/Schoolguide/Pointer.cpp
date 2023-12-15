#include <iostream>
#include <string>
#include <cstring>

#define MAXSIZE 100

#define DEBUG 1
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
int FnpopPAthNode(PathNode* Pathhead, int numbers, int vA) {
	PathNode* p = Pathhead;
	while (p->next != nullptr) {
		if (p->next->vA == vA || p->next->vB == vA) {
			numbers = popPathNode(p, numbers);
		}
		p = p->next;
	}
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
#ifndef Arrary_INFO
	cout << endl;
	for (int i = 0; i < numbers; i++) {
		for (int j = 0; j < numbers; j++) {
			cout << Adjacency[i][j] << "\t";
		}
		cout << endl;
	}cout << endl;
#endif
	for (int k = 0; k < numbers; k++) {
		for (int i = 0; i < numbers; i++) {
			for (int j = 0; j < numbers; j++) {
				if (((Adjacency[i][k] + Adjacency[k][j] < Adjacency[i][j] && Adjacency[i][k] != 0 && Adjacency[k][j] != 0) || (Adjacency[i][j] == 0 && Adjacency[i][k] !=0 && Adjacency[k][j] != 0)) && (i != j)) {
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
#ifndef Arrary_INFO
	cout << endl;
	for (int i = 0; i < numbers; i++) {
		for (int j = 0; j < numbers; j++) {
			cout << Adjacency[i][j] << "\t";
		}
		cout << endl;
	}cout << endl;
	for (int i = 0; i < numbers; i++) {
		for (int j = 0; j < numbers; j++) {
			cout << paths[i][j].length << "\t";
		}
		cout << endl;
	}cout << endl;
	for (int i = 0; i < numbers; i++) {
		for (int j = 0; j < numbers; j++) {
			cout << paths[i][j].pathLength << "\t";
		}
		cout << endl;
	}cout << endl;
#endif
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
	if(paths[start][end].length == 0)
		cout << "no path" << endl;
	else if (paths[start][end].length != 0) {
		cout << "path: ";
		for (int i = 0; i < paths[start][end].pathLength; i++) {
			for (int j = 0; j < nums; j++) {
				if (p->num == paths[start][end].path[i])
					break;
				p = p->next;
			}
			cout << paths[start][end].path[i] << ":" << p->name << "->";
			p = infohead->next;
		}
		cout << "end" << endl;
	}
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

void DFS(int u, int* disc, int* low, int* parent, bool* ap, int& time, int numbers) {
	int children = 0;
	disc[u] = low[u] = ++time;

	for (int v = 0; v < numbers; ++v) {
		if (Adjacency_matrix[u][v] != 0) {
			if (disc[v] == -1) {
				children++;
				parent[v] = u;
				DFS(v, disc, low, parent, ap, time, numbers);

				low[u] = min(low[u], low[v]);

				if (parent[u] == -1 && children > 1)
					ap[u] = true;

				if (parent[u] != -1 && low[v] >= disc[u])
					ap[u] = true;
			}
			else if (v != parent[u]) {
				low[u] = min(low[u], disc[v]);
			}
		}
	}
}

void DFS(int start, int end, int numbers, int* path, bool* visited, int pathLength) {
	path[pathLength++] = start;
	visited[start] = true;

	if (start == end) {
		cout << "Path: ";
		for (int i = 0; i < pathLength; ++i) {
			cout << path[i] << " ";
		}
		cout << endl;
	}
	else {
		for (int i = 0; i < numbers; ++i) {
			if (Adjacency_matrix[start][i] != 0 && !visited[i]) {
				DFS(i, end, numbers, path, visited, pathLength);
			}
		}
	}
	visited[start] = false;
}

void findArticulationPoints(int numbers) {
	int* disc = new int[numbers];
	int* low = new int[numbers];
	int* parent = new int[numbers];
	bool* ap = new bool[numbers];
	int time = 0;

	for (int i = 0; i < numbers; i++) {
		disc[i] = -1;
		low[i] = -1;
		parent[i] = -1;
		ap[i] = false;
	}

	for (int i = 0; i < numbers; i++) {
		if (disc[i] == -1) {
			DFS(i, disc, low, parent, ap, time, numbers);
		}
	}

	cout << "key point is:";
	int num = 0;
	for (int i = 0; i < numbers; i++) {
		if (ap[i]) {
			cout << i << " ";
			num++;
		}
	}
	if(num== 0)
		cout << "no key point" << endl;
	cout << endl;

	delete[] disc;
	delete[] low;
	delete[] parent;
	delete[] ap;
}

void traverseAllPaths(int start, int end, int numbers) {
	bool* visited = new bool[numbers] {false};
	int* path = new int[numbers];
	int pathLength = 0;

	DFS(start, end, numbers, path, visited, pathLength);

	delete[] visited;
	delete[] path;
}

void findShortestPathWithVia(Pathinfo** paths, int numbers, int start, int end, int via) {
	for (int i = 0; i < numbers; i++) {
		int viaIndex = -1;
		for (int i = 0; i < numbers; i++) {
			if (i != start && i != end && i == via) {
				viaIndex = i;
				break;
			}
		}

		if (viaIndex == -1) {
			cerr << "Error: The specified 'via' node does not exist or is the same as start/end nodes." << endl;
			return;
		}
		else if(viaIndex = via){
			cout << "Shortest Path from " << start << " to " << end << " via " << via << ":" << endl;
			cout << "Length: " << paths[start][viaIndex].length + paths[viaIndex][end].length << " - ";
			for (int i = 0; i < paths[start][viaIndex].pathLength; i++) {
				cout << paths[start][viaIndex].path[i] << " ";
			}
			for (int i = 1; i < paths[viaIndex][end].pathLength; i++) {
				cout << paths[viaIndex][end].path[i] << " ";
			}
			cout << endl;
			break;
		}
	}
}