#include "pch.h"
#include <iostream>
#include "Graph.h"
#include <queue>

/*
 * Note I get different distances when finding the same node from the same
 * starting spot, however I do get the "sortest path" to the node in that instance
 * */
using namespace std;

int main()
{
    Graph graph;
    for (int i = 0; i < 18; i++)
    {
        graph.addVertex(i,i);
    }
    for (int i = 20; i < 38; i++)
    {
        graph.addVertex(i,i);
    }
// 0
//addEdge(Vertex1, Vertex2, edge edges)
    graph.addEdge(0, 1, 8);
    graph.addEdge(0, 2, 8);
    graph.addEdge(0, 7, 4);
    graph.addEdge(0, 14, 4);
    graph.addEdge(0, 20, 8);
// 1
    graph.addEdge(1, 5, 8);
// 2
    graph.addEdge(2, 3, 5);
    graph.addEdge(2, 6, 2);
// 3
    graph.addEdge(3, 17, 1);
// 4
    graph.addEdge(4, 5, 7);
    graph.addEdge(4, 7, 3);
    graph.addEdge(4, 8, 5);
// 5
    graph.addEdge(5, 6, 8);
    graph.addEdge(5, 8, 1);
    graph.addEdge(5, 25, 6);
// 6 All edges added
// 7
    graph.addEdge(7, 11, 1);
// 8
    graph.addEdge(8, 11, 8);
    graph.addEdge(8, 12, 7);
// 9
    graph.addEdge(9, 10, 6);
    graph.addEdge(9, 12, 9);
    graph.addEdge(9, 13, 3);
// 10
    graph.addEdge(10, 13, 5);
    graph.addEdge(10, 17, 2);
    graph.addEdge(10, 30, 4);
// 11
    graph.addEdge(11, 12, 2);
    graph.addEdge(11, 14, 6);
// 12
    graph.addEdge(12, 13, 2);
    graph.addEdge(12, 15, 8);
    graph.addEdge(12, 16, 6);
// 13
    graph.addEdge(13, 17, 9);
// 14 All edges added
// 15
    graph.addEdge(15, 35, 7);
// 16
    graph.addEdge(16, 17, 1);
// 17 All edges added
// 20
    graph.addEdge(20, 21, 1);
    graph.addEdge(20, 24, 3);
    graph.addEdge(20, 27, 5);
    graph.addEdge(20, 34, 1);
// 21
    graph.addEdge(21, 24, 1);
// 22
    graph.addEdge(22, 23, 8);
    graph.addEdge(22, 25, 1);
    graph.addEdge(22, 26, 8);
// 23
    graph.addEdge(23, 26, 2);
    graph.addEdge(23, 37, 2);
// 24
    graph.addEdge(24, 27, 2);
    graph.addEdge(24, 28, 6);
// 25
    graph.addEdge(25, 26, 7);
    graph.addEdge(25, 28, 1);
    graph.addEdge(25, 29, 6);
// 26
    graph.addEdge(26, 29, 9);
    graph.addEdge(26, 30, 5);
// 27
    graph.addEdge(27, 28, 5); //this node is messing up
    graph.addEdge(27, 34, 7);
// 28
    graph.addEdge(28, 31, 5);
    graph.addEdge(28, 32, 1);
// 29
    graph.addEdge(29, 30, 1);
    graph.addEdge(29, 33, 5);
// 30
    graph.addEdge(30, 37, 4);
// 31
    graph.addEdge(31, 32, 4);
    graph.addEdge(31, 34, 3);
    graph.addEdge(31, 35, 9);
// 32
    graph.addEdge(32, 33, 4);
    graph.addEdge(32, 36, 1);
// 33
    graph.addEdge(33, 36, 7);
// 34 All edges added
// 35
    graph.addEdge(35, 36, 4);
    graph.addEdge(35, 37, 1);
// 36 All edges added
// 37 All edges added
    cout << "STARTING FROM 14" << endl;
    graph.calculatePaths(14);
    cout << endl << "STARTING FROM 1" << endl;
    graph.calculatePaths(1);
    graph.printGraph();
}
/*
"C:\Users\alexv\CS 233\Dykstrim\cmake-build-debug\Dykstrim.exe"
STARTING FROM 14
Node element 37 Distance: 24

STARTING FROM 1
Node element 37 Distance: 30
 0|   8 8         4             4           8
 1| 8         8
 2| 8     5     2
 3|     5                             1
 4|           7   3 5
 5|   8     7   8   1                                 6
 6|     2     8
 7| 4       3             1
 8|         5 1           8 7
 9|                     6   9 3
10|                   6       5       2                         4
11|               1 8       2   6
12|                 7 9   2   2   8 6
13|                   3 5   2         9
14| 4                     6
15|                         8                                             7
16|                         6         1
17|       1             2     9     1
18|
19|
20| 8                                         1     3     5             1
21|                                         1       1
22|                                               8   1 8
23|                                             8       2                     2
24|                                         3 1           2 6
25|           6                                 1       7   1 6
26|                                             8 2   7       9 5
27|                                         5       2       5           7
28|                                                 6 1   5       5 1
29|                                                   6 9       1     5
30|                     4                               5     1               4
31|                                                         5       4   3 9
32|                                                         1     4   4     1
33|                                                           5     4       7
34|                                         1             7       3
35|                               7                               9         4 1
36|                                                                 1 7   4
37|                                               2             4         1
38|
39|
40|
41|
42|
43|
44|
45|
46|
47|
48|
49|

Process finished with exit code 0

*/