#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

struct HuffmanNode {
	char data;
	int f;
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(char data, int frequency) : data(data), f(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
	bool operator()(HuffmanNode* a, HuffmanNode* b) {
		return a->f > b->f;
	}
};

void sorting(char Dlist[], int Flist[], int numPairs) {
    for (int i = 0; i < numPairs - 1; i++)
        for (int j = i; j < numPairs; j++) {
            if (Flist[i] < Flist[j]) {
                Flist[i] = Flist[i] + Flist[j];
                Flist[j] = Flist[i] - Flist[j];
                Flist[i] = Flist[i] - Flist[j];
                Dlist[i] = Dlist[i] + Dlist[j];
                Dlist[j] = Dlist[i] - Dlist[j];
                Dlist[i] = Dlist[i] - Dlist[j];
            }
        }
}
void sorting(HuffmanNode** nodes, int numPairs) {
    for (int i = 0; i < numPairs - 1; i++)
        for (int j = i; j < numPairs; j++) {
            if (nodes[i]->f < nodes[j]->f) {
                HuffmanNode* temp = nodes[i];
                nodes[i] = nodes[j];
                nodes[j] = temp;
            }
        }
}

HuffmanNode* buildHuffmanTree_1(char Dlist[], int Flist[], int numPairs) {
    HuffmanNode** nodes = new HuffmanNode * [numPairs];

    for (int i = 0; i < numPairs; i++) {
        nodes[i] = new HuffmanNode(Dlist[i], Flist[i]);
    }
    int min1 = numPairs - 1, min2 = numPairs - 2;
    while (numPairs > 1) {
        HuffmanNode* newNode = new HuffmanNode(127, nodes[min1]->f + nodes[min2]->f);
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];

        nodes[numPairs - 2] = newNode;
        numPairs--;
        sorting(nodes, numPairs);
        min1 = numPairs - 1;
        min2 = numPairs - 2;
    }

    HuffmanNode* root = nodes[0];
    delete[] nodes;
    return root;
}

// init the tree
//HuffmanNode* buildHuffmanTree(vector<pair<char, int>> fs) {
//    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
//    
//    for (auto freq : fs) {
//        HuffmanNode* node = new HuffmanNode(freq.first, freq.second);
//        pq.push(node);
//    }
//
//    while (pq.size() > 1) {
//        HuffmanNode* left = pq.top();
//        pq.pop();
//        HuffmanNode* right = pq.top();
//        pq.pop();
//
//        HuffmanNode* newNode = new HuffmanNode('#', left->f + right->f);
//        newNode->left = left;
//        newNode->right = right;
//        pq.push(newNode);
//    }
//
//    return pq.top();
//}

// using tree to find the encoder
string HuffEncoder_1(HuffmanNode* root, char ch, string code = "") {
    if (root == nullptr) {
        return "";
    }

    if (root->data == ch) {
        return code;
    }

    string leftResult = HuffEncoder_1(root->left, ch, code + "0");
    string rightResult = HuffEncoder_1(root->right, ch, code + "1");

    if (!leftResult.empty()) {
        return leftResult;
    }

    if (!rightResult.empty()) {
        return rightResult;
    }

    return "";
}

// using tree to find the decoder 
char HuffDecoder_1(HuffmanNode* &point, char ch) {
    char decodedLine = 127;

    if (ch == '0') {
        point = point->left;
    }
    else if (ch == '1') {
        point = point->right;
    }

    if (point->left == nullptr && point->right == nullptr) {
        decodedLine = point->data;
        return decodedLine;
    }
    return 127;
}// give back a char (had decoded)

// print the tree
void printHuffmanTree(HuffmanNode* root, string code = "") {
    if (root == nullptr) {
        return;
    }

    if (root->data != 127) {
        cout << "Character: " << root->data << ", Frequency: " << root->f << ", Code: " << code << endl;
    }

    printHuffmanTree(root->left, code + "0");
    printHuffmanTree(root->right, code + "1");
}

// save the huffmantree in outfile
void serializeHuffmanTree(HuffmanNode* root, ofstream& outfile) {
    if (root == nullptr) {
        outfile << "null ";
        return;
    }

    outfile << root->data << " " << root->f << " ";

    serializeHuffmanTree(root->left, outfile);
    serializeHuffmanTree(root->right, outfile);
}

// read the huffmantree from infile
HuffmanNode* deserializeHuffmanTree(ifstream& infile) {
    string data;
    int f;
    infile >> data;

    if (data == "null") {
        return nullptr;
    }

    infile >> f;
    char ch =data[0];

    HuffmanNode* node = new HuffmanNode(ch, f);

    node->left = deserializeHuffmanTree(infile);
    node->right = deserializeHuffmanTree(infile);

    return node;
}

// save the tree by tree size and print to term
void printandsaveTree(HuffmanNode* node, ofstream& outfile, bool isLeft = false, string prefix = "") {
    if (node != nullptr) {
        cout << (isLeft ? "L--" : "R--") << prefix << node->data << " (" << node->f << ")" << endl;
        outfile << (isLeft ? "L--" : "R--") << prefix << node->data << " (" << node->f << ")" << endl;

        printandsaveTree(node->left,outfile, true, prefix + (isLeft ? "    " : "|   "));
        printandsaveTree(node->right, outfile, false, prefix + (isLeft ? "|   " : "    "));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// get the encoder table and decoder table
//void buildHuffmanCodes(HuffmanNode* root, map<char, string>& huffmanEncodes, map<string, char>& huffmanDecodes, string code = "")
//{
//    if (root == nullptr) {
//        return;
//    }
//
//    if (root->data != '#') {
//        huffmanEncodes[root->data] = code;
//        huffmanDecodes[code] = root->data;
//    }
//
//    buildHuffmanCodes(root->left, huffmanEncodes, huffmanDecodes, code + "0");
//    buildHuffmanCodes(root->right, huffmanEncodes, huffmanDecodes, code + "1");
//}

// using pairs to find the encoder
//string HuffEncoder(string text, map<char, string>&huffmanCodes) {
//    string encodedText = "";
//    for (char c : text) {
//        encodedText += huffmanCodes[c];
//    }
//    return encodedText;
//}

// using pairs to find the decoder
//string Huffdecoder(string &text, map<string, char>& huffmanDecodes) {
//    string decodedText = "";
//    string base = "";
//    size_t i = 0;
//
//    while (i < text.size()) {
//        base += text[i];
//        if (huffmanDecodes.count(base) > 0) {
//            decodedText += base;
//            text.erase(0, i + 1);
//            base = "";
//            i = 0; // Reset the index
//        }
//        else {
//            i++;
//        }
//    }
//
//    return decodedText;
//}