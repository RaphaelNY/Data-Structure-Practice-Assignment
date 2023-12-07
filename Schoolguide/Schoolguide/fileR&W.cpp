#include <iostream>
#include <fstream>
#include "Pointer.h"
#include <string>

using namespace std;

/* read the data from the terminal correct
	input: head of the linked list
	output: numbers of vertices
*/
int Rawdata_readinfromTerminal(PathNode* head, int numbers) {
	int vA, vB, pathlen, num;
	cout << "enter the path num:";
	cin >> num;
	numbers += num;
	for (int i = 0; i < num;i++) {
		cout << "enter the pair and pathlen:";
		cin >> vA >> vB >> pathlen;
		PathNode* node = new PathNode(vA,vB,pathlen);
		node->next = head->next;
		head->next = node;
	}
	cout<<"RawPathdata read is over"<<endl;
	return numbers;
}
int Rawdata_readinfromTerminal(PathNode* head, int numbers, int vA) {
	int vB, pathlen, num;
	cout << "enter the path num:";
	cin >> num;
	numbers += num;
	for (int i = 0; i < num; i++) {
		cout << "enter the pair and pathlen:";
		cin >> vB >> pathlen;
		PathNode* node = new PathNode(vA, vB, pathlen);
		node->next = head->next;
		head->next = node;
	}
	cout << "RawPathdata read is over" << endl;
	return numbers;
}

// create pointinfo chain correct
int AddingPointinfo(Pointinfo* head, int nums) {
	string name, info;
	int num,nu;
	Pointinfo* p = new Pointinfo("", "", -1);	
	cout << "please enter the pointer nums:";
	cin >> nu;
	nums += nu;
	for (int i = 0; i < nu; i++) {
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
int AddingPointinfo(Pointinfo* head, int nums, int nu) {
	string name, info;
	int num, nu;
	Pointinfo* p = new Pointinfo("", "", -1);
	nums += nu;
	for (int i = 0; i < nu; i++) {
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