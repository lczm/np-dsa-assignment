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

   public:
    Graph();
    bool addConnection(Node fromNode, Node toNode, int cost);
    bool hasConnection(Node fromNode, Node toNode);
    void getAllConnections(Node fromNode, Vector<Connection*>& nodeConnections);
    ~Graph();
};