#include "Graph.h"

Graph::Graph()
{
}

bool Graph::addConnection(string fromNodeId, string toNodeId, int cost)
{
    // eg connection from sengkang to punggol
    if (!hasConnection(fromNodeId,toNodeId))
    {
        Node* fromNode = nodeList->get(fromNodeId);
        Node* toNode = nodeList->get(toNodeId);


        Connection* forwardConnection = new Connection();
        forwardConnection->fromNode = fromNode;
        forwardConnection->toNode = toNode;
        forwardConnection->cost = cost;

        // eg connection from punggol to sengkang
        Connection* backwardConnection = new Connection();
        backwardConnection->fromNode = toNode;
        backwardConnection->toNode = fromNode;
        backwardConnection->cost = cost;

        connections.pushBack(forwardConnection);
        connections.pushBack(backwardConnection);
        return true;
    }

    return false;
}

bool Graph::removeAllConnectionsForNodeOneWay(string fromNodeId)
{
    Vector<Connection*> nodeConnections;
    getAllConnectionsForNode(fromNodeId, nodeConnections);

    if (nodeConnections.size() > 0)
    {
        for (int i = 0; i < nodeConnections.size(); i++)
        {
            removeConnection(nodeConnections[i]->fromNode->id, nodeConnections[i]->toNode->id);
        }
        return true;
    }
    return false;
}

bool Graph::removeAllConnectionsForNodeBothWays(string fromNodeId)
{
    Vector<Connection*> nodeConnections;
    getAllConnectionsForNode(fromNodeId, nodeConnections);

     if (nodeConnections.size() > 0)
     {
        for (int i = 0; i < nodeConnections.size(); i++)
        {   
            //due to connection being deleted
            string fromNode = nodeConnections[i]->fromNode->id;
            string toNode = nodeConnections[i]->toNode->id;

            removeConnection(fromNode, toNode);
            removeConnection(toNode, fromNode);
        }

        return true;
     }
     return false;
}

bool Graph::removeConnection(string fromNodeId, string toNodeId)
{
    if (hasConnection(fromNodeId, toNodeId))
    {
        int connectionIndex = getConnectionIndex(fromNodeId, toNodeId);
        Connection* connectionToDelete = connections[connectionIndex];
        connectionToDelete->fromNode = NULL;
        connectionToDelete->toNode = NULL;
        connectionToDelete->cost = 0;
        connections.remove(connectionIndex);
        delete connectionToDelete;
        return true;
            
    }
    return false;
}

bool Graph::hasConnection(string fromNodeId, string toNodeId)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {   

        string s = connections[i]->fromNode->id;
        string t = connections[i]->toNode->id;

        if (connections[i]->fromNode->id == fromNodeId && connections[i]->toNode->id == toNodeId)
        {
            return true;
        }
    }
    return false;
}

Connection* Graph::getConnection(string fromNodeId, string toNodeId)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        string s = connections[i]->fromNode->id;
        string t = connections[i]->toNode->id;

        if (connections[i]->fromNode->id == fromNodeId && connections[i]->toNode->id == toNodeId)
        {
            return connections[i];
        }
    }
    return NULL;
}

int Graph::getConnectionIndex(string fromNodeId, string toNodeId)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {
        if (connections[i]->fromNode->id == fromNodeId && connections[i]->toNode->id == toNodeId)
        {
            return i;
        }
    }
}

void Graph::getAllConnectionsForNode(string fromNodeId, Vector<Connection*>& nodeConnections)
{
    for (uint32_t i = 0; i < connections.size(); i++)
    {   
        string d = connections[i]->fromNode->id;
        if (connections[i]->fromNode->id == fromNodeId)
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


NodeRecord* getMin(Vector<NodeRecord*> &v, int start, int end)
{
    if (start == end)
    {
        return v.at(start);
    }
    else
    {
        int mid = (start + end) / 2;
        return min(
            getMin(v, start, mid), getMin(v, mid + 1, end),
            [](const NodeRecord* a, const NodeRecord* b) { return a->costSoFar < b->costSoFar;});
    }
}

void Graph::shortestPathBetweenStations(string fromNodeId, string toNodeid)
{
    Dictionary<NodeRecord*> openList;
    Dictionary<NodeRecord*> closedList;

    //Start record
    NodeRecord * startRecord = new NodeRecord();
    startRecord->nodeId = fromNodeId;
    startRecord->connection = nullptr;
    startRecord->costSoFar = 0;

    //test Record
    NodeRecord* startRecord1 = new NodeRecord();
    startRecord1->nodeId = "EW20";
    startRecord1->connection = nullptr;
    startRecord1->costSoFar = 10;

     NodeRecord* startRecord2 = new NodeRecord();
    startRecord2->nodeId = "EW21";
    startRecord2->connection = nullptr;
    startRecord2->costSoFar = -20;

    //add to openlist;
    openList.add(startRecord->nodeId, startRecord);
    openList.add(startRecord1->nodeId, startRecord1);
    openList.add(startRecord2->nodeId, startRecord2);


    while (!openList.isEmpty())
    {
        Vector<NodeRecord*> records;
        openList.getAllItems(records);
        NodeRecord* current = getMin(records, 0, records.size() - 1);
        return;
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