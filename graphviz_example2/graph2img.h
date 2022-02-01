
#ifndef GRAPH2IMG_H
#define GRAPH2IMG_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <gvc.h>
#include "graph.h"


// Creates a DOT file, representing the graph, which can be used as input for visualization in Graphviz
template<typename T>
void printImage(std::string fileName, const char *extension, Graph<T> &graph) {
    using Node = typename Graph<T>::Node;

    Agraph_t *g;                            // Graphviz's special graph data structure
    std::map<Node *, Agnode_t *> agnodes;      // A mapping between nodes of our graph to nodes in the Graphviz's graph

    // Setting up a Graphviz Context - but only once even for multiple graphs
#ifndef NO_LAYOUT_OR_RENDERING
    static GVC_t *gvc;
    if (!gvc)
        gvc = gvContext();
#endif

    g = agopen("g", Agundirected, NULL); // Change constant to "Agdirected" for directed graphs

    for (Node *node: graph.getNodes()) {
        std::stringstream ss;
        ss << node->data;
        char nodeLabel[20];
        ss >> nodeLabel;

        agnodes[node] = agnode(g, nodeLabel,
                               TRUE);  // 'nodeLabel' will also internally denote the node identifier in the graph

        // Setting attributes when creating the nodes
        agsafeset(agnodes[node], "color", "red", "");
    }

    bool skip = true;

    for (auto edge: graph.getEdgeWeights()) {
        if ((skip = !skip)) // only for undirected graphs
            continue;

        int weight = edge.first;
        Node *u = edge.second.first;
        Node *v = edge.second.second;

        std::stringstream ss;
        ss << weight;
        char edgeWeight[20];
        ss >> edgeWeight;

        Agedge_t *ghEdge = agedge(g, agnodes[u], agnodes[v], nullptr, TRUE);

        // Setting attributes when creating the edges
        agsafeset(ghEdge, "color", "blue", "");
        agsafeset(ghEdge, "label", edgeWeight, "");
    }

#ifdef NO_LAYOUT_OR_RENDERING
    agwrite(g, stdout);
#else
    gvLayout(gvc, g, "dot");

    fileName = fileName + "." + extension;

    gvRenderFilename(gvc, g, extension, fileName.c_str());
    gvFreeLayout(gvc, g);

#endif

    agclose(g);
}

#endif