//
// Created by alexv on 6/7/2023.
//

#ifndef DYKSTRIM_GRAPH_H
#define DYKSTRIM_GRAPH_H

#include <vector>
#include <queue>
#include "pch.h"
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;
static int EDGENUMBER = 0;
const int VECTORSIZE = 100;
const int GRAPHSIZE = 50;

class Vertex {
public:
    int vrtElement;// vertex key
    int distance;
    bool visited; //used to check if node has been visited
    vector<int> edges;

    Vertex(int vrtElement, int distance = INFINITY, bool visited = false) : distance(
            distance), vrtElement(vrtElement), visited(visited) {
        // empty constructor
    }
}; // end of vertex class

class Edges {
public:
    int degree;
    int weight;
    Vertex *v1;
    Vertex *v2;

    Edges(int degree, int weight, Vertex *v1 = nullptr, Vertex *v2 = nullptr) : degree(
            degree), weight(weight), v1(v1), v2(v2) {
    }
}; // end of Edges class

struct PrioitySort {
    bool operator()(const Edges *lhs, const Edges *rhs) const {
        return lhs->weight > rhs->weight;
    }
};

class Graph {
public:
    Graph() {
        for (int i = 0; i < GRAPHSIZE; i++) {
            for (int j = 0; j < GRAPHSIZE; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }

    void addVertex(int v1Row, int v1Col) {
        //insert the newVertex in the graph
        Vertex *newVertex = new Vertex(v1Row);
        vertices[v1Row] = newVertex;
    }

    void addEdge(int v1, int v2, int weight) {
        Edges *newEdge = new Edges(++EDGENUMBER, weight);
        vertices[v1]->edges.push_back(EDGENUMBER);
        vertices[v2]->edges.push_back(EDGENUMBER);
        newEdge->v1 = vertices[v1];
        newEdge->v2 = vertices[v2];
        edges[EDGENUMBER] = newEdge;
        adjMatrix[v1][v2] = weight;
        adjMatrix[v2][v1] = weight;
    }

    Vertex *getVertex(int vrtElement) {
        for (int i = 0; i < VECTORSIZE; i++) {
            if (vertices[i]->vrtElement == vrtElement) {
                return vertices[i];
            }
        }
    }

    Edges *getEdge(int edgeElement) {
        for (int i = 0; i < VECTORSIZE; i++) {
            if (edges[i] != nullptr && edges[i]->degree == edgeElement) {
                return edges[i];
            }
        }
    }

    void calculatePaths(int vrtElement) {
        priority_queue<Edges *> priorityEdges;
        Vertex *currentVrt;
        Edges *vrtEdge;
        currentVrt = getVertex(vrtElement);
        if (currentVrt->vrtElement != vrtElement) {
            cout << "Not in Adjacency Matrix" << endl;
            return;
        }
        //v1 = prev, v2 = next
        currentVrt->distance = 0;
        while (currentVrt->vrtElement != 37) {
            if (!currentVrt->visited) {
                currentVrt->visited = true;
                for (int i = 0; i < currentVrt->edges.size(); i++) {
                    vrtEdge = getEdge(currentVrt->edges[i]);
                    if (vrtEdge->v1 != currentVrt) {
                        if (vrtEdge->v1->distance >=
                            currentVrt->distance + vrtEdge->weight) {
                            vrtEdge->v1->distance =
                                    currentVrt->distance + vrtEdge->weight;
                        }
                    }
                    else {
                        if (vrtEdge->v2->distance >=
                            currentVrt->distance + vrtEdge->weight) {
                            vrtEdge->v2->distance =
                                    currentVrt->distance + vrtEdge->weight;
                        }
                    }
                    priorityEdges.push(vrtEdge);
                }
            }
            vrtEdge = priorityEdges.top();
            priorityEdges.pop();
            if (currentVrt != vrtEdge->v1) {
                currentVrt = vrtEdge->v1;
            }
            else {
                currentVrt = vrtEdge->v2;
            }
        }
        cout << "Node element " << currentVrt->vrtElement << " Distance: "
             << currentVrt->distance <<
             endl;
        for (
                int i = 0;
                i < VECTORSIZE;
                i++) {
            if (vertices[i] != nullptr) {
                vertices[i]->visited = false;
                vertices[i]->distance = INFINITY;
            }
        }
        while (!priorityEdges.empty()) {
            priorityEdges.pop();
        }
    }

    void printGraph() {
        for (int i = 0; i < GRAPHSIZE; i++) {
            cout << setw(2) << i << "| "; //row
            for (int j = 0; j < GRAPHSIZE; j++) {
                if (adjMatrix[i][j] != 0) {
                    cout << adjMatrix[i][j] << " "; //col
                }
                else {
                    cout << "  "; //col
                }
            }
            cout << endl;
        }
    }

private:
    Vertex *vertices[VECTORSIZE]{};
    Edges *edges[VECTORSIZE]{};
    int adjMatrix[GRAPHSIZE][GRAPHSIZE];
}; // end of Graph class

#endif //DYKSTRIM_GRAPH_H
