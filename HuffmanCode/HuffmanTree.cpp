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
        out << endl;
    }

}

string HuffmanTree::getCode(char letter) const {
    int check = 0;
    string code;
    for (int i = 0; i < root->element.size(); i++) {
        if (letter == root->element[i]) {
            check = 1;
            break;
        }
    }
    if (check == 1) {
        code = codeLookup.at(letter);
    }
    return code;
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
        out << node->element << ": " << node->frequency << "|" << endl;
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
        out << node->element << ": " << code << "|" << endl;
    }
}

/*The idea of savetree is to save our letter with a key being the letter
 * and pairing that key is a binary code that is create by recursively going
 * down the tree*/
void HuffmanTree::saveTree(BinaryNode *current,
                           string code) {
    if (current->left != nullptr) {
        saveTree(current->left, code + '0');
    }
    if (current->right != nullptr) {
        saveTree(current->right, code + '1');
    }
    if (current->left == nullptr && current->right == nullptr) {
        codeLookup[current->element[0]] = code;
    }
}

// writes tree information to file so the tree can be rebuilt when unzipping
void HuffmanTree::saveTree(std::ostream &compressedFileStream) {
    //TODO Project 2 need to write code
    // calls recursive function
    int mapSize = codeLookup.size();
    compressedFileStream << mapSize << ":";
    /*this loop makes sure that End of File character isn't added
     * into the file to cause a segmentation fault*/
    for (auto pair: codeLookup) {
        if (pair.first == 0) {
        }
        else {
            //Pair.first = key , Pair.second = binary code
            compressedFileStream << pair.first << " = " << pair.second << ':' << endl;
        }
    }
}


void HuffmanTree::rebuildTree(BinaryNode *node, string element, string codedRoute) {
    //TODO Project 2 need to write code


}

void HuffmanTree::rebuildTree(ifstream &compressedFile) {
    // read info from file
    // use info to build tree
    string codedRoute;
    codedRoute = compressedFile.good();
    rebuildTree(root, string(), codedRoute);
    //TODO Project 2 need to write code
    // calls recursive function
}

/*
 * The Idea behind this function is to create
 * our set up adding into the priority queue
 * as well as combine what's in our priority queue*/
HuffmanTree::BinaryNode *HuffmanTree::buildTree(string frequencyText) {
    priority_queue<HuffmanTree::BinaryNode *,
            vector<HuffmanTree::BinaryNode *>,
            compareBinaryNodes> nodes;
    BinaryNode *thing1 = nullptr;
    BinaryNode *thing2 = nullptr;
    /*These two loops help combine and add up the
     * amount of how many are in the text
     * with the array size of 128 being the max ascii value*/
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
    /*This while loop is combining all the frequency text together
     * to make our huffman tree based on the priority queue*/
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
/*The idea of decode is to take a encoded string and roll down
 * the Huffman tree to find the encoded letter*/
string HuffmanTree::decode(vector<char> encodedBytes) {
    string decoded;
    int iterator = 0;
    BinaryNode *nodeIterator = root;
    while (iterator < encodedBytes.size()) {
        if (nodeIterator->left == nullptr || nodeIterator->right == nullptr) {
            decoded = decoded + nodeIterator->element;
            nodeIterator = root;
            iterator = iterator + 1;
        }
        else if (encodedBytes[iterator] == '0') {
            nodeIterator = nodeIterator->left;
            iterator = iterator + 1;
        }
        else if (encodedBytes[iterator] == '1') {
            nodeIterator = nodeIterator->right;
            iterator += 1;
        }
        else {
            decoded = decoded + nodeIterator->element;
            nodeIterator = root;
            iterator = iterator + 1;
        }
    }
    return decoded;
}

/*The idea of this function is to take a letter and change its bit to
 * and push back its bit mask to a vector*/
vector<char> HuffmanTree::encode(string stringToEncode) {
    stringToEncode.push_back(
            EOFCharacter); // needed when encoding message for file I/O
    vector<char> encoded;
//    encoded.push_back(0);
    string temp;
    /*This for loop is in charge of creating a string based
     * on the letters binary code from the codeLookup*/
    for (char ch: stringToEncode) {
        for (char i: codeLookup[ch]) {
            temp.push_back(i);
        }
    }
    int bitPosition = 7;
    int iterator = 0;
    char ch = 0;
    /*This while loop is en charge of changing the bit mask when encountering
     * a 1 or 0 and turning off or on that bit position*/
    while (temp.size() > iterator) {
        if (bitPosition < 0) {
            encoded.push_back(ch);
            ch++;
            bitPosition = 7;
        }
        if (temp[iterator] == '1') {
            setBit(ch, bitPosition);
        }
        bitPosition--;
        iterator++;
    }
    return encoded;

}

/*The idea on an UncompressFile is to rebuild and decode from the compressed file*/
void HuffmanTree::uncompressFile(string compressedFileName,
                                 string uncompressedToFileName) {
    //TODO Project 2 need to write code
    ifstream compressedFile(compressedFileName, ios::out | ios::binary);
    ofstream fOut(uncompressedToFileName, ios::out | ios::binary);
    if (compressedFile.fail()) {
        cout << "failed to open: " << compressedFileName << " in uncompressFile" << endl;
    }
    ostringstream temp;
    temp << compressedFile.rdbuf();
    const string &s = temp.str();
    vector<char> encodedVec;
    string unCompressedString;
    /*The idea for this for loop is to push back the 1's and 0's
     * and for setting up to decode vector we will pass in*/
    for (int i = 8; i < s.size(); i++) {
        if (s[i] == '1' || s[i] == '0' || s[i] == ':') {
            encodedVec.push_back(s[i]);
        }
    }
    unCompressedString = decode(encodedVec);
    /*This loop is outputting the decoded string into a file from
     * UnCompressedString*/
    for (char i: unCompressedString) {
        fOut << i;
    }
    fOut.close();
    compressedFile.close();
    // NOTE: when opening the compressedFile, you need to open in
    // binary mode for reading..hmmm..why is that?
}

/*The idea of the CompressFIle is to save our bit masks into a file
 * that we set in our encoded function*/
void HuffmanTree::compressFile(string compressToFileName,
                               string uncompressedFileName, bool buildNewTree) {
    //TODO Project 2 need to write code
    ifstream compressedFile(uncompressedFileName, ios::out | ios::binary);
    ofstream fOut(compressToFileName, ios::out | ios::binary);
    if (compressedFile.fail()) {
        cout << "File failed to open: " << uncompressedFileName << "in compressFile"
             << endl;
    }
    ostringstream temp;
    temp << compressedFile.rdbuf();
    const string &s = temp.str();
    vector<char> compressed = encode(s);
    /*SaveTree is the idea to output the saved encode bit mask
     * to a file*/
    saveTree(fOut);
    compressedFile.close();
    fOut.close();
}
