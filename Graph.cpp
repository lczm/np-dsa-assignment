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


//NodeRecord* getMin(Vector<NodeRecord*> &v, int start, int end)
//{
//    if (start == end)
//    {
//        return v.at(start);
//    }
//    else
//    {
//        int mid = (start + end) / 2;
//        return std::min(
//            getMin(v, start, mid), getMin(v, mid + 1, end),
//            [](const NodeRecord* a, const NodeRecord* b) { return a->costSoFar < b->costSoFar;});
//    }
//}

//Compares two node records and returns the min of the two
NodeRecord* minCost( NodeRecord* a, NodeRecord* b){

    return (a->costSoFar < b->costSoFar) ? a :  b;
};


//Recursive algorithm that get the lowest cost in an unordered list
//and returns the NodeRecord that has the lowest cost
NodeRecord* getMin(Vector<NodeRecord*>& v, int start, int end)
{
    if (start == end)
    {
        return v.at(start);
    }
    else
    {
        int mid = (start + end) / 2;
        return minCost(getMin(v, start, mid), getMin(v, mid + 1, end));
    }
}


void Graph::shortestPathBetweenStations(string fromNodeId, string toNodeId,
                                                       Vector<Connection*>& cons)
{
    Dictionary<NodeRecord*> openList; //Nodes yet to visit
    Dictionary<NodeRecord*> closedList; //Visited nodes
    //Start record
    NodeRecord * startRecord = new NodeRecord();
    startRecord->nodeId = fromNodeId;
    startRecord->connection = nullptr;
    startRecord->costSoFar = 0;

    //Add the start node to the openList
    openList.add(startRecord->nodeId, startRecord);
    NodeRecord* current = nullptr; 

    while (!openList.isEmpty())
    {   
        //Get all the records from the openList
        Vector<NodeRecord*> records;
        openList.getAllItems(records);

        //Get the NodeRecord with the minimum costSoFar
        current = getMin(records, 0, records.size() - 1);
        
        //Break if the current node is the endNode
        if (current->nodeId == toNodeId)
        {
            break;
        }

        //Get all the connections for the current node
        Vector<Connection*> connections;
        this->getAllConnectionsForNode(current->nodeId, connections);

        //Traverse through all the connections that has
        //a connection to the current node
        for (int i = 0; i < connections.size(); i++)
        {   
            Node* endNode = connections[i]->toNode;
            int endNodeCost = current->costSoFar + connections[i]->cost;

            //If the closed list has the node we skip it
            //as we do not want to go in circles
            if (closedList.hasKey(endNode->id))
            {
                continue;
            }
            else if (openList.hasKey(endNode->id))
            {   
                //If this node's costSoFar is greater than the cost from coming by this node
                //update the costSoFar as well as the connection to this node
                //the toNodeId would be the endNode
                if (openList.get(endNode->id)->costSoFar > endNodeCost)
                {
                    openList.get(endNode->id)->costSoFar = endNodeCost;
                    openList.get(endNode->id)->connection = connections[i];
                }

                //If it is lesser or equal to we continue
                else
                {
                    continue;
                }
            }
            else
            {   
                //If the open List does not have the record
                //We create a new Noderecord & add it to the dictionary
                NodeRecord* endNodeRecord = new NodeRecord();
                endNodeRecord->nodeId = endNode->id;
                endNodeRecord->connection = connections[i];
                endNodeRecord->costSoFar = endNodeCost;
                openList.add(endNodeRecord->nodeId, endNodeRecord);
            }
        }

        //Finally we remove the current node and
        //append it to the closed list we have searched though all of its connections
        openList.remove(current->nodeId);
        closedList.add(current->nodeId, current);

    }

    //If after the algorithm the current node is not the end Node
    //We return nothing
    if (current->nodeId != toNodeId)
    {
        return;
    }
    else
    {   
        //lastly we get the shortest path
        while (current->nodeId != fromNodeId)
        {
            cons.pushBack(current->connection);
            current = closedList.get(current->connection->fromNode->id);
        }

        //add reverse
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