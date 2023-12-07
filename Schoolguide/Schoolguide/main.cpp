#include <iostream>
#include <fstream>
#include <string>
#include "fileR&W.h"

using namespace std;	

string readfilePath = "E:\\资料\\数据结构\\Schoolguide\\Schoolguide\\Rawdata.txt";
string savefilePath = "E:\\资料\\数据结构\\Schoolguide\\Schoolguide\\Rawdata.txt";

int main() {
	int numbers,nums;
	PathNode* Pathhead = new PathNode(0,0,0);
	Pointinfo* infohead = new Pointinfo("", "", 0);
	numbers = Rawdata_readinfromFile(Pathhead, readfilePath);
	nums = AddingPointinfo(infohead);
	//print_allPointinfo(infohead);
	//searchinfo(infohead, nums);
	//buildingAdjoint_matrices(numbers, head);
	//Pathinfo** paths = Floyd_A(numbers);
	//printPath(paths, 0, 5);
	/* int** Adjacency = Floyd_B(numbers);
	for (int j = 0; j < numbers; j++) {
		for (int i = 0; i < 7; i++)
			cout << Adjacency[j][i] << "\t";
	 	cout << endl;
    }
	*/
}
