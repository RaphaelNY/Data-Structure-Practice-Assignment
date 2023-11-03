#include <iostream>
#include <fstream>
#include "huffmanTree.h"
#include <string>

using namespace std;

void Rawdata_r1(char Dlist[], int Flist[], int &numPairs) {

    cout << "Enter the number of character-frequency pairs: ";
    cin >> numPairs;

    for (int i = 0; i < numPairs; i++) {
        char character;
        int frequency;

        cout << "Enter character " << i + 1 << ": ";
        cin >> character;

        cout << "Enter frequency for character " << character << ": ";
        cin >> frequency;

        Dlist[i] = character;
        Flist[i] = frequency;
    }
}

//vector<pair<char, int>> Rawdata_r(vector<pair<char, int>> frequencies) {
//    int numPairs;
//
//    cout << "Enter the number of character-frequency pairs: ";
//    cin >> numPairs;
//
//    for (int i = 0; i < numPairs; i++) {
//        char character;
//        int frequency;
//
//        cout << "Enter character " << i + 1 << ": ";
//        cin >> character;
//
//        cout << "Enter frequency for character " << character << ": ";
//        cin >> frequency;
//
//        frequencies.push_back(make_pair(character, frequency));
//    }
//    return frequencies;
//}//  request user enter the char-frequencies

// count the char's f of your file 
void Filecharcount(string read_path, char Dlist[], int Flist[], int& numPairs) {
    numPairs = 128;
    for (int i = 0; i < numPairs; i++) {
        Flist[i] = 0;
    }
    ifstream infile(read_path);
    if (infile.is_open()) {
        char c;
        while (infile.get(c)) {
            Dlist[c] = c;
            Flist[c]++;
        }

        infile.close();
    }
    else {
        cerr << "Unable to open the infile." << endl;
    }
}
// read ToBeTran and write to CodeFile
void FilereadandEncoder(string read_path, string save_path, HuffmanNode* root) {
    ifstream infile(read_path);
    HuffmanNode* point = root;

    if (infile.is_open()) {
        ofstream outfile(save_path);

        if (outfile.is_open()) {
            char c;
            string ch;

            while (infile.get(c)) {
                point = root;
                ch = HuffEncoder_1(point, c);
                outfile << ch;
            }
            outfile.close();
        }
        else {
            cerr << "Unable to open the outfile." << endl;
        }

        infile.close();
    }
    else {
        cerr << "Unable to open the infile." << endl;
    }
}

// read the readpath(CodeFile) && decoder the char && write in savepath(TextFile)
void FilereadandDecoder(string read_path, string save_path, HuffmanNode* root) {
    ifstream infile(read_path);
    HuffmanNode* point = root;
    if (infile.is_open()) {
        ofstream outfile(save_path);
        if (outfile.is_open()) {
            char c;
            char ch;
            while (infile.get(c)) {
                ch = HuffDecoder_1(point, c);
                if (ch == 127) {
                    continue;
                }
                else {
                    // add to save file
                    outfile.put(ch);
                    point = root;
                }
            }
            outfile.close();
        }
        else {
            cerr << "Unable to open the outfile." << endl;
        }

        infile.close();
    }
    else {
        cerr << "Unable to open the infile." << endl;
    }
}

// print 50chars once from CodeFile && print in term && save 50chars one line to CodePrin
void FilereadandPrint(string read_path, string save_path) {
    ifstream infile(read_path);
    if (infile.is_open()) {
        ofstream outfile(save_path);
        if (outfile.is_open()) {
            char c;
            string line;
            int charCount = 0;
            while (infile.get(c)) {
                line += c;
                charCount++;

                if (charCount == 50) {
                    cout << line;
                    outfile << line << endl;
                    charCount = 0;

                    line.clear();
                }
            }

            if (!line.empty()) {
                cout << line;
                outfile << line << endl;
            }

            outfile.close();
        }
        else {
            cerr << "Unable to open the outfile." << endl;
        }

        infile.close();
    }
    else {
        cerr << "Unable to open the infile." << endl;
    }
}

// function save the tree
void saveHuffmanTreeToFile(HuffmanNode* root, string save_path) {
    ofstream outfile(save_path, ofstream::trunc);

    if (outfile.is_open()) {
        serializeHuffmanTree(root, outfile);
        outfile.close();
    }
    else {
        cerr << "Unable to open the file for saving Huffman tree." << endl;
    }
}

// save and print the tree to file by tree size
void saveprintTreeToFile(HuffmanNode* root, string save_path) {
    ofstream outfile(save_path);
    if (outfile.is_open()) {
        printandsaveTree(root, outfile, false, "");
        outfile.close();
    }
    else {
        cerr << "Unable to open the file for saving Huffman tree." << endl;
    }
}

// function read the tree
HuffmanNode* loadHuffmanTreeFromFile(string read_path) {
    ifstream infile(read_path);
    if (infile.is_open()) {
        HuffmanNode* root = deserializeHuffmanTree(infile);
        infile.close();
        return root;
    }
    else {
        cerr << "Unable to open the file for loading Huffman tree. maybe you hadn't told me the rule" << endl;
    }

    return nullptr;
}

void treesizeshowandsave(HuffmanNode* root, string save_path) {
    printHuffmanTree(root);
    saveHuffmanTreeToFile(root, save_path);
}