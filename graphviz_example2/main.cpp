#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "disjointsets.h"
#include "graph.h"
#include "graph2img.h"

using Node = Graph<char>::Node;
using MyGraph = Graph<char>;
using MyDisjointSets = DisjointSets<Node *>;

void buildGraph(MyGraph &graph) {
    Node *nodeA = graph.addNode('A');
    Node *nodeB = graph.addNode('B');
    Node *nodeC = graph.addNode('C');
    Node *nodeD = graph.addNode('D');
    Node *nodeE = graph.addNode('E');
    Node *nodeF = graph.addNode('F');
    Node *nodeG = graph.addNode('G');
    Node *nodeH = graph.addNode('H');
    Node *nodeI = graph.addNode('I');

    graph.addEdge(nodeA, nodeB, 4);
    graph.addEdge(nodeA, nodeH, 8);
    graph.addEdge(nodeB, nodeH, 11);
    graph.addEdge(nodeB, nodeC, 8);
    graph.addEdge(nodeC, nodeD, 7);
    graph.addEdge(nodeC, nodeF, 4);
    graph.addEdge(nodeC, nodeI, 2);
    graph.addEdge(nodeD, nodeF, 14);
    graph.addEdge(nodeD, nodeE, 9);
    graph.addEdge(nodeE, nodeF, 10);
    graph.addEdge(nodeF, nodeG, 2);
    graph.addEdge(nodeG, nodeI, 6);
    graph.addEdge(nodeG, nodeH, 1);
    graph.addEdge(nodeH, nodeI, 7);
}

// Returns the minimum spanning tree (mst) of a graph
MyGraph kruskal(MyGraph &graph) {
    MyGraph mst;

    MyDisjointSets s;

    for (Node *v: graph.getNodes())
        s.makeSet(v);

    bool skip = true;

    for (auto edge: graph.getEdgeWeights()) {
        if (skip = !skip)
            continue;

        int weight = edge.first;

        Node *u = edge.second.first;
        Node *v = edge.second.second;

        if (s.find(u) != s.find(v)) {
            Node *ut = mst.existsNode(u->data) ? mst.getNode(u->data) : mst.addNode(u->data);
            Node *vt = mst.existsNode(v->data) ? mst.getNode(v->data) : mst.addNode(v->data);

            mst.addEdge(ut, vt, weight);

            //std::cout << '(' << u->data << ',' << v->data << ')' << ':' << weight << std::endl;

            s.unionSet(u, v);
        }
    }

    return mst;
}

int main() {
    MyGraph graph;

    buildGraph(graph);

    MyGraph mst = kruskal(graph);

    printImage("output", "png", graph);
    // printImage("output", "gv", graph);

    return 0;
}