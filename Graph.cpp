#include "Graph.h"

Graph::Graph()
{
}

bool Graph::addConnection(string fromNode, string toNode, int cost)
{
    // eg connection from sengkang to punggol
    Connection* forwardConnection = new Connection();
    forwardConnection->fromNodeId = fromNode;
    forwardConnection->toNodeId = toNode;
    forwardConnection->cost = cost;

    // eg connection from punggol to sengkang
    Connection* backwardConnection = new Connection();
    backwardConnection->fromNodeId = toNode;
    backwardConnection->toNodeId = fromNode;
    backwardConnection->cost = cost;

    connections.pushBack(forwardConnection);
    connections.pushBack(backwardConnection);
    return true;
}

bool Graph::hasConnection(string fromNode, string toNode)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        if (connections[i]->fromNodeId == fromNode && connections[i]->toNodeId == toNode)
        {
            return true;
        }
    }
    return false;
}

void Graph::getAllConnectionsForNode(string fromNodeId, Vector<Connection*>& nodeConnections)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        if (connections[i]->fromNodeId == fromNodeId)
        {
            nodeConnections.pushBack(connections[i]);
        }
    }
}

void Graph::getAllGraphConnections(Vector<Connection*>& graphConnections)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        graphConnections.pushBack(connections[i]);
    }
}


Graph::~Graph()
{
    // Not needed as vector deletes automatically, this causes undefined behaviour
    // for (uint32_t i = 0; i < connections.size(); i++)
    // {
    //     delete connections[i];
    // }
}