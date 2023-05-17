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
    cout << "\n\nTest 3\n";
    std::ifstream frequencyStream("Bigo.txt");
    HuffmanTree tree2(frequencyStream);
    tree2.printTree();
    tree2.printCodes();

/*
    Side Note: I am using a text.txt file because BigO.bin isn't working on clion, however
    I can open the bin file using a normal text with clion extension to open any document in binary
 */
    tree2.compressFile("text.txt", "Bigo.txt");
    tree2.printCodes();
    tree2.uncompressFile("text.txt", "BigORebuilt.txt");
    tree2.printTree();
    tree2.printCodes();

    ////Test 4
    cout << "\n\nTest 4\n";
    std::ifstream frequencyStream2("20000leagues.txt");
    HuffmanTree tree3(frequencyStream2);
    tree3.printTree();
    tree3.printCodes();
    cout << "Code L :" << tree3.getCode('L') << endl;
    tree3.compressFile("20000leaguesComp.bin" ,"20000leagues.txt",true);
    tree3.uncompressFile("20000leaguesComp.bin", "20000leaguesRebuilt.txt");
    tree3.printTree();
    tree3.printCodes();

    // Try Other Files

    //// read in text file create string - might be useful
    std::ifstream bigtext("20000leagues.txt");
    std::string big((std::istreambuf_iterator<char>(bigtext)),
    				   std::istreambuf_iterator<char>());

    cout << endl;
    system("pause");
    return 0;
}
/*
"C:\Users\alexv\CS 233\Huffman\cmake-build-debug\Huffman.exe"
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
L: 13|
E: 2|
R: 2|
H: 4|
D: 1|
W: 1|
 : 1|
P: 1|
O: 7|


printCodes:
L: 0|
E: 1000|
R: 1001|
H: 101|
D: 11000|
W: 11001|
 : 11010|
P: 11011|
O: 111|



Code L :0
Code D :11000


Test 2

L: 0|
E: 1000|
R: 1001|
H: 101|
D: 11000|
W: 11001|
 : 11010|
P: 11011|
O: 111|

00000000-

LERHDW PO:


Test 3
a: 14|
r: 7|
O: 2|
:: 2|
0: 1|
A: 1|
": 2|
e: 16|
t: 16|
 : 61|
d: 8|
.: 4|
=: 1|
w: 1|
T: 2|
k: 4|
g: 4|
v: 2|
F: 1|
D: 1|
p: 5|
o: 20|
(: 5|
x: 1|
y: 1|
,: 3|
m: 5|
l: 5|
): 5|
?: 3|
b: 3|
i: 12|
f: 13|
s: 13|
n: 26|

: 6|
u: 7|
h: 7|
c: 7|
a: 0000|
r: 00010|
O: 0001100|
:: 0001101|
0: 00011100|
A: 00011101|
": 0001111|
e: 0010|
t: 0011|
 : 01|
d: 10000|
.: 100010|
=: 10001100|
w: 10001101|
T: 1000111|
k: 100100|
g: 100101|
v: 1001100|
F: 10011010|
D: 10011011|
p: 100111|
o: 1010|
(: 101100|
x: 10110100|
y: 10110101|
,: 1011011|
m: 101110|
l: 101111|
): 110000|
?: 1100010|
b: 1100011|
i: 11001|
f: 11010|
s: 11011|
n: 1110|

: 111100|
u: 111101|
h: 111110|
c: 111111|
a: 0000|
r: 00010|
O: 0001100|
:: 0001101|
0: 00011100|
A: 00011101|
": 0001111|
e: 0010|
t: 0011|
 : 01|
d: 10000|
.: 100010|
=: 10001100|
w: 10001101|
T: 1000111|
k: 100100|
g: 100101|
v: 1001100|
F: 10011010|
D: 10011011|
p: 100111|
o: 1010|
(: 101100|
x: 10110100|
y: 10110101|
,: 1011011|
m: 101110|
l: 101111|
): 110000|
?: 1100010|
b: 1100011|
i: 11001|
f: 11010|
s: 11011|
n: 1110|

: 111100|
u: 111101|
h: 111110|
c: 111111|
a: 14|
r: 7|
O: 2|
:: 2|
0: 1|
A: 1|
": 2|
e: 16|
t: 16|
 : 61|
d: 8|
.: 4|
=: 1|
w: 1|
T: 2|
k: 4|
g: 4|
v: 2|
F: 1|
D: 1|
p: 5|
o: 20|
(: 5|
x: 1|
y: 1|
,: 3|
m: 5|
l: 5|
): 5|
?: 3|
b: 3|
i: 12|
f: 13|
s: 13|
n: 26|

: 6|
u: 7|
h: 7|
c: 7|
a: 0000|
r: 00010|
O: 0001100|
:: 0001101|
0: 00011100|
A: 00011101|
": 0001111|
e: 0010|
t: 0011|
 : 01|
d: 10000|
.: 100010|
=: 10001100|
w: 10001101|
T: 1000111|
k: 100100|
g: 100101|
v: 1001100|
F: 10011010|
D: 10011011|
p: 100111|
o: 1010|
(: 101100|
x: 10110100|
y: 10110101|
,: 1011011|
m: 101110|
l: 101111|
): 110000|
?: 1100010|
b: 1100011|
i: 11001|
f: 11010|
s: 11011|
n: 1110|

: 111100|
u: 111101|
h: 111110|
c: 111111|


Test 4
c: 21|
K: 23|
]: 23|
[: 23|
?: 90|
": 91|
7: 91|
J: 97|
5: 98|
9: 48|
z: 50|
W: 99|
S: 100|
6: 103|
/: 11|
`: 13|
1: 27|
X: 54|
C: 105|
f: 108|

: 108|
3: 110|
a: 110|
t: 111|
T: 113|
O: 114|
x: 117|
g: 117|
r: 117|
 : 28|
Z: 6|
Q: 9|
b: 15|
.: 30|
F: 31|
P: 120|
V: 121|
A: 124|
U: 126|
l: 32|
}: 16|
{: 16|
): 65|
(: 65|
m: 66|
@: 68|
p: 69|
4: 73|
;: 18|
u: 9|
%: 2|
R: 3|
=: 1|
#: 1|
~: 1|
_: 3|
j: 43|
*: 85|
8: 87|
c: 0000000|
K: 0000001|
]: 0000010|
[: 0000011|
?: 00001|
": 00010|
7: 00011|
J: 00100|
5: 00101|
9: 001100|
z: 001101|
W: 00111|
S: 01000|
6: 01001|
/: 01010000|
`: 01010001|
1: 0101001|
X: 010101|
C: 01011|
f: 01100|

: 01101|
3: 01110|
a: 01111|
t: 10000|
T: 10001|
O: 10010|
x: 10011|
g: 10100|
r: 10101|
 : 1011000|
Z: 101100100|
Q: 101100101|
b: 10110011|
.: 1011010|
F: 1011011|
P: 10111|
V: 11000|
A: 11001|
U: 11010|
l: 1101100|
}: 11011010|
{: 11011011|
): 110111|
(: 111000|
m: 111001|
@: 111010|
p: 111011|
4: 111100|
;: 11110100|
u: 111101010|
%: 11110101100|
R: 11110101101|
=: 111101011100|
#: 1111010111010|
~: 1111010111011|
_: 11110101111|
j: 1111011|
*: 111110|
8: 111111|
Code L :
c: 21|
K: 23|
]: 23|
[: 23|
?: 90|
": 91|
7: 91|
J: 97|
5: 98|
9: 48|
z: 50|
W: 99|
S: 100|
6: 103|
/: 11|
`: 13|
1: 27|
X: 54|
C: 105|
f: 108|

: 108|
3: 110|
a: 110|
t: 111|
T: 113|
O: 114|
x: 117|
g: 117|
r: 117|
 : 28|
Z: 6|
Q: 9|
b: 15|
.: 30|
F: 31|
P: 120|
V: 121|
A: 124|
U: 126|
l: 32|
}: 16|
{: 16|
): 65|
(: 65|
m: 66|
@: 68|
p: 69|
4: 73|
;: 18|
u: 9|
%: 2|
R: 3|
=: 1|
#: 1|
~: 1|
_: 3|
j: 43|
*: 85|
8: 87|
c: 0000000|
K: 0000001|
]: 0000010|
[: 0000011|
?: 00001|
": 00010|
7: 00011|
J: 00100|
5: 00101|
9: 001100|
z: 001101|
W: 00111|
S: 01000|
6: 01001|
/: 01010000|
`: 01010001|
1: 0101001|
X: 010101|
C: 01011|
f: 01100|

: 01101|
3: 01110|
a: 01111|
t: 10000|
T: 10001|
O: 10010|
x: 10011|
g: 10100|
r: 10101|
 : 1011000|
Z: 101100100|
Q: 101100101|
b: 10110011|
.: 1011010|
F: 1011011|
P: 10111|
V: 11000|
A: 11001|
U: 11010|
l: 1101100|
}: 11011010|
{: 11011011|
): 110111|
(: 111000|
m: 111001|
@: 111010|
p: 111011|
4: 111100|
;: 11110100|
u: 111101010|
%: 11110101100|
R: 11110101101|
=: 111101011100|
#: 1111010111010|
~: 1111010111011|
_: 11110101111|
j: 1111011|
*: 111110|
8: 111111|

Press any key to continue . . . hj


Process finished with exit code 0
*/
