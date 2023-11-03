#include <iostream>
#include <fstream>
#include <string>
#include "huffmanTree.h"

using namespace std;

void Rawdata_r1(char Dlist[], int Flist[], int& numPairs);

void Filecharcount(string read_path, char Dlist[], int Flist[], int& numPairs);

// vector<pair<char, int>> Rawdata_r(vector<pair<char, int>> frequencies);

void FilereadandEncoder(string read_path, string save_path, HuffmanNode* root);

void FilereadandDecoder(string read_path, string save_path, HuffmanNode* root);

void FilereadandPrint(string read_path, string save_path);

void saveHuffmanTreeToFile(HuffmanNode* root, string save_path);

void saveprintTreeToFile(HuffmanNode* root, string save_path);

HuffmanNode* loadHuffmanTreeFromFile(string read_path);

void treesizeshowandsave(HuffmanNode* root, string save_path);

