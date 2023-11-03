#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct HuffmanNode;

struct CompareNodes;

struct vec;

void sorting(char Dlist[], int Flist[], int numPairs);

HuffmanNode* buildHuffmanTree_1(char Dlist[], int Flist[], int numPairs);

// HuffmanNode* buildHuffmanTree(vector<pair<char, int>> fs);

char HuffDecoder_1(HuffmanNode* &point, char ch);

string HuffEncoder_1(HuffmanNode* root, char ch, string code = "");

void printHuffmanTree(HuffmanNode* root, string code = "");

void serializeHuffmanTree(HuffmanNode* root, ofstream& outfile);

HuffmanNode* deserializeHuffmanTree(ifstream& infile);

void printandsaveTree(HuffmanNode* node, ofstream& outfile, bool isLeft = false, string prefix = "");

//////////////////////////////////////////////////////////////////////////////
//void buildHuffmanCodes(HuffmanNode* root, map<char, string>& huffmanEncodes, map<string, char>& huffmanDecodes, string code = "");
//
//string HuffEncoder(string text, map<char, string>& huffmanCodes);
//
//string Huffdecoder(string &text, map<string, char>& huffmanDecodes);
