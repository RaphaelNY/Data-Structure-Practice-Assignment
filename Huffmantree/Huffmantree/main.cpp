#include <iostream>
#include <fstream>
#include <conio.h>
#include "fileR&W.h"
#include "huffmanTree.h"
using namespace std;

#define DEBUG 0

#if (DEBUG != 0)

#define TREE_INFO 1
#define Code_INFO 2

#endif

#define MAX_LEN 130

string file1 = "D:\\code\\C\\Data-Structure-Practice-Assignment\\Huffmantree\\Huffmantree\\data\\HfmTree.txt";
string file2 = "D:\\code\\C\\Data-Structure-Practice-Assignment\\Huffmantree\\Huffmantree\\data\\ToBeTran.txt";
string file3 = "D:\\code\\C\\Data-Structure-Practice-Assignment\\Huffmantree\\Huffmantree\\data\\CodeFile.txt";
string file4 = "D:\\code\\C\\Data-Structure-Practice-Assignment\\Huffmantree\\Huffmantree\\data\\TextFile.txt";
string file5 = "D:\\code\\C\\Data-Structure-Practice-Assignment\\Huffmantree\\Huffmantree\\data\\CodePrin.txt";
string file6 = "D:\\code\\C\\Data-Structure-Practice-Assignment\\Huffmantree\\Huffmantree\\data\\TreePrint.txt";

void menu(char Dlist[], int Flist[], int& numPairs, HuffmanNode* &root);

int main() {
    char Dlist[MAX_LEN];
    int  Flist[MAX_LEN];
    int numPairs;

	HuffmanNode* root = NULL;

	menu(Dlist, Flist, numPairs, root);

    //Rawdata_r1(Dlist, Flist, numPairs);
    //sorting(Dlist, Flist, numPairs);
    //HuffmanNode* root = buildHuffmanTree_1(Dlist, Flist, numPairs);
    //printHuffmanTree(root);
    //saveHuffmanTreeToFile(root, file1);
    //HuffmanNode* root_2 = loadHuffmanTreeFromFile(file1); //correct
    //FilereadandEncoder(file2, file3, root_2); //correct
    //FilereadandDecoder(file3, file4, root_2); //correct
    //FilereadandPrint(file3, file5); //correct
    //saveprintTreeToFile(root_2, file6);

    return 0;
}

void menu(char Dlist[], int Flist[], int& numPairs, HuffmanNode* &root) {
	while (1) {
		system("cls");
		cout << "\n\
[I]:Please enter your preferred encoding rule that meets the requirements\n\
[E]:Encode your file\t[D]:Decode your file\t[P]:Print Decode result\n\
[T]:Tree printing\t[Q]:Quit\nYour choice:";
		char choice1, choice2;
		cin >> choice1;
		switch (choice1) {
		case 'I':
			system("cls");
			cout << "[1]Load Tree From File\n[2]Type in dataset\n[3]Set From File\nYour choice:";
			cin >> choice2;
			if (choice2 < '1' || choice2 > '3') {
				cout << "Invalid choice!\n";
				system("pause");
				break;
			}
			if (choice2 == '3') {
				cout << "where is ToBeFile :\n";
				cin >> file2;
				Filecharcount(file2, Dlist, Flist, numPairs);
				sorting(Dlist, Flist, numPairs);
				for (int i = 0; i < numPairs; i++) {
					if (Flist[i] == 0) {
						numPairs = i;
						break;
					}
				}
				root = buildHuffmanTree_1(Dlist, Flist, numPairs);
			}
			else if (choice2 == '2') {
				system("cls");
				Rawdata_r1(Dlist, Flist, numPairs);
				sorting(Dlist, Flist, numPairs);
				root = buildHuffmanTree_1(Dlist, Flist, numPairs);
			}
			else if (choice2 == '1') {
				system("cls");
				root = loadHuffmanTreeFromFile(file1);
			}
			saveHuffmanTreeToFile(root, file1);
			cout << "Successfully built & saved\n";
			system("pause");
			break;

		case 'E':
			system("cls");
			if (root == NULL) {
				root = loadHuffmanTreeFromFile(file1);
				system("pause");
				break;
			}
			cout<<"where is ToBeFile :\n";
			cin >> file2;
			cout << "where is CodeFile :\n";
			cin >> file3;
			FilereadandEncoder(file2, file3, root);
			cout << "Successfully encoded\n";
			system("pause");
			break;
		case 'D':
			system("cls");
			if (root == NULL) {
				root = loadHuffmanTreeFromFile(file1);
				system("pause");
				break;
			}
			cout << "where is CodeFile:\n";
			cin >> file3;
			cout << "where is TextFile:\n";
			cin >> file4;
			FilereadandDecoder(file3, file4, root);
			cout << "Successfully decoded\n";
			system("pause");
			break;
		case 'P':
			system("cls");
			cout << "where is CodeFile:\n";
			cin >> file3;
			cout << "-----------------------code-----------------------\n";
			FilereadandPrint(file3, file5);
			cout << "\n-----------------------ends-----------------------\n";
			system("pause");
			break;
		case 'T':
			system("cls");
			if(root == NULL) {
				root = loadHuffmanTreeFromFile(file1);
				system("pause");
				break;
			}
			printf("-----------------------tree-----------------------\n");
			saveprintTreeToFile(root, file6);
			printf("\n-----------------------ends-----------------------\n");
			system("pause");
			break;
		case 'Q':
			return;
			break;
		default:
			cout << "Invalid choice!\n";
			system("pause");
			break;
		}
	}
}