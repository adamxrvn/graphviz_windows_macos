// UNDIRECTED WEIGHTED GRAPH

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

template<typename T>
class Graph
{
public:

    class Node
    {
    public:
        T data;
        Node(const T& data = T()) : data(data) {}
    };

    ~Graph()
    {
        for (Node* node : _nodes)
            delete node;
    }

    Node* addNode(const T& data = T())
    {
        Node* node = new Node(data);

        _nodes.push_back(node);

        return node;
    }

    bool existsNode(T& x)
    {
        // Check if exists a node with data = x
        for(Node* node : _nodes)
            if(node->data == x)
                return true;
        return false;
    }

    void addEdge(Node* nodeSource, Node* nodeDest, int weight)
    {
        bool existsNodeSource = std::find(_nodes.begin(), _nodes.end(), nodeSource) != _nodes.end();
        bool existsNodeDest = std::find(_nodes.begin(), _nodes.end(), nodeDest) != _nodes.end();

        if (existsNodeSource && existsNodeDest)
        {
            // Create two edges (A,B) and (A,B) which represent a bi-directional link A<--->B
            _adjList.insert( { nodeSource , nodeDest });
            _adjList.insert( { nodeDest , nodeDest  });

            _edgeWeights.insert({ weight, {nodeSource, nodeDest} } );
            _edgeWeights.insert({ weight, {nodeDest, nodeSource} } );
        }
    }

    Node* getNode(const T& data)
    {
        for(Node* node : _nodes)
            if(node->data == data)
                return node;
        return nullptr;
    }

    bool existsEdge(Node* x, Node* y)
    {
        auto ret = _adjList.equal_range(x);

        // all pairs whose first component is equal to x are in the range [ret->first, ret->second)
        for(auto it = ret.first; it != ret.second; ++it)
            if(it->second == y)
                return true;
        return false;
    }

    std::vector<Node*> getNeighbors(Node* x)
    {
        std::vector<Node*> neighbors;

        auto ret = _adjList.equal_range(x);

        for(auto it = ret.first; it != ret.second; ++it)
            neighbors.push_back(it->second);

        // for every node "y" in the vector "neighbors", there exists an edge "(x,y)" in the graph.
        return neighbors;
    }

    int getNodeOutDegree(Node* x)
    {
        return this->getNeighbors(x).size();
    }

    int getNodeInDegree(Node* x)
    {
        int cnt = 0;

        for(auto pair : _adjList)
            if(pair.second == x)
                cnt++;
        return cnt;
    }

    const std::vector<Node*>& getNodes() const
    {
        return _nodes;
    }

    const std::multimap<int, std::pair<Node*,Node*>> getEdgeWeights() const
    {
        return _edgeWeights;
    }

private:

    std::multimap<Node*, Node*> _adjList;

    std::multimap<int, std::pair<Node*,Node*>> _edgeWeights;

    std::vector<Node*> _nodes;

};

template<typename T>
std::ostream& operator <<(std::ostream& os, const Graph<T>& graph)
{
    using Node = typename Graph<T>::Node;

    for(Node* node : graph.getNodes())
        os << node->data << std::endl;

    bool skip = true; // only for undirected graphs!

    for(auto edge : graph.getEdgeWeights())
    {
        if(skip = !skip) //only for undirected graphs
            continue;

        int weight = edge.first;

        Node* u = edge.second.first;
        Node* v = edge.second.second;

        os << u->data << ' ' << v->data << ' ' <<  weight << std::endl; // printing the weight
    }

    return os;
}

#endif