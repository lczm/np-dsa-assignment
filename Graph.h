#pragma once
#include <iostream>
#include "structures/vector.h"
#include "Dictionary.h"
using namespace std;

struct Node
{
    string id;
    string name;

    bool operator==(const Node& compare) const
    {
        return (id == compare.id) && (name == compare.name);
    }
};

struct Connection
{
    Node * fromNode;
    Node* toNode;
    int cost;
};

class Graph
{
   private:
    Vector<Connection*> connections;
    Dictionary<Node*>* nodeList;

   public:
    Graph();
    void setNodeList(Dictionary<Node*>* nodeList)
    {
        this->nodeList = nodeList;
    }
    Dictionary<Node*>* & getNodeList()
    {
        return nodeList;
    };

    bool addConnection(string fromNodeId, string toNodeId, int cost);
    bool removeAllConnectionsForNodeOneWay(string fromNodeId);
    bool removeAllConnectionsForNodeBothWays(string fromNodeId);
    bool removeConnection(string fromNodeId, string toNodeId);
    bool hasConnection(string fromNodeId, string toNodeId);
    int  getConnectionIndex(string fromNodeId, string toNodeId);
    void getAllConnectionsForNode(string fromNodeId, Vector<Connection*>& nodeConnections);
    void getAllGraphConnections(Vector<Connection*>& graphConnections);
    void shortestPathBetweenStations(string fromNodeId, string toNodeid);
    ~Graph();
};