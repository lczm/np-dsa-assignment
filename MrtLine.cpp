#include "MrtLine.h"

int extractIntegers(string stationId)
{
    string number;

    for (int i = 0; i < stationId.size(); i++)
    {
        if (isdigit(stationId[i]))
        {
            number += stationId[i];
        }
    }

    stringstream geek(number); 
    int x = 0;
    geek >> x; 

    return x;
}

string extractString(string stationId)
{
    string lineIdentifier;

    for (int i = 0; i < stationId.size(); i++)
    {
        if (isalpha(stationId[i]))
        {
            lineIdentifier += stationId[i];
        }
    }

    return lineIdentifier;
}

MrtLine::MrtLine()
{
}

MrtLine::MrtLine(Graph* graph)
{
    this->graph = graph;
}


//will refactor
void MrtLine::addNewStation(string stationId, string newStationName, bool infront, int costPrev,
                            int costForward)
{   
    //extracting the string and integers
    int extractedId = extractIntegers(stationId);
    string mrtLineIdentifier = extractString(stationId);
    int selectedStationPtr = 0;


    for (int i = 0; i < stationList.getSize(); i++)
    {
        if (stationList.getAt(i)->id == stationId)
        {
            selectedStationPtr = i;
        }
    }

    Node* newStation = new Node();
    newStation->name = newStationName;

    if (infront)
    {   
        newStation->id = mrtLineIdentifier + to_string(extractedId + 1);
        updateLineIds(newStation->id);
        updateConnectionsBetweenStations(selectedStationPtr, selectedStationPtr + 1, costPrev,
                                         costForward, newStation, 1);
    }
    else
    {
        newStation->id = mrtLineIdentifier + to_string(extractedId);
        updateLineIds(newStation->id);
        updateConnectionsBetweenStations(selectedStationPtr, selectedStationPtr - 1, costForward,
                                         costPrev, newStation, 0);
    }
  
}

void MrtLine::updateLineIds(string newStationId)
{
    // Update all the stationIds
    string mrtLineIdentifier = extractString(newStationId);
    Dictionary<Node*>* nodeList = graph->getNodeList();
    for (int i = stationList.getSize()-1; i >= 0; i--)
    {
        if (extractIntegers(stationList.getAt(i)->id) >= extractIntegers(newStationId))
        {
            //Update the hash table in containing all the nodes
            Node* current = nodeList->get(stationList.getAt(i)->id);
            nodeList->remove(stationList.getAt(i)->id);

            int ChangeExtractedId = extractIntegers(stationList.getAt(i)->id) + 1;
            string id = mrtLineIdentifier + to_string(ChangeExtractedId);

            stationList.getAt(i)->id = id;
            nodeList->add(stationList.getAt(i)->id, current);
        }
    }
}

void MrtLine::updateConnectionsBetweenStations(int selectedStationPtr, int oldStationIndex,
                                               int costPrev,
                                               int costForward, Node* newStation, 
                                               int beforeAfter)
{
    // removing old connections
    string oldConnectionStationId = stationList.getAt(oldStationIndex)->id;
    graph->removeConnection(stationList.getAt(selectedStationPtr)->id, oldConnectionStationId);
    graph->removeConnection(oldConnectionStationId, stationList.getAt(selectedStationPtr)->id);

    // adding new connections
    Dictionary<Node*>* nodeList = graph->getNodeList();
    nodeList->add(newStation->id, newStation);


    graph->addConnection(stationList.getAt(selectedStationPtr)->id, newStation->id, costPrev);
    graph->addConnection(newStation->id, oldConnectionStationId, costForward);
    
    stationList.addAt(newStation, selectedStationPtr + beforeAfter);

}

void MrtLine::addStationFront(Node*& newNode)
{
    stationList.addFront(newNode);
}

void MrtLine::addStationBack(Node*& newNode)
{
    stationList.addBack(newNode);
}

void MrtLine::removeStation(Node*& newNode)
{
}

void MrtLine::removeConnectionBetweenStations(string fromNodeId, string toNodeId)
{
}

void MrtLine::printStationsAll()
{
    for (int i = 0; i < stationList.getSize(); i++)
    {
        cout << "Id:" << stationList.getAt(i)->id << " Name:" << stationList.getAt(i)->name << endl;
    }
}

void MrtLine::printStationsBasedOnDirection(string stationId)
{
}

MrtLine::~MrtLine()
{
}

