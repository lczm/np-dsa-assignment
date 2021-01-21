#pragma once
#include <iostream>
using namespace std;
#include "structures/vector.h"

struct Node
{
    string id;
};

struct Connection
{
    Node fromNode;
    Node toNode;
    int cost;
};

class Graph
{
   private:
    Vector<Connection*> connections;
    Vector<Node*> Nodes;

   public:
    Graph();
    bool addConnection(Node fromNode, Node toNode, int cost);
    bool addNode(Node& newNode);
    bool hasConnection(Node fromNode, Node toNode);
    void getAllConnectionsForNode(Node fromNode, Vector<Connection*>& nodeConnections);
    Vector<Connection*> getAllConnectionsForNode(Node fromNode);
    void getAllGraphConnections(Vector<Connection*>& graphConnections);
    void getAllNodesFromGraph(Vector<Node*>& graphNodes);
    ~Graph();
};