//#include "stdafx.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <bitset>
#include <unordered_map>
#include <sstream>
#include "HuffmanTree.h"

using namespace std;

inline bool HuffmanTree::getBit(unsigned char byte, int position) const {
    return (byte & BITMASK[position]);
}

// Usage
// mybyte = setBit(mybyte,4);
// This sets the bit in position 4
inline unsigned char HuffmanTree::setBit(unsigned char byte, int position) const {
    return byte | BITMASK[position];
}

void HuffmanTree::printBits(char binary, std::ostream &out) const {
    for (size_t i = 0; i < sizeof(char) * 8; i++) {
        if (getBit(binary, i)) {
            out << 1;
        }
        else {
            out << 0;
        }
    }
}

void HuffmanTree::printBinary(vector<char> bytes, std::ostream &out) const {
    for (char byte: bytes) {
        printBits(byte, out);
        out << "-";
    }

}

string HuffmanTree::getCode(char letter) const {
    string code = "";
    int j = 0;
    BinaryNode *temp = root;
    for (int i = 0; i <= temp->element.size(); i++) {
        if (temp->element[i] - letter == 0) {
            break;
        }
        if (i == temp->element.size()) {
            return code + "not found";
        }
    }
    while (true) {
        if (temp->left != nullptr) {
            for (int i = 0; i < temp->left->element[i]; i++) {
                if (temp->left->element[i] - letter == 0) {
                    temp = temp->left;
                    code = code + '0';
                    if (temp->left == nullptr && temp->right == nullptr) {
                        return code;
                    }
                }
            }
        }
        if (temp->right != nullptr) {
            for (int i = 0; i < temp->right->element[i]; i++) {
                if (temp->right->element[i] - letter == 0) {
                    temp = temp->right;
                    code = code + '1';
                    if (temp->left == nullptr && temp->right == nullptr) {
                        return code;
                    }
                }
            }
        }
    }
}

void HuffmanTree::makeEmpty(BinaryNode *&t) {
    if (t->left != nullptr) {
        makeEmpty(t->left);
    }
    if (t->right != nullptr) {
        makeEmpty(t->right);
    }
    delete t;
}

void HuffmanTree::printTree(BinaryNode *node, std::ostream &out) const {
    if (node->left != nullptr) {
        printTree(node->left, out);
    }
    if (node->right != nullptr) {
        printTree(node->right, out);
    }
    if (node->left == nullptr && node->right == nullptr) {
        out << node->element << ": " << node->frequency << "|";
    }
}

void HuffmanTree::printCodes(BinaryNode *node, std::ostream &out, string code) const {
    if (node->left != nullptr) {
        printCodes(node->left, out, code + '0');
    }
    if (node->right != nullptr) {
        printCodes(node->right, out, code + '1');
    }
    if (node->left == nullptr && node->right == nullptr) {
        out << node->element << ": " << code << "|";
    }
}


void HuffmanTree::saveTree(BinaryNode *current,
                           string code) { //we pass in the root with an empty string
    // need to write code    //left will be tagged as 1
    //Right will be tagged as 0
    if (current->left != nullptr) {
        saveTree(current->left, code + '0');
    }
    if (current->right != nullptr) {
        saveTree(current->right, code + '1');
    }
    if (current->left == nullptr && current->right == nullptr){
        codeLookup[current->element[0]] = code;
    }
}

// writes tree information to file so the tree can be rebuilt when unzipping
void HuffmanTree::saveTree(std::ostream &compressedFileStream) {
    //TODO Project 2 need to write code
    // calls recursive function
}


void HuffmanTree::rebuildTree(BinaryNode *node, string element, string codedRoute) {
    //TODO Project 2 need to write code


}

void HuffmanTree::rebuildTree(ifstream &compressedFile) {
    // read info from file
    // use info to build tree

    //TODO Project 2 need to write code
    // calls recursive function
}

HuffmanTree::BinaryNode *HuffmanTree::buildTree(string frequencyText) {
    priority_queue<HuffmanTree::BinaryNode *,
            vector<HuffmanTree::BinaryNode *>,
            compareBinaryNodes> nodes;
    BinaryNode *thing1 = nullptr;
    BinaryNode *thing2 = nullptr;
    char fArray[128]{0};
    for (int i = 0; i < frequencyText.size(); i++) {
        fArray[frequencyText[i]]++;
    }
    for (int i = 0; i < 128; i++) {
        if (fArray[i] > 0) {
            BinaryNode *temp = new BinaryNode(string() + char(i), fArray[i]);
            nodes.push(temp);
        }
    }
    while (nodes.size() > 1) {
        thing1 = nodes.top();
        nodes.pop();
        thing2 = nodes.top();
        nodes.pop();
        nodes.push(new BinaryNode(thing1->element + thing2->element,
                                  thing1->frequency + thing2->frequency, thing1,
                                  thing2));
    }
    return nodes.top();
}

