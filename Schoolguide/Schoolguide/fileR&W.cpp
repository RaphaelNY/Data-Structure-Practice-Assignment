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
	for (int i = 0; i < num;i++) {
		cout << "enter the pair and pathlen:";
		cin >> vA >> vB >> pathlen;
		PathNode* node = new PathNode(vA,vB,pathlen);
		node->next = head->next;
		head->next = node;
		if (vA > numbers) numbers++;
		if (vB > numbers) numbers++;
	}
	cout<<"RawPathdata read is over"<<endl;
	return numbers;
}
int Rawdata_readinfromTerminal(PathNode* head, int numbers, int vA) {
	int vB, pathlen, num;
	cout << "enter the path num:";
	cin >> num;
	numbers += 1;
	for (int i = 0; i < num; i++) {
		cout << "enter the end point and pathlen:";
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
	int num;
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

int PopingPointinfo(Pointinfo* head, string name, int nums) {
	Pointinfo*p = head;
	while (abs(p->next->name.compare(name))) {
		p = p->next;
	}
	nums = popPointinfo(p, nums);
	return nums;
}

/* read the data from the file correct
	input: head of the linked list
	output: numbers of vertices
*/
int Rawdata_readinfromFile(PathNode* head, string readfilePath_1) {
	int vA, vB, pathlen;
	int numbers = 0;
	ifstream fin(readfilePath_1);
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
int Rawdata_readinfromFile(Pointinfo* infohead, string readfilePath_2) {
	int nums = 0;
	ifstream fin(readfilePath_2);
	fin >> nums;
	for (int i = 0; i < nums; i++) {
		string name, info;
		int num;
		fin >> name >> info >> num;
		Pointinfo* node = new Pointinfo(name, info, num);
		node->next = infohead->next;
		infohead->next = node;
	}
	fin.close();
	cout << "infodata read is over" << endl;
	return nums;
}

/* save the data in the file
	input: head of the linked list
	output: numbers of vertices
*/
void Rawdata_saveinFile(PathNode* Pathhead, Pointinfo* infohead, int nums, int numbers, string savefilePath_1, string savefilePath_2) {
	ofstream fout_1(savefilePath_1);
	ofstream fout_2(savefilePath_2);
	PathNode* p = Pathhead->next;
	fout_1 << numbers << endl;
	while (p) {
		fout_1 << p->vA << " " << p->vB << " " << p->pathlen << endl;
		p = p->next;
	}delete p;
	fout_1.close();

	Pointinfo* q = infohead->next;
	fout_2 << nums << endl;
	while (q) {
		fout_2 << q->name << "\n" << q->info << "\n" << q->num << endl;
		q = q->next;
	}delete q;
	fout_2.close();

	cout << "Rawdata save is over" << endl;
}