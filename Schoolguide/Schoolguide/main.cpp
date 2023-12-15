#include <iostream>
#include <fstream>
#include <string>
#include "fileR&W.h"
#include <conio.h>

using namespace std;	

string readfilePath_1 = "Rawdata.txt";
string savefilePath_1 = "Rawdata.txt";
string readfilePath_2 = "infodata.txt";
string savefilePath_2 = "infodata.txt";

void menu();

int main() {
	menu();
	//nums = AddingPointinfo(infohead);
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

void menu() {
	int numbers, nums,vA,vB,pathlength,num;
	string name,info;
	Pointinfo* p = NULL;
	PathNode* Pathhead = new PathNode(0, 0, 0);
	Pointinfo* infohead = new Pointinfo("", "", 0);
	numbers = Rawdata_readinfromFile(Pathhead, readfilePath_1);
	nums = Rawdata_readinfromFile(infohead, readfilePath_2);
	buildingAdjoint_matrices(numbers, Pathhead);
	Pathinfo** paths = Floyd_A(numbers);

	while (1) {
		system("cls");
		cout <<
"[1]:show the map(if you want to see this useless map)(ok)\n\
[2]:check the info of all Attractions(ok)\n\
[3]:Query the shortest path between two points(You're too lazy, aren't you?)(ok)\n\
[4]:three point best path find(Oh, greed!)(ok)\n\
[5]:Find all paths between two points(I don't think you'll want to see it)(ok)\n\
[6]:find key point\n\
[7]:add a new point and his path(ok)\n\
[8]:delete a point and his path(ok)\n\
[9]:add path(ok)\n\
[a]:delete a path(ok)\n\
[b]:save the data(ok)\n\
[Q]:Quit\n\
please enter the number of the option you want to choose:";
		char opt1 = _getch();
		switch (opt1) {
			case '1':
				system("cls");
				system("start a.png");
				system("pause");
				break;
			case '2':
				system("cls");
				p = infohead->next;
				for (int i = 0; i < nums; i++) {
					cout << '[' << i << ']' << ":" << p->name << endl;
					p = p->next;
				}
				cout << endl;

				searchinfo(infohead, nums);
				system("pause");
				break;
			case '3':
				system("cls");
				int start, end;
				cout << "please enter the start number:\n";
				cin >> start;
				cout << "please enter the end number:\n";
				cin >> end;
				//printPath(paths, start, end);
				printinfo_ofPath(paths, infohead, nums, start, end);
				system("pause");
				break;
			case '4':
				system("cls");
				int via;
				cout << "please enter the start, end, and pathpoint;";
				cin >> start >> end >> via;
				findShortestPathWithVia(paths, numbers, start, end, via);
				cout << "search over" << endl;
				system("pause");
				break;
			case '5':
				system("cls");
				cout << "please enter the start number:\n";
				cin >> start;
				cout << "please enter the end number:\n";
				cin >> end;
				traverseAllPaths(start, end, numbers);
				cout << "search over" << endl;
				system("pause");
				break;
			case '6':
				system("cls");
				findArticulationPoints(numbers);
				system("pause");
				break;
			case '7':
				system("cls");
				nums = AddingPointinfo(infohead, nums, 1);
				numbers = Rawdata_readinfromTerminal(Pathhead, numbers, infohead->next->num);
				buildingAdjoint_matrices(numbers, Pathhead); // update the Adjacency_matrix
				paths = Floyd_A(numbers);
				break;
			case '8':
				system("cls");
				cout << "please enter the name of the point you want to delete:\n";
				cin >> name;
				p = infohead;
				while (abs(p->next->name.compare(name))) {
					p = p->next;
				}
				vA = p->next->num;
				delete p;
				nums = PopingPointinfo(infohead, name, nums);
				numbers = FnpopPAthNode(Pathhead, numbers, vA);
				buildingAdjoint_matrices(numbers, Pathhead); // update the Adjacency_matrix
				paths = Floyd_A(numbers);
				break;
			case '9':
				system("cls");
				numbers = Rawdata_readinfromTerminal(Pathhead, numbers);
				buildingAdjoint_matrices(numbers, Pathhead); // update the Adjacency_matrix
				paths = Floyd_A(numbers);
				break;
			case 'a':
				system("cls");
				cout << "please enter the number of the path you want to delete:\n";
				cout << "please enter the start number,end number, and pathlength:\n";
				cin >> vA >> vB >> pathlength;
				numbers = FnpopPAthNode(Pathhead, numbers, vA, vB, pathlength);
				buildingAdjoint_matrices(numbers, Pathhead); // update the Adjacency_matrix
				paths = Floyd_A(numbers);
				break;
			case 'b':
				system("cls");
				Rawdata_saveinFile(Pathhead, infohead, nums, numbers, savefilePath_1, savefilePath_2);
				break;
			case 'Q':
				return;
				break;
			default:
				cout << "Invalid option! please enter again!\n";
				system("pause");
				break;
		}
	}
}
