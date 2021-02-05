#pragma once
#include <iostream>
#include <algorithm>
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


struct NodeRecord
{
    string nodeId;
    Connection* connection;
    int costSoFar;
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

    //Add a connection between two stations (E.g. EW1 to EW2 with a cost of 1000m)
    // pre : fromNodeId, toNodeId
    // post: Add the connection to the graph
    // returns a boolean
    bool addConnection(string fromNodeId, string toNodeId, int cost);

    //Remove all connections that a fromNode has to the toNode
    // pre : fromNodeId
    // post: Removes all connections from the fromNode to the toNode
    // Returns a boolean
    bool removeAllConnectionsForNodeOneWay(string fromNodeId);

    //Remove all connections that a fromNode has to the toNode (vice-versa)
    // pre : fromNodeId
    // post: Removes all the connections from the fromNode to the toNode
    // and the connection from the toNode to the fromNode
    bool removeAllConnectionsForNodeBothWays(string fromNodeId);

    // Removes the connection one way between these two nodes
    // pre : fromNodeId, toNodeId
    // post: bool
    // Removes the connection from the fromNode to the toNode
    bool removeConnection(string fromNodeId, string toNodeId);

    //Check if the two nodes has a connection
    // pre : fromNodeId, toNodeId
    // post: bool
    // Returns true if the two nodes have a connection
    bool hasConnection(string fromNodeId, string toNodeId);

    //Get the specific connection between these two nodes
    // pre : fromNodeId, toNodeId
    // post: None
    // Returns a pointer to the connection
    Connection* getConnection(string fromNodeId, string toNodeId);

    //Get the index of the connection specified
    // pre : fromNodeId, toNodeId
    // post: None
    // Returns the index of the connection stored in the vector
    int  getConnectionIndex(string fromNodeId, string toNodeId);

    // Get all the existing connections that the node has
    // pre : fromNodeId, nodeConnections
    // post: None
    // Returns all the connections that a node has
    void getAllConnectionsForNode(string fromNodeId, Vector<Connection*>& nodeConnections);

    //Get all of the graph's connections
    // pre : graphConnections
    // post: None
    // Returns all the connections that the graph has
    void getAllGraphConnections(Vector<Connection*>& graphConnections);

    //Get the shortest path between two nodes
    // pre : Starting destination, end destination
    // post: None
    // Returns the shortest path between the two stations
    void shortestPathBetweenStations(string fromNodeId, string toNodeId,
                                                    Vector<Connection*> &cons);
    ~Graph();
};