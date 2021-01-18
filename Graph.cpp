#include "Graph.h"


Graph::Graph()
{
}



bool Graph::addConnection(Node fromNode, Node toNode, int cost)
{   

    //eg connection from sengkang to punggol
    Connection* forwardConnection = new Connection();
    forwardConnection->fromNode = fromNode;
    forwardConnection->toNode = toNode;
    forwardConnection->cost = cost;

    // eg connection from punggol to sengkang
    Connection* backwardConnection = new Connection();
    backwardConnection->fromNode = toNode;
    backwardConnection->toNode = fromNode;
    backwardConnection->cost = cost;

    connections.push_back(forwardConnection);
    connections.push_back(backwardConnection);
    return true;
}


bool Graph::hasConnection(Node fromNode, Node toNode)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        if (connections[i]->fromNode.id == fromNode.id && connections[i]->toNode.id == toNode.id)
        {
            return true;
        }
    }
    return false;
}

void Graph::getAllConnections(Node fromNode, Vector<Connection*>& nodeConnections)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        if (connections[i]->fromNode.id == fromNode.id)
        {
            nodeConnections.push_back(connections[i]);
        }
    }

}

Graph::~Graph()
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        delete connections[i];
    }
}