HuffmanTree::HuffmanTree(string
                         frequencyText) {
    root = buildTree(frequencyText);
    saveTree(root, string());
}

HuffmanTree::HuffmanTree(ifstream &frequencyStream) {
    std::string frequencyText((std::istreambuf_iterator<char>(frequencyStream)),
                              std::istreambuf_iterator<char>());    // builds the frequencyText by using STL iterators
    frequencyStream.close();
    if (frequencyText.size() > 0) {
        root = buildTree(frequencyText);
        saveTree(root, string());   // build the lookupTable for codes
    }
}

HuffmanTree::~HuffmanTree() {
    makeEmpty(root);
}

// print out the char and its encoding
void HuffmanTree::printCodes(std::ostream &out) const {
    printCodes(root, out, string());
}

// prints out the char and frequency
void HuffmanTree::printTree(std::ostream &out) const {
    printTree(root, out);
}

void HuffmanTree::makeEmpty() {
    makeEmpty(root);
}

string HuffmanTree::decode(vector<char> encodedBytes) {
    string decoded;
    int iterator = 0;
    BinaryNode *nodeIterator = root;
    while (iterator < encodedBytes.size()) {
        if (encodedBytes[iterator] == '0') {
            nodeIterator = nodeIterator->left;
            iterator = iterator + 1;
        }
        else if (encodedBytes[iterator] == '1') {
            nodeIterator = nodeIterator->right;
            iterator = iterator + 1;
        }
        else {
            decoded = decoded + nodeIterator->element;
            nodeIterator = root;
            iterator = iterator + 1;
        }
    }
    return decoded;
}

vector<char> HuffmanTree::encode(string stringToEncode) {
    stringToEncode.push_back(
            EOFCharacter); // needed when encoding message for file I/O
    vector<char> encoded;
    string temp = "";
    for (int i = 0; i < stringToEncode.size(); i++) {
        for (int j = 0; j < root->element.size(); j++) {
            if (root->element[j] - stringToEncode[i] == 0) {
                temp = temp + getCode(stringToEncode[i]);
                temp = temp + EOFCharacter;
                break;
            }
        }
    }
    for (int i = 0; i < temp.size(); i++) {
        encoded.push_back(temp[i]);
    }
    return encoded;
}

void HuffmanTree::uncompressFile(string compressedFileName,
                                 string uncompressedToFileName) {
    //TODO Project 2 need to write code

    // NOTE: when opening the compressedFile, you need to open in
    //  binary mode for reading..hmmm..why is that?
}

void HuffmanTree::compressFile(string compressToFileName,
                               string uncompressedFileName, bool buildNewTree) {
    //TODO Project 2 need to write code

    // NOTE: when opening the compressedFile, you need to open in
    //  binary mode for writing..hmmm..why is that?
}
/*
 * "C:\Users\alexv\CS 233\HuffmanCode\cmake-build-debug\HuffmanCode.exe"
priority_queue test area:
Top: 100
New Top: 10
10
100
101
111
1011
1110
1111


unordered_map test area:
c has: compiler
d = 10010
c = changed
b = ballon
a = apple
Number of items stored in map: 4



Test 1


Building the tree from: HHHHEELLLLLLLOO WOOOOORRLLLLLLDP


printTree:
L: 13|E: 2|R: 2|H: 4|D: 1|W: 1| : 1|P: 1|O: 7|

printCodes:
L: 0|E: 1000|R: 1001|H: 101|D: 11000|W: 11001| : 11010|P: 11011|O: 111|


Code L :0
Code D :11000


Test 2

L: 0|E: 1000|R: 1001|H: 101|D: 11000|W: 11001| : 11010|P: 11011|O: 111|
10001100-00001100-10001100-00000000-10001100-00001100-00001100-00001100-00000000-00001100-00000000-10001100-10001100-00001100-10001100-10001100-00000000-
HELP:

Press any key to continue . . . k


Process finished with exit code 0
*/