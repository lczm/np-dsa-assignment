#pragma once
#include <iostream>
#include "structures/vector.h"
using namespace std;

struct Node
{
    string id;
    string name;
};

struct Connection
{
    string fromNodeId;
    string toNodeId;
    int cost;
};

class Graph
{
   private:
    Vector<Connection*> connections;

   public:
    Graph();
    bool addConnection(string fromNode, string toNode, int cost);
    bool hasConnection(string fromNode, string toNode);
    void getAllConnectionsForNode(string fromNodeId, Vector<Connection*>& nodeConnections);
    void getAllGraphConnections(Vector<Connection*>& graphConnections);
    ~Graph();
};