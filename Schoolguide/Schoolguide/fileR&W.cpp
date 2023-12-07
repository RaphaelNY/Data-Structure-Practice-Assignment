#include <iostream>
#include <fstream>
#include "Pointer.h"
#include <string>

using namespace std;

/* read the data from the terminal correct
	input: head of the linked list
	output: numbers of vertices
*/
int Rawdata_readinfromTerminal(PathNode* head) {
	head->next = nullptr;
	int vA, vB, pathlen;
	int numbers;
	cout << "enter the pointer num:";
	cin >> numbers;
	cout<< "enter the pair and pathlen:";
	while (cin>> vA>> vB>> pathlen) {
		PathNode* node = new PathNode(vA,vB,pathlen);
		node->next = head->next;
		head->next = node;
	}
	cout<<"Rawdata read is over"<<endl;
	return numbers;
}

// create pointinfo chain correct
int AddingPointinfo(Pointinfo* head) {
	head->next = nullptr;
	string name, info;
	int num;
	int nums;
	Pointinfo* p = new Pointinfo("", "", -1);	
	cout << "please enter the nums:";
	cin >> nums;
	for (int i = 0; i < nums; i++) {
		cout << "please enter the name:";
		cin >> name;
		cout << "please enter the info:";
		cin >> info;
		cout << "please enter the number:";
		cin >> num;
		Pointinfo* p = new Pointinfo(name, info, num);
		p->next = head->next;
		head->next = p;
	}
	return nums;
}

/* read the data from the file correct
	input: head of the linked list
	output: numbers of vertices
*/
int Rawdata_readinfromFile(PathNode* head, string readfilePath) {
	int vA, vB, pathlen;
	int numbers = 0;
	ifstream fin(readfilePath);
	fin >> numbers;
	while (fin >> vA >> vB >> pathlen) {
		cout << vA << " " << vB << " " << pathlen << endl;
		PathNode* node = new PathNode(vA, vB, pathlen);
		node->next = head->next;
		head->next = node;
	}
	fin.close();
	cout << "Rawdata read is over" << endl;
	return numbers;
}

/* save the data in the file
	input: head of the linked list
	output: numbers of vertices
*/
void Rawdata_saveinFile(PathNode* head,int numbers, string savefilePath) {
	ofstream fout(savefilePath);
	PathNode* p = head->next;
	fout << numbers;
	while (p) {
		fout << p->vA << " " << p->vB << " " << p->pathlen << endl;
		p = p->next;
	}
	fout.close();
	cout << "Rawdata save is over" << endl;
}