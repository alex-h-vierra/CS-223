// HuffmanCoding.cpp : Defines the entry point for the console application.
//


#include <string>
#include <fstream>
#include <streambuf>
#include <queue>
#include <functional>

#include "HuffmanTree.h"

using namespace std;

int main() {

    // example code for priority_queue....play with it and then remove/comment out
    cout << "priority_queue test area: \n";
    priority_queue<int, vector<int>, greater<int> > pq;

    pq.push(111);
    pq.push(1111);
    pq.push(1011);
    pq.push(100);
    pq.push(1110);
    pq.push(101);

    cout << "Top: " << pq.top() << endl;
    pq.push(10);
    cout << "New Top: " << pq.top() << endl;

    while (!pq.empty()) {
        cout << pq.top() << endl;
        pq.pop();
    }
    cout << endl << endl;

    // example code for unordered_map....play with it and then remove/comment out
    //  an unordered_map can be used to store the char and its encoded
    //  values after you have built the tree
    cout << "unordered_map test area: \n";
    unordered_map<char, string> exampleMap;
    exampleMap['a'] = "apple";			// creates a new entry if 'a' is not in the map and associates "apple" with 'a'
    exampleMap['b'] = "ballon";
    exampleMap['c'] = "compiler";
    exampleMap['d'] = "10010";

    cout << "c has: " << exampleMap['c'] << endl;

    exampleMap['c'] = "changed";
    for (auto pair : exampleMap) {
        cout << pair.first << " = " << pair.second << endl;
    }
    cout << "Number of items stored in map: " << exampleMap.size();
    cout << endl << endl;


    // SUGGESTION: write and test the functions in the order called below
    //         (some of the functions may need to call other private functions)

    //Test 1
    cout << "\n\nTest 1\n";
    cout << "\n\nBuilding the tree from: HHHHEELLLLLLLOO WOOOOORRLLLLLLDP\n";
    HuffmanTree tree("HHHHEELLLLLLLOO WOOOOORRLLLLLLDP");
    //
    cout << "\n\nprintTree: \n";
    tree.printTree();
    //
    cout << "\n\nprintCodes:\n";
    tree.printCodes();
    cout << endl << endl;

    cout << "\nCode L :" <<tree.getCode('L') << endl;
    cout << "Code D :" << tree.getCode('D') << endl;


    //Test 2
    cout << "\n\nTest 2\n\n";
    vector<char> encoded = tree.encode("HELP");
    tree.printCodes();
    cout << endl;
    tree.printBinary(encoded);
//      don't call for lab:    // for lab, instead output chars inside encoded
    cout << endl;
    cout << tree.decode(encoded) << ":" << endl;
    // LAB 3: Should run up to here with the above functions working with chars '1' and '0'
    //			instead of making the changes at the binary level

    //Test 3
    //cout << "\n\nTest 3\n";
    //std::ifstream frequencyStream("Bigo.txt");
    //HuffmanTree tree2(frequencyStream);
    //tree2.printTree();
    //tree2.printCodes();

    //tree2.compressFile("BigO.bin", "Bigo.txt");
    //tree2.printCodes();
    //tree2.uncompressFile("BigO.bin", "BigORebuilt.txt");
    //tree2.printTree();
    //tree2.printCodes();

    ////Test 4
    //cout << "\n\nTest 4\n";
    //std::ifstream frequencyStream2("20000leagues.txt");
    //HuffmanTree tree3(frequencyStream2);
    //tree3.printTree();
    //tree3.printCodes();
    //cout << "Code L :" << tree3.getCode('L') << endl;
    //tree3.compressFile("20000leaguesComp.bin" ,"20000leagues.txt",true);
    //tree3.uncompressFile("20000leaguesComp.bin", "20000leaguesRebuilt.txt");
    //tree3.printTree();
    //tree3.printCodes();

    // Try Other Files

    //// read in text file create string - might be useful
    //std::ifstream bigtext("20000leagues.txt");
    //std::string big((std::istreambuf_iterator<char>(bigtext)),
    //				   std::istreambuf_iterator<char>());

    cout << endl;
    system("pause");
    return 0;
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